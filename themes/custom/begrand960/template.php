<?php

// Hack to remove colon after webform labels
// Friday June 18, 2010 - mike@begrand.net


function begrand960_preprocess_views_exposed_form(&$vars, $hook) {

  // only alter the proximity search exposed filter form
  if ($vars['form']['#id'] == 'views-exposed-form-bgn-events-by-event-type-block-1') {

    // Change the text on the submit button
    $vars['form']['submit']['#value'] = t('Find');

    // Rebuild the rendered version (submit button, rest remains unchanged)
    unset($vars['form']['submit']['#printed']);
    $vars['button'] = drupal_render($vars['form']['submit']);
  }
}



function begrand960_form_element($element, $value) {
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  $output = '<div class="form-item"';
  if (!empty($element['#id'])) {
    $output .= ' id="'. $element['#id'] .'-wrapper"';
  }
  $output .= ">\n";
  $required = !empty($element['#required']) ? '<span class="form-required" title="'. $t('This field is required.') .'">*</span>' : '';

  if (!empty($element['#title'])) {
    $title = $element['#title'];
    if (!empty($element['#id'])) {
      $output .= ' <label for="'. $element['#id'] .'">'. $t('!title !required', array('!title' => filter_xss_admin($title), '!required' => $required)) ."</label>\n";
    }
    else {
      $output .= ' <label>'. $t('!title !required', array('!title' => filter_xss_admin($title), '!required' => $required)) ."</label>\n";
    }
  }

  $output .= " $value\n";

  if (!empty($element['#description'])) {
    $output .= ' <div class="description">'. $element['#description'] ."</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}


function begrand960_fivestar_summary($user_rating, $average_rating, $votes, $stars = 5, $feedback = TRUE) {
  $output = '<h3>Rate this article</h3>';
  $div_class = '';
  if (isset($user_rating)) {
    $div_class = isset($votes) ? 'user-count' : 'user';
    $user_stars = round(($user_rating * $stars) / 100, 1);
    $output .= '<span class="user-rating">'. t('Your rating: <span>!stars</span>', array('!stars' => $user_rating ? $user_stars : t('None'))) .'</span>';
  }
  if (isset($user_rating) && isset($average_rating)) {
    $output .= ' ';
  }
  if (isset($average_rating)) {
    $div_class = isset($votes) ? 'average-count' : 'average';
    $average_stars = round(($average_rating * $stars) / 100, 1);
    $output .= '<span class="average-rating">'. t('Average: <span>!stars</span>', array('!stars' => $average_stars)) .'</span>';
  }
  if (isset($user_rating) && isset($average_rating)) {
    $div_class = 'combo';
  }

  if (isset($votes) && !(isset($user_rating) || isset($average_rating))) {
    $output .= ' <span class="total-votes">'. format_plural($votes, '<span>@count</span> vote', '<span>@count</span> votes') .'</span>';
    $div_class = 'count';
  }
  elseif (isset($votes)) {
    $output .= ' <span class="total-votes">('. format_plural($votes, '<span>@count</span> vote', '<span>@count</span> votes') .')</span>';
  }

  if ($votes === 0) {
    $output = '<span class="empty">'. t('No votes yet') .'</span>';
  }

  $output = '<div class="fivestar-summary fivestar-summary-'. $div_class . ($feedback ? ' fivestar-feedback-enabled' : '') .'">'. $output .'</div>';
  return $output;
}

function begrand960_lt_loggedinblock(){
  	global $user;
  	return l(check_plain($user->name), 'user/' . $user->uid) .' | ' . l(t('Log out'), 'logout');
  }
  
  
 function begrand960_feed_icon($url, $title) {
  if ($image = theme('image', 'misc/feed.png', t('Syndicate content'), $title)) {
    return '<a href="'. check_url($url) .'" class="feed-icon">'. $image .' RSS Feed</a>';
  }
}



function begrand960_username($object) {

  if ($object->uid && $object->name) {
    // Shorten the name when it is too long or it will break many tables.
    //if (drupal_strlen($object->name) > 20) {
      // $name = drupal_substr($object->name, 0, 15) .'...';
    //}
    //else {
      $name = $object->name;
    //}

    if (user_access('access user profiles')) {
      $output = l($name, 'user/'. $object->uid, array('attributes' => array('title' => t('View user profile.'))));
    }
    else {
      $output = check_plain($name);
    }
  }
  else if ($object->name) {
    // Sometimes modules display content composed by people who are
    // not registered members of the site (e.g. mailing list or news
    // aggregator modules). This clause enables modules to display
    // the true author of the content.
    if (!empty($object->homepage)) {
      $output = l($object->name, $object->homepage, array('attributes' => array('rel' => 'nofollow')));
    }
    else {
      $output = check_plain($object->name);
    }

    $output .= ' ('. t('not verified') .')';
  }
  else {
    $output = check_plain(variable_get('anonymous', t('Anonymous')));
  }
	
  return $output;
}


function begrand960_theme($existing, $type, $theme, $path) {
  return array(
    // tell Drupal what template to use for the user register form
    'user_register' => array(
      'arguments' => array('form' => NULL),
      'template' => 'user-register', // this is the name of the template
    ),
    'edit-blog-node-form' => array( 'arguments' => array('form' => NULL),
	),
  );
}

function begrand960_comment_block() {
  $items = array();
  foreach (comment_get_recent() as $comment) {
    $items[] = l($comment->subject, 'node/'. $comment->nid, array('fragment' => 'comment-'. $comment->cid)) .'<br /><span class="comment-date">'. t('@time ago', array('@time' => format_interval(time() - $comment->timestamp))). '</span>';
  }
  if ($items) {
    return theme('item_list', $items);
  }
  
function begrand960_og_page($form) { 
	
		if (!in_array('contributor', array_values($user->roles))){ 
			// Hide complex form fields for authenticated users
			$form['buttons']['save']['#value'] = "Search";

		}
		return (drupal_render($form));
	}
	


	
}




