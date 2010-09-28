<?php
// $Id: taxonomy_vtn.pages.inc,v 1.1.2.53 2009/07/26 21:39:07 alexiswilke Exp $

/**
 * @file
 * pages for display vocabularies, terms and nodes
 *
 */


/**
 * Get a list of vocabularies or terms to include/exclude.
 * In case users do not put spaces, we remove them here.
 *
 * @param[in] $varname1  The name of the global variable
 * @param[in] $varname2  The name of the local variable when available
 *
 * @return NULL or an array of identifiers
 */
function _taxonomy_vtn_get_list($varname1, $varname2 = NULL) {
  $result = NULL;

  $r = explode(',', str_replace(' ', '', variable_get($varname1, '')));

  if ($varname2) {
    $r = array_merge($r, explode(',', str_replace(' ', '', variable_get($varname2, ''))));
  }

  foreach($r as $id) {
    if (is_numeric($id)) {
      $result[$id] = $id;
    }
  }

  return $result;
}

/**
 * Set term or node pages breadcrumb
 */
function _taxonomy_vtn_set_breadcrumb($parent, $voc_obj, $include_parent) {
  if ($include_parent) {
    $term = taxonomy_get_term($parent);
    $breadcrumb[] = l($term->name, 'taxonomy_vtn/voc/' . $voc_obj->vid . '/' . $parent . '/1');
  }
  for ($p = $parent; $p > 0; $p = $first_parent->tid) {
    $term_parents = taxonomy_get_parents($p);
    if (count($term_parents) == 0) {
      // go to the root of this vocabulary
      $breadcrumb[] = l($voc_obj->name, 'taxonomy_vtn/voc/' . $voc_obj->vid . '/0/1');
      break;
    }
    // TODO: multi-parent is not currently supported...
    $first_parent = array_shift($term_parents);
    $breadcrumb[] = l($first_parent->name, 'taxonomy_vtn/voc/' . $voc_obj->vid . '/' . $first_parent->tid . '/1');
  }
  $breadcrumb[] = l(variable_get('taxonomy_vtn_vocabularies_master_index', t('Master index')), 'taxonomy_vtn');
  $breadcrumb[] = l(t('Home'), '<front>');
  drupal_set_breadcrumb(array_reverse($breadcrumb));
}

/**
 * Implementation of taxonomy_vtn_show_vocabularies().
 */
function taxonomy_vtn_show_vocabularies($op, $group) {
  $groups = array();
  switch ($op) {
  //case 'all':    // list all as before unless default groups are defined
  default:
    $group = variable_get('taxonomy_vtn_vocabularies_default_groups', NULL);
    if (is_string($group)) {
      $groups = explode(',', drupal_strtolower($group));
      if (count($groups) > 0) {
        $op = 'groups';
      }
      else {
        $group = NULL;
      }
    }
    break;

  case 'group':  // list as all, but only with the specified groups
    if ($group == 'all') {
      $group = NULL;
    }
    else {
      $groups = explode(',', drupal_strtolower($group));
    }
    break;

  case 'groups': // list groups separated by their name
    if ($group == 'all') {
      $group = NULL;
    }
    else {
      $groups = explode(',', drupal_strtolower($group));
    }
    break;

  }
  // remove the spaces, just in case
  foreach ($groups as $k => $grp) {
    $groups[$k] = trim($grp);
  }

  // all vocabulary ids
  $all_vocs = taxonomy_get_vocabularies();

  // keep only those the user wants to include
  $include_vocs = _taxonomy_vtn_get_list('taxonomy_vtn_vocabularies_include');
  if ($include_vocs) {
    foreach($include_vocs as $include_vocs_id) {
      if (isset($all_vocs[$include_vocs_id])) {
        $vocs[$include_vocs_id] = $all_vocs[$include_vocs_id];
      }
    }
  }
  else {
    $vocs = $all_vocs;
  }

  // remove those the user never wants
  $omit_vocs = _taxonomy_vtn_get_list('taxonomy_vtn_vocabularies_omit');
  if ($omit_vocs) {
    foreach ($omit_vocs as $omit_vocs_id) {
      unset($vocs[$omit_vocs_id]);
    }
  }

  if ( (count($vocs) == 1) && (variable_get('taxonomy_vtn_vocabularies_goto_terms_if_one', 0) == 1) ) {
    // TODO: this does not in any way offers parent/child support
    drupal_goto('taxonomy_vtn/voc/'. key($vocs));
  }

  // Check if the page hasn't already been cached. If not, create and cache it.
  $cache_name = 'taxonomy_vtn_show_vocs';
  if ($group) {
    $cache_name .= '-grp-' . $group;
  }
  if (strlen($cache_name) > 254) {
    // don't cache those things that don't make sense
    $cache_name = NULL;
  }
  if ($cache_name) {
    $cc = cache_get($cache_name);
    $cache_data = $cc->data;
    if ($cache_data && variable_get('taxonomy_vtn_caching', 0) == 1) {
      $output = $cache_data;
      //print 'vocs cache';
      return $output;
    }
  }

  $output = '<div class="taxonomy-vtn-vocabulary-page">';
  if ($vocs) {

    $show_empty_vocs = variable_get('taxonomy_vtn_vocabularies_show_empty_vocs', 1);
    $show_index = variable_get('taxonomy_vtn_vocabularies_show_voc_index', 0);
    $show_count_terms = variable_get('taxonomy_vtn_vocabularies_show_count_terms', 1);
    $show_voc_desc = variable_get('taxonomy_vtn_vocabularies_show_voc_desc', 1);
    $show_hide_descriptions = variable_get('taxonomy_vtn_vocabularies_show_hide_descriptions', 1);
    $count_group_vocabularies =  variable_get('taxonomy_vtn_vocabularies_count_group_vocabularies', 1);
    $count_column_vocs =  variable_get('taxonomy_vtn_vocabularies_count_column_vocs', 2);

    $format = variable_get('taxonomy_vtn_vocabularies_format', TAXONOMY_VTN_DEFAULT_FORMAT);
    if ($format == TAXONOMY_VTN_DEFAULT_FORMAT) {
      $format = FILTER_FORMAT_DEFAULT;
    }

    $first_time = TRUE;

    if ($op == 'groups') {
      foreach ($groups as $g) {
        $blocks[] = array($g);
      }
      // The following hides the master index
      if (!variable_get('taxonomy_vtn_vocabularies_hide_master_index', FALSE) && count($blocks) > 1) {
        $first_time = FALSE;
        $title = variable_get('taxonomy_vtn_vocabularies_master_index', NULL);
        if ($title) {
          drupal_set_title($title);
        }
      }
    }
    else {
      $blocks = array($groups);
    }

    foreach ($blocks as $groups) {
      $arr = array();
      $is_desc = false;
      foreach ($vocs as $vid => $voc_obj) {
        // correct group?
        if ($group) {
          $voc_group = variable_get("taxonomy_vtn_terms_group$vid", '');
          $voc_groups = explode(',', drupal_strtolower($voc_group));
          foreach ($voc_groups as $k => $g) {
            $voc_groups[$k] = trim($g);
          }
          // any group in common?
          if (count(array_intersect($voc_groups, $groups)) == 0) {
            continue;
          }
          $title = $voc_group;
        }

        // TODO: this does not exclude unpublished nodes...
        $terms = taxonomy_get_tree($vid);
        $tcount = count($terms);

        if ($show_count_terms) {
          $count_terms = ' ('. $tcount .')';
        }

        if ($show_voc_desc && $voc_obj->description) {
          $voc_desc = '<div class="taxonomy-vtn-description">'. check_markup($voc_obj->description, $format, FALSE) .'</div>';
          $is_desc = TRUE; // Show/hide description link can be added
        }
        else {
          $voc_desc = '';
        }

        if ($tcount || $show_empty_vocs) {
          $index = drupal_strtoupper(drupal_substr($voc_obj->name, 0, $count_group_vocabularies));

          if (variable_get("taxonomy_vtn_terms_parent_child_links$vid", 0)) {
            $href = 'taxonomy_vtn/voc/'. $vid . '/0/1';
          }
          else {
            $href = 'taxonomy_vtn/voc/'. $vid;
          }

          $arr[$index][] = l($voc_obj->name, $href) . $count_terms . $voc_desc;
        }
      }
      if ($group && $title) {
        if ($first_time) {
          drupal_set_title($title);
          $first_time = FALSE;
        }
        else {
          $output .= '<h2>' . $title . '</h2>';
        }
      }

      // change locale to sort
      if (variable_get('taxonomy_vtn_use_setlocale', 1) == 1 && variable_get('taxonomy_vtn_server_support_setlocale', 0) == 1) {
        $my_locale = variable_get('taxonomy_vtn_locale_code', 'en_US.UTF8');
        setlocale(LC_ALL, $my_locale);
        ksort($arr, SORT_LOCALE_STRING);
        // set locale back to default
        setlocale(LC_ALL, NULL); // without this count($arr) not work properly
      }
      else {
        ksort($arr); //--- this not support locales
      }


      $attr = $show_index != 0 ? array() : array('class' => 'simple-list');
      $cnt = ceil(count($arr) / $count_column_vocs);
      if ($cnt <= 0) {
        $cnt = 1;
      }
      // reset the cells
      for ($k = 0; $k < $count_column_vocs; ++$k) {
        $cell = 'cell' . ++$k;
        $$cell = '';
      }
      $k = 0;
      $col = 0;
      foreach ($arr as $i => $t) {
        if ($k == 0 || ($k % $cnt) == 0 || $k == $cnt) {
          $cell = 'cell'. ++$col;
        }
        $$cell .= theme('item_list', $t, $show_index != 0 ? $i : NULL, 'ul', $attr);
        ++$k;
      }

      if ($k) {
        // prepare cells and their width
        $xcells = array();
        for ($num = 1; $num <= $col; ++$num) {
          $xcell = 'cell'. $num;
          $xcells[] = array('data' => $$xcell, 'style' => 'width:'. (100 / $col) .'%');
        }
        $row = array($xcells);

        if ($show_voc_desc && $is_desc && $show_hide_descriptions) {
          $output .= '<div class="taxonomy-vtn-navigation">';
          $output .= '<a class="show-hide-desc" href="javascript:taxonomy_vtn_show_hide_desc(\'vocabularies\');">'. t('Show / Hide descriptions') .'</a>';
          $output .= '</div>';
        }

        $output .= theme('table', array(), $row, array('class' => 'taxonomy-vtn-vocabularies', 'id' => 'taxonomy_vtn_vocabularies'));
      }
      else {
        $output .= '<p class="taxonomy-vtn-no-data-info">';
        $output .= t('No data to display. The option to not show empty vocabularies is certainly selected.');
        $output .= '</p>';
      }
    }
  }
  else {
    $output .= '<p class="taxonomy-vtn-no-data-info">';
    $output .= t('No data to display. There is no vocabularies or they all are excluded from display.');
    $output .= '</p>';
  }

  $output .= '</div>'; // close tag <div class="taxonomy-vtn-vocabulary-page">

  // Cache the fully rendered page in case of aggressive caching
  if (variable_get('taxonomy_vtn_caching', 0) == 1 && $cache_name) {
    cache_set($cache_name, $output);
  }

  return $output;
}

/**
 * Compare two terms.
 */
function _taxonomy_vtn_sort($a, $b, $locale = FALSE) {
  static $numeric_sort;

  // first compare weights
  $weight_cmp = $a['obj']->weight - $b['obj']->weight;
  if ($weight_cmp != 0) {
    return $weight_cmp;
  }

  if (!isset($numeric_sort)) {
    $numeric_sort = $a['obj']->numeric_sort - 1;
  }
  // weights are equal, check name
  $na = $a['obj']->clean_name;
  $nb = $b['obj']->clean_name;

  if ($numeric_sort >= 0) {
    $wa = explode(' ', $na);
    $wb = explode(' ', $nb);
    if (is_numeric($wa[$numeric_sort]) && is_numeric($wb[$numeric_sort])) {
      $number = $wa[$numeric_sort] - $wb[$numeric_sort];
      if ($number != 0) {
        return $number;
      }
    }
    // if equal try the full name alphabetically
  }

  if ($locale) {
    return strcoll($na, $nb);
  }
  return strcmp($na, $nb);
}

/**
 * Compare two terms respecting the locale setup.
 */
function _taxonomy_vtn_sort_locale($a, $b) {
  return _taxonomy_vtn_sort($a, $b, TRUE);
}

/**
 * Implementation of taxonomy_vtn_show_terms().
 */
function taxonomy_vtn_show_terms($vocid, $parent = 0, $max_depth = NULL, $params = NULL) {
  if (!is_object($params)) {
    $params = new stdClass;
    $params->check_omit = TRUE;
    $params->title_mode = 'title';
    $params->show_voc_desc = TRUE;
  }
  if ($parent === 'ALPHA') {
    $parent = 0;
    // we limit the number of letters to 5 (for the cache name, in part, at least)
    $letter = drupal_strtolower(substr($max_depth, 0, 5));
    $max_depth = NULL;
    $letter_len = strlen($letter);
    if ($letter_len == 0) {
      // ignore empty requests
      $letter = NULL;
    }
  }
  else {
    $letter_len = 0;
    $letter = NULL;
  }

  if ($params->check_omit) {
    // check for excluded voc_id
    $omit_vocs = _taxonomy_vtn_get_list('taxonomy_vtn_vocabularies_omit');
    if ($omit_vocs) {
      if (in_array($vocid, $omit_vocs)) {
        $vocid = NULL;
      }
    }
  }

  if (!is_numeric($vocid)) {
    if ($params->always_return) {
      return FALSE;
    }
    drupal_set_message(t('Please select a vocabulary first'));
    drupal_goto('taxonomy_vtn');
  }

  $own_vid = (int)$vocid;
  $voc_obj = taxonomy_vocabulary_load($own_vid);
  if (!$voc_obj) {
    if ($params->always_return) {
      return FALSE;
    }
    drupal_set_title(t('Bad vocabulary identifier (!voc_id)', array('!voc_id' => $own_vid)));
    $output  = '<p class="taxonomy-vtn-no-data-info">';
    $output .= t('No data to display. You probably have no vocabulary with vid = !voc_id', array('!voc_id' => $own_vid));
    $output .= '</p>';
    $terms_navigation = '';
    if (variable_get('taxonomy_vtn_terms_show_back_to_voc', 1) == 1) {
      $where_back = t('vocabularies');
      if (variable_get('taxonomy_vtn_user_friendly_titles', 1) == 1) {
        $where_back = t('master index');
      }
      $terms_navigation = '<span class="taxonomy-vtn-back-button">'. l('<< '. t('Back to') .' '. $where_back, 'taxonomy_vtn') .'</span>';
      $output .= '<div class="taxonomy-vtn-navigation">'. $terms_navigation .'</div>';
    }
    return $output;
  }
  // vocabulary vid is ok, lets do it

  switch ($params->title_mode) {
  //case 'none':
  default:
    break;

  case 'inline': // inline title
  case 'title': // drupal title
    if (variable_get('taxonomy_vtn_user_friendly_titles', 1) == 1) {
      $title = t('Terms in @vocabulary', array('@vocabulary' => $voc_obj->name));
    }
    else {
      // in this case, use the vocabulary name as is
      $title = $voc_obj->name;
    }
    if ($params->title_mode == 'title') {
      drupal_set_title($title);
      $title = '';
    }
    else {
      $title = '<h3>' . $title . '</h3>';
    }
    break;

  }

  // Check if the page hasn't already been cached. If not, create and cache it.
  if (!$params->no_cache) {
    $cache_name = 'taxonomy_vtn_show_terms_' . $own_vid;
    if (!is_null($parent)) {
      // avoid tainted params
      $parent = (int)$parent;
    }
    if ($parent) {
      $cache_name .= 'p' . $parent;
    }
    if (!is_null($max_depth)) {
      // avoid tainted params
      $max_depth = (int)$max_depth;
    }
    if ($max_depth > 0) {
      if ($max_depth > 10) {
        // security issue, otherwise people could request an "infinite" number
        // of pages creating a real large cache... and allowing a depth of more
        // than 10 is probably not too sensical
        $max_depth = 10;
      }
      $cache_name .= 'md' . $max_depth;
    }
    else {
      $max_depth = NULL;
    }
    if ($letter) {
      $cache_name .= 'l-' . $letter;
    }
    $cc = cache_get($cache_name);
    $cache_data = $cc->data;
    if ($cache_data && variable_get('taxonomy_vtn_caching', 0) == 1) {
      $output = $cache_data;
      //print 'terms cache';
      return $output;
    }
  }

  $format = variable_get('taxonomy_vtn_vocabularies_format', TAXONOMY_VTN_DEFAULT_FORMAT);
  if ($format == TAXONOMY_VTN_DEFAULT_FORMAT) {
    $format = FILTER_FORMAT_DEFAULT;
  }

  if (!isset($params->long_description)) {
    if ($parent) {
      // get description from the parent term
      $params->long_description = variable_get("taxonomy_vtn_term_long_description$parent", '');
    }
    else {
      // get description from the vocabulary
      $params->long_description = variable_get("taxonomy_vtn_terms_long_description$own_vid", '');
    }
  }
  if (!isset($params->parent_child_links)) {
    $params->parent_child_links = variable_get("taxonomy_vtn_terms_parent_child_links$own_vid", 0);
  }
  if (!isset($params->show_parent_term)) {
    $params->show_parent_term = variable_get("taxonomy_vtn_terms_show_parent_term$own_vid", 0);
  }
  if (!isset($params->show_nodes)) {
    $params->show_nodes = variable_get("taxonomy_vtn_terms_show_nodes$own_vid", 0);
  }
  if (!isset($params->show_empty_terms)) {
    $params->show_empty_terms = variable_get("taxonomy_vtn_terms_show_empty_terms$own_vid", 1);
  }
  if (!isset($params->show_index)) {
    $params->show_index = variable_get("taxonomy_vtn_terms_show_terms_index$own_vid", 1);
  }
  if (!isset($params->show_count_nodes)) {
    $params->show_count_nodes = variable_get("taxonomy_vtn_terms_show_count_nodes$own_vid", 1);
  }
  if (!isset($params->show_term_desc)) {
    $params->show_term_desc = variable_get("taxonomy_vtn_terms_show_term_desc$own_vid", 1);
  }
  if (!isset($params->show_synonyms)) {
    $params->show_synonyms = variable_get("taxonomy_vtn_terms_show_synonyms$own_vid", 1);
  }
  if (!isset($params->count_group_terms)) {
    $params->count_group_terms = variable_get("taxonomy_vtn_terms_count_group_terms$own_vid", 1);
  }
  if (!isset($params->count_column_terms)) {
    $params->count_column_terms = variable_get("taxonomy_vtn_terms_count_column_terms$own_vid", 2);
  }
  if (!isset($params->term_goto)) {
    $params->term_goto = variable_get("taxonomy_vtn_terms_goto$own_vid", 'nodes');
  }
  if (!isset($params->show_back_to_voc)) {
    $params->show_back_to_voc = variable_get("taxonomy_vtn_terms_show_back_to_voc$own_vid", 1);
  }
  if (!isset($params->show_hide_descriptions)) {
    $params->show_hide_descriptions = variable_get("taxonomy_vtn_terms_show_hide_descriptions$own_vid", 1);
  }
  if (!isset($params->show_related)) {
    $params->show_related = variable_get("taxonomy_vtn_terms_show_related$own_vid", 0);
  }
  if (!isset($params->show_quick_index)) {
    $params->show_quick_index = variable_get("taxonomy_vtn_terms_show_quick_index$own_vid", 0);
  }
  if ($letter) {
    // we really don't need an index if this is a single letter!
    $params->show_quick_index = FALSE;
  }
  if (!isset($params->break_quick_index)) {
    $params->break_quick_index = variable_get("taxonomy_vtn_terms_break_quick_index$own_vid", 0);
  }
  if (!isset($params->show_statistics)) {
    $params->show_statistics = variable_get("taxonomy_vtn_terms_show_statistics$own_vid", 0);
  }
  $numeric_sort = variable_get("taxonomy_vtn_terms_numeric_sort$own_vid", 0);

  if (!isset($params->ignored_chars)) {
    $params->ignored_chars = variable_get("taxonomy_vtn_terms_ignored_chars$own_vid", '');
  }
  if ($params->ignored_chars) {
    // transform to array
    $params->ignored_chars_array = str_split($params->ignored_chars);
    $params->ignored_chars_empty = array();
    foreach ($params->ignored_chars_array as $k => $ignore) {
      $params->ignored_chars_empty[$k] = '';
    }
  }

  $format = variable_get("taxonomy_vtn_terms_format$own_vid", TAXONOMY_VTN_DEFAULT_FORMAT);
  if ($format == TAXONOMY_VTN_DEFAULT_FORMAT) {
    $format = FILTER_FORMAT_DEFAULT;
  }

  $stats = '';

  $output = '<div class="taxonomy-vtn-term-page">';
  $output .= $title; // for inline titles

  if ($params->long_description) {
    $output .= '<div class="taxonomy-vtn-description">'. check_markup($params->long_description, $format, FALSE) .'</div>';
  }
  else if ($voc_obj->description && $params->show_voc_desc) {
    $output .= '<div class="taxonomy-vtn-description">'. check_markup($voc_obj->description, $format, FALSE) .'</div>';
  }

  // TODO: for depth use:  if ( $terms = taxonomy_get_tree($own_vid,0,-1,3) )
  $terms = taxonomy_get_tree($own_vid, $parent, -1, $max_depth);
  if ($letter) {
    // keep only the terms that match
    foreach ($terms as $k => $term) {
      if (drupal_strtolower(substr($term->name, 0, $letter_len)) != $letter) {
        unset($terms[$k]);
      }
    }
  }
  if ($params->show_parent_term && $parent > 0) {
    // the following loop sorts the terms so we can safely append
    $terms[] = taxonomy_get_term($parent);
  }
  if (count($terms) > 0) {
    $arr = array();
    $arr_terms = array();
    $row = array();
    $is_desc = false;

    // exclude some terms_id (use global and local term numbers)
    $omit_terms = _taxonomy_vtn_get_list('taxonomy_vtn_terms_omit',
                                         "taxonomy_vtn_terms_omit$own_vid");
    if (!$omit_terms) {
      // to make sure it works, use an empty array in this one case
      $omit_terms = array();
    }

    // only include some terms_id (use global and local term numbers)
    $include_terms = _taxonomy_vtn_get_list('taxonomy_vtn_terms_include',
                                            "taxonomy_vtn_terms_include$own_vid");

    // prepare own full structure with terms and synonyms and link to them
    $related_count = 0;
    $referenced_nodes_count = 0;
    $referenced_children_count = 0;
    if (!isset($params->show_edit_link)) {
      $params->show_edit_link = user_access('administer taxonomy_vtn')
        && user_access('administer taxonomy')
        && variable_get('taxonomy_vtn_edit_terms', 0) == 1;
    }
    else {
      $params->show_edit_link = $params->show_edit_link
        && user_access('administer taxonomy_vtn')
        && user_access('administer taxonomy');
    }
    $edit_link = '';
    module_load_include('inc.php', 'taxonomy_vtn', 'taxonomy_vtn_overwrites');
    foreach ($terms as $term) {

      // include/exclude user specified terms and avoid duplicates
      if (($include_terms === NULL || in_array($term->tid, $include_terms)) &&
          !in_array($term->tid, $omit_terms)) {
        // avoid handling the same term twice
        $omit_terms[] = $term->tid;

        $ccount = 0; // by default, assume that we don't have children on this term
        $term_goto_path = '';
        if ($params->parent_child_links && $term->tid != $parent) {
          // if this term has children, then link to them instead
          $children = taxonomy_get_tree($own_vid, $term->tid, -1, 1);
          if ($children) {
            $term_goto_path = 'taxonomy_vtn/voc/' . $own_vid . '/' . $term->tid . '/1';
            // count the children
            $ccount = count($children);
            if ($params->show_parent_term) {
              // NOTE: Is that really correct? The counter should tell you how many
              //       entries you will see and the parent will be repeated...
              $ccount += 1;
            }
          }
        }

        if (!$term_goto_path) {
          switch ($params->term_goto) {
          //case 'nodes':
          default:
            $term_goto_path = 'taxonomy_vtn/term/'. $term->tid;
            if ($parent) {
              $term_goto_path .= '/'. $parent;
            }
            $tcount = _taxonomy_vtn_count_nodes(array($term->tid), 'all');
            break;

          case 'taxonomy_term':
            $term_goto_path = taxonomy_term_path($term);
            $tcount = _taxonomy_vtn_count_nodes(array($term->tid), 0);
            break;

          case 'taxonomy_term_all':
            $term_goto_path = taxonomy_term_path($term) .'/all';
            $tcount = _taxonomy_vtn_count_nodes(array($term->tid), 'all');
            break;

          case 'taxonomy_view':
            $term_goto_path = 'taxonomy_view/' . $own_vid . '/' . $term->tid;
            $tcount = _taxonomy_vtn_count_nodes(array($term->tid), 'all');
            break;

          }
        }
        else {
          // whether or not we have children, we need to count the nodes!
          switch ($params->term_goto) {
          default:
            $tcount = _taxonomy_vtn_count_nodes(array($term->tid), 'all');
            break;

          case 'taxonomy_term':
            $term_goto_path = taxonomy_term_path($term);
            $tcount = _taxonomy_vtn_count_nodes(array($term->tid), 0);
            break;

          }
        }

        if ($ccount || $tcount || $params->show_empty_terms) {
          // add the count when available and requested
          if ($params->show_count_nodes && $parent && ($ccount > 0 || $tcount > 0)) {
            if ($ccount == 0) {
              $count_nodes = ' ('. $tcount .')';
            }
            else {
              $count_nodes = ' ('. $ccount .'/'. $tcount .')';
            }
            $referenced_nodes_count += $tcount;
            $referenced_children_count += $ccount;
          }
          else if ($params->show_count_nodes && $tcount > 0) {
            $count_nodes = ' ('. $tcount .')';
            $referenced_nodes_count += $tcount;
          }
          else {
            $count_nodes = '';
          }

          $term_desc = '';
          if ($params->show_term_desc && $term->description) {
            $term_desc = '<div class="taxonomy-vtn-description">'. check_markup($term->description, $format, FALSE) .'</div>';
            $is_desc = true;
          }

          if ($params->show_edit_link) {
            $edit_link = ' [' . l(t('edit'), 'admin/content/taxonomy/edit/term/' . $term->tid,
                           array('query' => array('destination' => 'taxonomy_vtn/voc/' . $own_vid)))
                        . ']';
          }

          if (is_array($params->ignored_chars_array)) {
            $term->clean_name = str_replace($params->ignored_chars_array, $params->ignored_chars_empty, $term->name);
          }
          else {
            $term->clean_name = $term->name;
          }
          $term->numeric_sort = $numeric_sort;
          $arr_terms[$term->name]['obj'] = $term;
          $arr_terms[$term->name]['term'][] = l($term->name, $term_goto_path) . $count_nodes . $edit_link . $term_desc;
          // if is not empty term or we show empty terms
          // and we will show synonyms then get for this
          if ($params->show_synonyms) {
            $synonyms = taxonomy_get_synonyms($term->tid);
            foreach ($synonyms as $synonym_name) {
              // $synonym_term = taxonomy_get_synonym_root($synonym_name);
              // all synonyms have a target - this term
	      if ($letter && drupal_strtolower(substr($synonym_name, 0, $letter_len)) != $letter) {
		// looks real weird to have other columns when you ask
		// for one specific letter to be displayed, so we skip
		// any synonym that does not match; what we're missing
		// are all the other terms with synonyms that start with
		// $letter...
	        continue;
	      }
              $syn_obj = new stdClass;
              $syn_obj->name = $synonym_name;
              if (is_array($params->ignored_chars_array)) {
                $syn_obj->clean_name = str_replace($params->ignored_chars_array, $params->ignored_chars_empty, $synonym_name);
              }
              else {
                $syn_obj->clean_name = $synonym_name;
              }
              $syn_obj->weight = $term->weight;
              $syn_obj->numeric_sort = $numeric_sort;
              $arr_terms[$synonym_name]['obj'] = $syn_obj;
              $arr_terms[$synonym_name]['synonym'][] = l($term->name, $term_goto_path);
            }
          }

          if ($params->show_related) {
            // prepare related terms
            $related = taxonomy_get_related($term->tid);
            foreach ($related as $rel) {

              switch ($params->term_goto) {
              //case 'nodes':
              default:
                $rel_goto_path = 'taxonomy_vtn/term/'. $rel->tid;
                if ($parent) {
                  $rel_goto_path .= '/'. $parent;
                }
                break;

              case 'taxonomy_term':
                $rel_goto_path = taxonomy_term_path($rel);
                break;

              case 'taxonomy_term_all':
                $rel_goto_path = taxonomy_term_path($rel) .'/all';
                break;

              case 'taxonomy_view':
                $rel_goto_path = 'taxonomy_view/' . $own_vid . '/' . $rel->tid;
                break;

              }

              $relatedx[$term->name][] = l($rel->name, $rel_goto_path);
              $related_count++;
            }
          } // show realted
        } // has terms or show empty true
      } // exclude end
    } // end foreach terms as term prepare


    $my_locale = variable_get('taxonomy_vtn_locale_code', 'en_US.UTF8');

    // change locale to sort
    if (variable_get('taxonomy_vtn_use_setlocale', 1) == 1 && variable_get('taxonomy_vtn_server_support_setlocale', 0) == 1 ) {
      setlocale(LC_ALL, $my_locale);
      usort($arr_terms, '_taxonomy_vtn_sort_locale');
      // set locale back to default
      setlocale(LC_ALL, NULL); // without this count($arr) does not work properly
    }
    else {
      usort($arr_terms, '_taxonomy_vtn_sort'); //--- no specific language support (works for English)
    }

    $term_count = 0;
    $synonym_count = 0;

    // Now we build an index with links to proper terms for synonyms
    foreach ($arr_terms as $types) {
      $name = $types['obj']->name;
      $index = drupal_strtoupper(drupal_substr($types['obj']->clean_name, 0, $params->count_group_terms));
      if ($numeric_sort == 1 && is_numeric($index)) {
        // otherwise the numerical order won't do much good!
        $index = '#';
      }
      foreach ($types as $type => $links) {
        switch ($type) {
        case 'term':
          $term_count++;
          // if some related terms exist, show them
          $ree = '';
          if ($params->show_related && $relatedx[$name]) {
            $ree = '<div class="taxonomy-vtn-related-terms">'. t('Related terms') .': '. implode(', ', $relatedx[$name]) .'</div>';
          }

          foreach ($links as $link) { // there may be more than one
            $arr[$index][] = $link . $ree;
          }
          break;

        case 'synonym':
          $synonym_count++;
          $arr[$index][] = $name .'<div class="taxonomy-vtn-synonyms">'. t('Synonyms') .': '. implode(', ', $links) .'</div>';
          break;

        }
      }
    } // end foreach arr_terms


    // sort array key (index like A B C .. etc.)
    // change locale to sort
    if (variable_get('taxonomy_vtn_use_setlocale', 1) == 1 && variable_get('taxonomy_vtn_server_support_setlocale', 0) == 1) {
      setlocale(LC_ALL, $my_locale);
      ksort($arr, SORT_LOCALE_STRING);
      // set locale back to default
      setlocale(LC_ALL, NULL); // without this count($arr) does not work properly
    }
    else {
      ksort($arr); //--- no support for languages
    }

    // defines where we need to add a <br/> for the top letters index
    $href = null;
    if ($params->break_quick_index && $params->show_quick_index) {
      $cut_href = ceil(count($arr) / 2);
    }
    else {
      $cut_href = 0;
    }
    $letter_href = '';

    // arrange the terms by letters
    $cnt = ceil(count($arr) / $params->count_column_terms);
    $k = 0;
    $col = 0;
    foreach ($arr as $i => $t) {
      if ($k == 0 || ($k % $cnt) == 0 || $k == $cnt) {
        $cell = 'cell'. ++$col;
      }
      if($params->show_index == 0) {
        $$cell .= theme('item_list', $t, NULL, 'ul', array('class' => 'simple-list'));
      }
      else {
        if ($params->show_quick_index) {
          if ($cut_href > 0) {
            --$cut_href;
            if ($cut_href == 0) {
              $href .= '<br/>';
            }
          }
          // TODO: we would need to enhance the test and make sure that $i is a valid character for HREF
          switch ($i) {
          case '&': $href_letter = 'amp'; break;
          case '"': $href_letter = 'quot'; break;
          case '\'': $href_letter = 'apos'; break;
          default: $href_letter = $i; break;
          }
          $href .= '<a class="taxonomy-vtn-index-link" href="#name-taxonomy-vtn-term-' . $href_letter . '">' . $i . '</a> ';
          $letter_link = l($i, 'taxonomy_vtn/alpha/' . $own_vid . '/' . check_plain($i),
            array(
              'attributes' => array(
                'class' => 'taxonomy-vtn-index-anchor',
                'name' => 'name-taxonomy-vtn-term-' . $href_letter,
              )
            )
          );
        }
        else {
          $letter_link = '<span class="taxonomy-vtn-index-anchor">' . $i . '</span>';
        }
        $$cell .= theme('item_list', $t, $letter_link, 'ul');
      }
      ++$k;
    }

    if ($k) {
      // prepare cells and their width
      for ($num = 1; $num <= $col; ++$num) {
        $xcell = 'cell'. $num;
        $xcells[] = array('data' => $$xcell, 'style' => 'width:'. (100 / $col) .'%');
      }
      $row[] = $xcells;

      $terms_navigation = array();
      _taxonomy_vtn_set_breadcrumb($parent, $voc_obj, FALSE);

      if ($params->show_term_desc && $is_desc && $params->show_hide_descriptions) {
        $terms_navigation[] = '<a class="show-hide-desc" href="javascript:taxonomy_vtn_show_hide_desc(\'terms\');">'. t('Show / Hide descriptions') .'</a>';
      }

      if ($params->show_back_to_voc || $params->show_term_desc) {
        $output .= '<div class="taxonomy-vtn-navigation">'. implode(' &nbsp; | &nbsp; ', $terms_navigation) .'</div>';
      }
      if ($href) {
        $output .= '<div class="taxonomy-vtn-references">' . $href . '</div>';
      }

      $output .= theme('table', array(), $row, array('class' => 'taxonomy-vtn-terms', 'id' => 'taxonomy_vtn_terms'));

      if ($params->show_statistics) {
        if ($parent) {
          $stats = '<div class="taxonomy-vtn-statistics">' . t('!lc letters, !tc terms, !sc synonyms, !rc related terms, !nc references to nodes, !cc references to children',
                     array('!lc' => $k,
                           '!tc' => $term_count,
                           '!sc' => $synonym_count,
                           '!rc' => $related_count,
                           '!nc' => $referenced_nodes_count,
                           '!cc' => $referenced_children_count)) . '</div>';
        }
        else {
          $stats = '<div class="taxonomy-vtn-statistics">' . t('!lc letters, !tc terms, !sc synonyms, !rc related terms, !nc references to nodes',
                     array('!lc' => $k,
                           '!tc' => $term_count,
                           '!sc' => $synonym_count,
                           '!rc' => $related_count,
                           '!nc' => $referenced_nodes_count)) . '</div>';
        }
      }
    }
    else {
      $output .= '<p class="taxonomy-vtn-no-data-info">';
      $output .= t('No data to display. You probably selected the option to avoid empty terms.');
      $output .= '</p>';
      $terms_navigation = '';
      if ($params->show_back_to_voc) {
        $where_back = t('vocabularies');
        if (variable_get('taxonomy_vtn_user_friendly_titles', 1) == 1) {
          $where_back = t('master index');
        }
        $terms_navigation = '<span class="taxonomy-vtn-back-button">'. l('<< '. t('Back to') .' '. $where_back, 'taxonomy_vtn') .'</span>';
        $output .= '<div class="taxonomy-vtn-navigation">'. $terms_navigation .'</div>';
      }
    }
  }// end if terms
  else {
    $output .= '<p class="taxonomy-vtn-no-data-info">';
    $output .= t('No data to display. This vocabulary is probably empty.');
    $output .= '</p>';
    $terms_navigation = '';
    if ($params->show_back_to_voc) {
      $where_back = t('vocabularies');
      if (variable_get('taxonomy_vtn_user_friendly_titles', 1) == 1) {
        $where_back = t('master index');
      }
      $terms_navigation = '<span class="taxonomy-vtn-back-button">'. l('<< '. t('Back to') .' '. $where_back, 'taxonomy_vtn') .'</span>';
      $output .= '<div class="taxonomy-vtn-navigation">'. $terms_navigation .'</div>';
    }
  }

  if ($parent && $params->show_nodes) {
    $output .= taxonomy_vtn_show_nodes($parent, NULL, TRUE);
  }

  $output .= $stats;
  $output .= '</div>'; // closing tag <div class="taxonomy-vtn-term-page">

  // Cache the fully rendered page in case of aggressive caching
  if (!$params->no_cache && variable_get('taxonomy_vtn_caching', 0) == 1) {
    cache_set($cache_name, $output);
  }

  return $output;
}

/**
 * Display a page using the name of the vocabulary instead of the ID
 */
function taxonomy_vtn_show_terms_by_name($voc_name) {
  $vocid = db_result(db_query(db_rewrite_sql("SELECT v.vid FROM {vocabulary} v WHERE LOWER(v.name) = '%s'", 'v', 'vid'), drupal_strtolower($voc_name)));
  if ($vocid) {
    return taxonomy_vtn_show_terms($vocid);
  }

  $output = '<div class="taxonomy-vtn-term-page">';
  $output .= '<p class="taxonomy-vtn-no-data-info">';
  $output .= t('Unknown vocabulary ("%voc_name").', array('%voc_name' => $voc_name));
  $output .= '</p>';
  $terms_navigation = '';
  if ($params->show_back_to_voc) {
    $where_back = t('vocabularies');
    if (variable_get('taxonomy_vtn_user_friendly_titles', 1) == 1) {
      $where_back = t('master index');
    }
    $terms_navigation = '<span class="taxonomy-vtn-back-button">'. l('<< '. t('Back to') .' '. $where_back, 'taxonomy_vtn') .'</span>';
    $output .= '<div class="taxonomy-vtn-navigation">'. $terms_navigation .'</div>';
  }
  $output .= '</div>';
  return $output;
}

/**
 * Implementation of taxonomy_vtn_show_nodes().
 */
function taxonomy_vtn_show_nodes($arg = '', $parent = NULL, $no_errors = FALSE) {

  // check for globally excluded voc_id
  $omit_terms = _taxonomy_vtn_get_list('taxonomy_vtn_terms_omit');
  if ($omit_terms) {
    if (in_array($arg, $omit_terms)) {
      $arg = NULL;
    }
  }

  if (!is_numeric($arg)) {
    drupal_set_message(t('Please select a vocabulary first'));
    drupal_goto('taxonomy_vtn');
  }

  $own_tid = (int)$arg;
  $term_obj = taxonomy_get_term($own_tid);
  if (!$term_obj) {
    if ($no_errors) {
      return '';
    }

    drupal_set_title(t('Bad term id'));
    $output  = '<p class="taxonomy-vtn-no-data-info">';
    $output .= t('No data to display. You probably don\'t have a term with tid = !term_id.', array('!term_id' => $own_tid));
    $output .= '</p>';

    $terms_navigation = '';
    if (variable_get('taxonomy_vtn_terms_show_back_to_voc', 1) == 1) {
      $where_back = t('Back to vocabularies');
      if (variable_get('taxonomy_vtn_user_friendly_titles', 1) == 1) {
        $where_back = t('Back to master index');
      }
      $terms_navigation = '<span class="taxonomy-vtn-back-button">'. l('<< '. $where_back, 'taxonomy_vtn') .'</span>';
      $output .= '<div class="taxonomy-vtn-navigation">'. $terms_navigation .'</div>';
    }
    return $output;
  }

  if (variable_get('taxonomy_vtn_user_friendly_titles', 1) == 1) {
    $title = t('Nodes of term @term_name', array('@term_name' => $term_obj->name));
  }
  else {
    $title = $term_obj->name;
  }
  drupal_set_title($title);

  // the variables are saved on a per vocabulary basis, get the identifier
  $own_vid = $term_obj->vid;

  $use_pager = (bool)variable_get("taxonomy_vtn_nodes_use_pager$own_vid", FALSE);
  if ($use_pager) {
    // with the pager we need to cache pages one by one
    $page = '_page'. isset($_GET['page']) ? $_GET['page'] : '0';
  }
  else {
    $page = '';
  }

  $cache_name = 'taxonomy_vtn_show_nodes_' . $own_tid;
  if ($page) {
    $cache_name .= 'p' . $page;
  }
  if ($no_errors) {
    $cache_name .= 'no_errors';
  }

  // Check if the page hasn't already been cached. If not, create and cache it.
  $cc = cache_get($cache_name);
  $cache_data = $cc->data;
  if ($cache_data && variable_get('taxonomy_vtn_caching', 0) == 1) {
    $output = $cache_data;
    //print 'nodes cache';
    return $output;
  }

  if ($use_pager) {
    $links_per_page = variable_get("taxonomy_vtn_nodes_links_per_page$own_vid", 10);
  }
  else {
    $links_per_page = 0;
  }
  $show_count_comments = variable_get("taxonomy_vtn_nodes_show_count_comments$own_vid", 1);
  $count_column_nodes = variable_get("taxonomy_vtn_nodes_count_column_nodes$own_vid", 2);
  $show_empty_count_comments = variable_get("taxonomy_vtn_nodes_show_empty_count_comments$own_vid", 0);
  $show_index = variable_get("taxonomy_vtn_nodes_show_nodes_index$own_vid", 0);
  $show_back_to_terms = variable_get("taxonomy_vtn_nodes_show_back_to_terms$own_vid", 1);

  // TODO: settings for depth , probably use level of terms ?
  module_load_include('inc.php', 'taxonomy_vtn', 'taxonomy_vtn_overwrites');
  $nodes = _taxonomy_vtn_select_nodes(array($own_tid), $operator = 'or', $depth = 'all', $use_pager, $order = 'n.title, n.sticky DESC', $links_per_page);
  while ($node = db_fetch_object($nodes)) {
    $node = node_load($node->nid);
    $title = ltrim($node->title);
    if (strlen($title) == 0) {
      $index = '&mdash;';
    }
    else {
      $first_letter = drupal_substr($title, 0, 1);
      if ($first_letter == '&') {
        // HTML entity, keep as is
        $index = preg_replace('/;.*/', ';', $title);
      }
      else {
        // TODO: cut "special" chars (does it really cut UTF-8 badly? TBD)
        $index = drupal_strtoupper($first_letter);
      }
    }
    //print_r($node);
    if ($show_count_comments) {
      if ( $node->comment_count || $show_empty_count_comments) {
        $count_comments = ' ('. format_plural($node->comment_count, '1 comment', '@count comments') .')';
      }
      else {
        $count_comments = '';
      }
    }
    $arr[$index][] = l($node->title, 'node/'. $node->nid) . $count_comments;
    // for <li> style .... $arr[$index][] = array('data' => l($node->title,'node/'.$node->nid) . $count_comments, 'style' => '');
  }

  $output = '<div class="taxonomy-vtn-node-page">';
  if ( count($arr) > 0 ) {

    $my_locale = variable_get('taxonomy_vtn_locale_code', 'en_US.UTF8');

    // change locale to sort
    if (variable_get('taxonomy_vtn_use_setlocale', 1) == 1 && variable_get('taxonomy_vtn_server_support_setlocale', 0) == 1) {
      setlocale(LC_ALL, $my_locale);
      ksort($arr, SORT_LOCALE_STRING);
      // set locale back to default
      setlocale(LC_ALL, NULL); // without this count($arr) not work properly
    }
    else {
      ksort($arr); //--- this not support locales
    }

    $attr = $show_index != 0 ? array() : array('class' => 'simple-list');
    $cnt = ceil(count($arr)/$count_column_nodes);
    $k = 0; $col = 0;
    foreach ($arr as $i => $t) {
      if ($k == 0 || ($k%$cnt) == 0 || $k == $cnt) {
        $cell = 'cell'. ++$col;
      }
      $$cell .= theme('item_list', $t, $show_index != 0 ? $i : NULL, 'ul', $attr);
      ++$k;
    }

    // prepare cells and their width
    $ile = $col < $count_column_nodes ? $col : $count_column_nodes;
    for ($num=1; $num <= $ile; ++$num) {
      $xcell = 'cell'. $num;
      $xcells[] = array('data' => $$xcell, 'style' => 'width:'. (100/$ile) .'%');
    }
    $row[] = $xcells;

    $output .= '<div class="taxonomy-vtn-node-description">'. $term_obj->description .'</div>';

    $voc_obj = taxonomy_vocabulary_load($own_vid);
    if ($voc_obj && !$no_errors) {
      if ($parent) {
        _taxonomy_vtn_set_breadcrumb($parent, $voc_obj, TRUE);
      }
      else {
        $breadcrumb[] = l(t('Home'), '<front>');
        $breadcrumb[] = l(variable_get('taxonomy_vtn_vocabularies_master_index', t('Master index')), 'taxonomy_vtn');
        $breadcrumb[] = l($voc_obj->name, 'taxonomy_vtn/voc/' . $own_vid);
        drupal_set_breadcrumb($breadcrumb);
      }
    }

    $output .= theme('table', array(), $row, array('class' => 'taxonomy-vtn-nodes', 'id' => 'taxonomy_vtn_nodes'));
  }
  else if (!$no_errors) {
    $output .= '<p class="taxonomy-vtn-no-data-info">';
    $output .= t('No data to display. This term is probably not used by any node.');
    $output .= '</p>';
    $nodes_navigation = '';
    if ($show_back_to_terms) {
      $where_back = t('terms');
      if (variable_get('taxonomy_vtn_user_friendly_titles', 1) == 1) {
        $where_back = t('master index');
      }
      $nodes_navigation = '<span class="taxonomy-vtn-back-button">'. l('<< '. t('Back to') .' '. $where_back, 'taxonomy_vtn/voc/'. $term_obj->vid) .'</span>';
      $output .= '<div class="taxonomy-vtn-navigation">'. $nodes_navigation .'</div>';
    }
  }

  $output .= '</div>';  // close tag <div class="taxonomy-vtn-node-page">
  if ($use_pager) {
    $output .= theme('pager');
  }

  // Cache the fully rendered page in case of aggressive caching
  if (variable_get('taxonomy_vtn_caching', 0) == 1) {
    cache_set($cache_name, $output);
  }

  return $output;
}

/**
 * Display a page using a vocabulary & term name.
 */
function taxonomy_vtn_show_nodes_by_name($voc_name, $term_name) {
  $terms = taxonomy_get_term_by_name($term_name);

  switch (count($terms)) {
  case 0:
    $output .= '<p class="taxonomy-vtn-no-data-info">';
    $output .= t('No data to display. This term ("%term_name") does not exist.', array('%term_name' => $term_name));
    $output .= '</p>';
    $nodes_navigation = '';
    if ($show_back_to_terms) {
      $where_back = t('terms');
      if (variable_get('taxonomy_vtn_user_friendly_titles', 1) == 1) {
        $where_back = t('master index');
      }
      $nodes_navigation = '<span class="taxonomy-vtn-back-button">'. l('<< '. t('Back to') .' '. $where_back, 'taxonomy_vtn/voc/'. $term_obj->vid) .'</span>';
      $output .= '<div class="taxonomy-vtn-navigation">'. $nodes_navigation .'</div>';
    }
    return $output;

  case 1:
    // no choice, ignore $voc_name
    return taxonomy_vtn_show_nodes($terms[0]->tid);

  default:
    // more than one, check the vocab and see
    $vocid = db_result(db_query(db_rewrite_sql("SELECT v.vid FROM {vocabulary} v WHERE LOWER(v.name) = '%s'", 'v', 'vid'), drupal_strtolower($voc_name)));
    foreach ($terms as $term) {
      if ($term->vid == $vocid) {
        // got it
        return taxonomy_vtn_show_nodes($term->tid);
      }
    }
    // randomly choose one term...
    return taxonomy_vtn_show_nodes($terms[0]->tid);

  }
}
