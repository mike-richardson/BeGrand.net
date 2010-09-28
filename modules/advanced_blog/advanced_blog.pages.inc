<?php
// $Id: advanced_blog.pages.inc,v 1.7 2010/05/08 11:44:50 xeniox Exp $

/**
 * @file
 * Renders pages for advanced_blog module
 */

/**
 * Renders sortable blog post overview page per user and timeframe
 */
function blog_nav_page($user, $year = NULL, $month = NULL, $day = NULL) {
  // initiate the pager attributes array with default values
  $pager_attrib = array("sort" => variable_get('blog_nav_sort', 'date'), 'order' => variable_get('blog_nav_order', 'DESC'));

  // change pager_attrib based on parameters
  if (isset($_GET['order'])) {
    $pager_attrib['order'] = ($_GET['order'] == 'desc') ? 'desc' : 'asc';
  }

  if (isset($_GET['sort'])) {
    switch ($_GET['sort']) {
      case 'date':
        $pager_attrib['sort'] = ($_GET['sort'] == 'date') ? 'date' : 'date';
        break;
      case 'title':
        $pager_attrib['sort'] = ($_GET['sort'] == 'title') ? 'title' : 'title';
        break;
      default:
        $pager_attrib['sort'] =  'date';
        break;
    }
  }

  // Load the appropriate user object
  if (is_numeric($user)) {
    $tempuser = user_load(array('uid' =>  $user));
  }
  else {
    $tempuser = user_load(array('name' => $user));
  }

  // Initiate the query
  $query = "SELECT n.nid, n.created, n.title, YEAR(FROM_UNIXTIME(n.created)) AS year, MONTH(FROM_UNIXTIME(n.created)) AS month, DAY(FROM_UNIXTIME(n.created)) AS day FROM {node} n WHERE n.type = 'blog' AND n.status <> 0 AND n.uid = %d ";

  // Initiate the arguments array for the paged query
  $args = array();
  $args[] = $tempuser->uid;

  // add LIMIT clause
  if ($year) {
    $query .= "AND YEAR(FROM_UNIXTIME(n.created)) = %d ";
    $args[] = $year;
  }

  if (is_numeric($month)) {
    $query .= "AND MONTH(FROM_UNIXTIME(n.created)) = %d ";
    $args[] = $month;
  }

  if (is_numeric($day)) {
    $query .= "AND DAY(FROM_UNIXTIME(n.created)) = %d";
    $args[] = $day;
  }

  // add SORT BY clause
  switch ($pager_attrib['sort']) {
    case 'date':
      $query .= " ORDER BY n.created " . $pager_attrib['order'] . " ";
      break;
    case 'title':
      $query .= " ORDER BY n.title " . $pager_attrib['order'] . " ";
      break;
    default:
      $query .= " ORDER BY n.created ASC ";
      break;
  } //end switch

  $result = pager_query($query, variable_get('blog_nav_nposts_userhomepage', 20), 0, NULL, $args);

  return theme('advanced_blog_nav_page_results', $result, $pager_attrib);
}

function theme_advanced_blog_nav_page_results($result, $attrib = array("sort" => 'title', 'order' => 'ASC')) {
  $output = theme('advanced_blog_nav_sort', $attrib);

  $entries = array();
  while ($node = db_fetch_object($result)) {
    $month = date('F', $node->created);
    $entries[] = l($node->title, 'node/' . $node->nid) . ' - ' . $entry_date = format_date($node->created);
  }
  $output .= theme('item_list', $entries);
  $output .= theme('pager', 0, variable_get('blog_nav_nposts_userhomepage', 20));
  return $output;
}

/**
 * Theme function: Theme blog detail page sort navigation
 */
function theme_advanced_blog_nav_sort($attributes) {
  $order = (strtolower($attributes['order']) == "desc") ? "asc" : "desc";
  $sort_attr = array("title" => t("Click a second time to reverse the sort order"));
  $output .= '<div class="blog_nav-sort">';
  $output .= t('Sort by:') . ' ';
  $output .= "[". l(t("Title"), $_GET['q'], array('attributes' => $sort_attr, 'query' => "&sort=title&order=$order"));
  $output .= "][". l(t("Date"), $_GET['q'], array('attributes' => $sort_attr, 'query' => "&sort=date&order=$order"));
  $output .= "]</div><br /> ";
  return $output;
}

function advanced_blog_page_list() {
  $maxdisp = 25;
  $advanced_blog_order  = variable_get("advanced_blog_order", 0);

  drupal_add_css(drupal_get_path('module', 'advanced_blog') .'/advanced_blog.css');

  // @TODO: find out why this is not used
  switch ($advanced_blog_order) {
    case 1: $order = 'user.name';
      break;
    case 2: $order = 'numitems DESC, u.name';
      break;
    case 3: $order = 'n.created DESC, u.name';
      break;
    case 4: $order = 'RAND()';
      break;
    default: $order = 'user.name';
  }

  $sql = "SELECT DISTINCT users.uid, users.name
  FROM {users} users
  LEFT JOIN {node} node
  ON users.uid = node.uid
  WHERE node.type = 'blog' AND users.uid <> 0
  ORDER BY users.name ASC";

  $sql_counts = "SELECT COUNT(DISTINCT (users.uid))
  FROM {users} users
  LEFT JOIN {node} node
  ON users.uid = node.uid
  WHERE node.type = 'blog' AND users.uid <> 0
  ORDER BY users.name ASC";

  $query = pager_query($sql, $maxdisp, 0, $sql_counts);
  $output .= '<div id="bloggerlist" class="clear-block">';
  while ($blogger = db_fetch_object($query)) {
    // Blogger account info
    $account = user_load($blogger->uid);
    $uid = $account->uid;
    if (empty($account->picture)) {
      $account->picture = variable_get('user_picture_default', '');
    }

    // Advanced blog info
    $details = advanced_blog_get_blog_details($uid);

    // Blogger posts
    $posts_qry = db_query_range("SELECT node.nid AS nid, node.title AS title
      FROM {node} node
      INNER JOIN {users} users ON node.uid = users.uid
      WHERE node.type = 'blog'
      AND node.status <> 0
      AND users.uid = %d
      ORDER BY node.created DESC", $uid, 0, 5);
    $posts = array();
    while ($row = db_fetch_object($posts_qry)) {
      $posts[] = l($row->title, 'node/' . $row->nid);
    }

    if (count($posts) == 5) {
      $posts[] = l(t('more...'), 'blog/' . $account->uid);
    }
    $output .= theme('advanced_blog_page_blogger_item', $account, $details, $posts);
  }
  $output .= "</div>";

  $output .= theme('pager', NULL, $maxdisp, 0);
  $output = theme('box', '', $output, 'main');
  return $output;
}

/**
 * Theme a blogger item on the advanced blog blogger list page
 */
function theme_advanced_blog_page_blogger_item($account, $details, $posts) {
  $output = '<div class="blogger">';
  $output .= '<div class="bloggerpic">';
  $output .= l('<img src="' . file_create_url($account->picture) . '" alt="' . $account->name . '" title="' . $account->name . '" />', 'user/' . $account->uid, array('html' => 'TRUE'));
  // check if user can be contacted!
  if (module_exists('contact') && _contact_user_tab_access($account)) {
    $output .= '<div class="bloggercontact">' . l(t('Contact me'), 'user/' . $account->uid . '/contact') . '</div>';  	
  }
  $output .= '</div>';
  $output .= '<div class="info">';
  $output .= '<h2>' . ((!empty($details->title)) ? l($details->title, 'blog/' . $account->uid) : theme_username($account)) . '</h2>';
  if ($details->description) {
    $output .= '<div class="about">' . $details->description . '</div>';
  }
  $output .= '<div class="entries">';
  $output .= '<h3>' . t('Posts') . '</h3>';
  $output .= theme('item_list', $posts);
  $output .= '</div>';
  $output .= '</div>';
  $output .= '</div>';
  return $output;
}