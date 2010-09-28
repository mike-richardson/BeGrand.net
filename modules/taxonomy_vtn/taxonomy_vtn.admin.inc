<?php
// $Id: taxonomy_vtn.admin.inc,v 1.1.2.7 2009/07/18 19:06:45 alexiswilke Exp $

/**
 * @file
 * administration form
 *
 * This file optimizes the .module by about 400 lines!
 */


/**
 * Define the settings form
 */
function taxonomy_vtn_settings() {

  // re-check for support to setlocale
  module_invoke('taxonomy_vtn', 'checklocales');

  // if we use caching and some setting are modified
  // then cache should be cleared
  $caching = variable_get('taxonomy_vtn_caching', 0);
  $post_caching = $_POST['taxonomy_vtn_caching'];
  if ($post_caching == 1 || ($caching && $_POST && $post_caching == 0)) {
    cache_clear_all('taxonomy_vtn_', 'cache', TRUE);
    drupal_set_message('Cache has cleared.');
  }

  $path = drupal_get_path( 'module', 'taxonomy_vtn' );

  // cache
  $form['global'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );

  // caching
  $desc = t('When Caching is on, entire index pages are being cached and changes on terms, nodes or vocabularies may not always have an effect until the cache gets rebuilt.') .'<br /><strong>'. t('Note') .':</strong> '. t('Now this module supports operations') .': <strong>'. t('insert, update, delete') .'</strong> '. t('for nodes, terms and vocabularies and is expected to automaticaly rebuild its cache. In most cases this is a safe choice. However you can !link now.', array('!link' => l(t('clear your Taxonomy VTN cache'), 'taxonomy_vtn/clear_cache')) );

  $form['global']['taxonomy_vtn_caching'] = array(
    '#type' => 'checkbox',
    '#title' => t('Caching'),
    '#description' => $desc,
    '#default_value' => variable_get('taxonomy_vtn_caching', 0),
  );

  // setlocale
  if ( $server_support_setlocale = variable_get('taxonomy_vtn_server_support_setlocale', 0) ) {
    $info = '<div class="messages info">'. theme_image( 'misc/watchdog-ok.png', 'alt', 'title') .' '. t('!setlocale is supported.!newline In other words, the alphabetical index with letters such as !letters can be properly sorted in your language.', array('!setlocale' => '<strong>setlocale</strong>', '!letters' => '<em>&#x105; &#x119; &#x144;</em>', '!newline' => '<br/>')) .'</div>';
  }
  else {
    $info = '<div class="messages warning">'. theme_image( 'misc/watchdog-warning.png', 'alt', 'title') .' '. t('Your server does not support !setlocale or your version of php is too old (use >= 4.4.0 or >= 5.0.2).!newline In other words, the alphabetical index sorting with letters such as !letters cannot be properly sorted in your language.', array('!setlocale' => '<strong>setlocale</strong>', '!letters' => '<em>&#x105; &#x119; &#x144;</em>', '!newline' => '<br/>')) .'</div>';
  }

  $form['global']['taxonomy_vtn_use_setlocale'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use setlocale'),
    '#description' => t('If you have some trouble with your indexes, try turning off this option.'),
    '#default_value' => ($server_support_setlocale == 1) ? variable_get('taxonomy_vtn_use_setlocale', 1) : 0,
    '#disabled' => ($server_support_setlocale == 0)
  );

  $locales = list_system_locales();
  $form['global']['taxonomy_vtn_locale_code'] = array(
    '#type' => 'select',
    '#title' => t('List of locales supported by your server'),
    '#description' => t('Select your language code for proper sorting.'),
    '#default_value' => variable_get('taxonomy_vtn_locale_code', 'en_US.UTF8'),
    '#options' => $locales,
    '#disabled' => ($server_support_setlocale == 0) || empty($locales)
  );


  $form['global']['info_support_setlocale'] = array(
    '#type' => 'markup',
    '#value' => $info
  );

  $form['global']['taxonomy_vtn_user_friendly_titles'] = array(
    '#type' => 'checkbox',
    '#title' => t('User friendly titles'),
    '#default_value' => variable_get('taxonomy_vtn_user_friendly_titles', 1),
  );

  $form['global']['taxonomy_vtn_overwrite_links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Overwrite links'),
    '#default_value' => variable_get('taxonomy_vtn_overwrite_links', 1),
  );

  $form['global']['taxonomy_vtn_edit_terms'] = array(
    '#type' => 'checkbox',
    '#title' => t('Quick link to edit terms'),
    '#description' => t('When selected, users who have administrative rights for the Taxonomy and Taxonomy VTN modules (BOTH RIGHTS REQUIRED) will see an <em>edit</em> link in the site index.'),
    '#default_value' => variable_get('taxonomy_vtn_edit_terms', 0),
  );




  // vocabularies
  $form['vocabularies'] = array(
    '#type' => 'fieldset',
    '#title' => t('Vocabularies'),
    '#description' => t('Set how the vocabularies index is displayed'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['vocabularies']['taxonomy_vtn_vocabularies_master_index'] = array(
    '#type' => 'textfield',
    '#title' => t('Master index name (default to "Master index")'),
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_master_index', t('Master index')),
  );
  $form['vocabularies']['taxonomy_vtn_vocabularies_hide_master_index'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide master index title'),
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_hide_master_index', FALSE),
    '#description' => t('If checked, do not add an extra title in the master index page (especially useful when your title and first group have the same name.)'),
  );
  $form['vocabularies']['taxonomy_vtn_vocabularies_default_groups'] = array(
    '#type' => 'textfield',
    '#title' => t('Default groups'),
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_default_groups', ''),
    '#description' => t('List of comma separated groups. Used when accessing the master index as taxonomy_vtn. If empty, ignore the groups (i.e. same display as before.)'),
  );
  $form['vocabularies']['taxonomy_vtn_vocabularies_show_voc_desc'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show descriptions'),
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_show_voc_desc', 1),
  );
  $form['vocabularies']['taxonomy_vtn_vocabularies_show_hide_descriptions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show') ." <strong>". t('Hide / Show descriptions') ."</strong>",
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_show_hide_descriptions', 1),
  );
  $form['vocabularies']['taxonomy_vtn_vocabularies_show_count_terms'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show count of terms'),
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_show_count_terms', 1),
  );
  $form['vocabularies']['taxonomy_vtn_vocabularies_show_empty_vocs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show empty vocabularies'),
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_show_empty_vocs', 1),
  );
  $form['vocabularies']['taxonomy_vtn_vocabularies_show_voc_index'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show index letters'),
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_show_voc_index', 0),
  );

  $options = array(
    '1' => t('One'),
    '2' => t('Two'),
    '3' => t('Three')
  );
  $form['vocabularies']['taxonomy_vtn_vocabularies_count_group_vocabularies'] = array(
    '#type' => 'select',
    '#title' => t('Letters to group'),
    '#description' => t('Group vocabulary letters together. Example:') .' <em>A B C</em> '. t('or') .' <em>AB CD CE</em>',
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_count_group_vocabularies', 1),
    '#options' => $options
  );

  $options = array(
    '1' => t('One'),
    '2' => t('Two'),
    '3' => t('Three')
  );
  $form['vocabularies']['taxonomy_vtn_vocabularies_count_column_vocs'] = array(
    '#type' => 'select',
    '#title' => t('Number of columns'),
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_count_column_vocs', 2),
    '#options' => $options
  );

  $form['vocabularies']['taxonomy_vtn_vocabularies_goto_terms_if_one'] = array(
    '#type' => 'checkbox',
    '#title' => t('Directly go to the terms if there is only one vocabulary'),
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_goto_terms_if_one', '0'),
  );

  $form['vocabularies']['taxonomy_vtn_vocabularies_omit'] = array(
    '#type' => 'textfield',
    '#title' => t('Exclude vocabularies by identifiers'),
    '#description' => t('Example: 1, 3, 11, 5'),
    '#default_value' =>  variable_get('taxonomy_vtn_vocabularies_omit', '')
  );

  $form['vocabularies']['taxonomy_vtn_vocabularies_include'] = array(
    '#type' => 'textfield',
    '#title' => t('Include vocabularies by identifiers, leave empty to include all'),
    '#description' => t('Example: 1, 3, 11, 5'),
    '#default_value' =>  variable_get('taxonomy_vtn_vocabularies_include', '')
  );


  $form['vocabularies']['taxonomy_vtn_vocabularies_format'] = array(
    '#type' => 'select',
    '#title' => t('Input format'),
    '#description' => t('Select a format to use to write out the descriptions.'),
    '#default_value' => variable_get('taxonomy_vtn_vocabularies_format', TAXONOMY_VTN_DEFAULT_FORMAT),
    '#options' => _taxonomy_vtn_get_formats(),
  );


  // terms
  $form['terms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Terms'),
    '#description' => t('Set how the terms index is displayed'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['terms']['taxonomy_vtn_terms_show_back_to_voc'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show') .' "<strong>'. t('Back to vocabularies') .'</strong>" '. t('on errors.'),
    '#default_value' => variable_get('taxonomy_vtn_terms_show_back_to_voc', 1),
  );
  $form['terms']['taxonomy_vtn_terms_omit'] = array(
    '#type' => 'textfield',
    '#title' => t('Exclude terms id from all tables'),
    '#description' => t('Example: 1, 3, 11, 5'),
    '#default_value' =>  variable_get('taxonomy_vtn_terms_omit', ''),
  );
  $form['terms']['taxonomy_vtn_terms_include'] = array(
    '#type' => 'textfield',
    '#title' => t('Identifiers of terms to include from all tables, leave empty to include all'),
    '#description' => t('Example: 1, 3, 11, 5'),
    '#default_value' =>  variable_get('taxonomy_vtn_terms_include', ''),
  );


  return system_settings_form($form);
}

/**
 * Implementation of taxonomy_vtn_clear_cache()
 */
function taxonomy_vtn_clear_cache() {
  cache_clear_all('taxonomy_vtn_', 'cache', TRUE);
  drupal_set_message('Cache has cleared.');
  drupal_goto(referer_uri());
}

/**
 * Alter the taxonomy settings page.
 */
function _taxonomy_vtn_settings(&$form) {
  $vid = $form['vid']['#value'];

  // terms
  $form['terms'] = array(
    '#type' => 'fieldset',
    '#title' => t('VTN Terms'),
    '#description' => t('Set how the terms index is displayed'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['terms']["taxonomy_vtn_terms_group$vid"] = array(
    '#type' => 'textfield',
    '#title' => t('Taxonomy VTN Group'),
    '#default_value' => variable_get("taxonomy_vtn_terms_group$vid", ''),
    '#description' => t('Taxonomies with a group name appear under http://www.example.com/taxonomy_vtn/group/&lt;group name&gt;, do not use the name \'all\' since that is a reserved name.'),
  );
  $form['terms']["taxonomy_vtn_terms_long_description$vid"] = array(
    '#type' => 'textarea',
    '#title' => t('Long description'),
    '#default_value' => variable_get("taxonomy_vtn_terms_long_description$vid", ''),
    '#description' => t('Describes this vocabulary in details. This text appears at the top of the terms page. If you use the parent/child scheme, then this description only appears at the top of the page showing the top-most (root) terms. The description of the vocabulary will be used as a teaser in the vocabulary listing page.'),
  );
  $form['terms']["taxonomy_vtn_terms_ignored_chars$vid"] = array(
    '#type' => 'textfield',
    '#title' => t('Unwanted characters in sort'),
    '#default_value' => variable_get("taxonomy_vtn_terms_ignored_chars$vid", ''),
    '#description' => t('List a set of characters to ignore in your terms. Useful if you have terms that start with a (, @, $, ., etc. but do not want to have such an entry in your term index. <span style="color: red;">WARNING:</span> removing the period (.) means removing the decimal point in numbers.'),
  );
  $form['terms']["taxonomy_vtn_terms_numeric_sort$vid"] = array(
    '#type' => 'textfield',
    '#title' => t('Word to sort numerically'),
    '#default_value' => variable_get("taxonomy_vtn_terms_numeric_sort$vid", 0),
    '#description' => t('Enter the word to be sorted numerically. Use 0 to only sort alphabetically.'),
  );
  $form['terms']["taxonomy_vtn_terms_parent_child_links$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Parent/child links'),
    '#default_value' => variable_get("taxonomy_vtn_terms_parent_child_links$vid", 0),
    '#description' => t('Handle the parent/child relationships of this vocabulary so links of a parent points to a child instead of the list of nodes.'),
  );
  $form['terms']["taxonomy_vtn_terms_show_parent_term$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show parent in children\'s list'),
    '#default_value' => variable_get("taxonomy_vtn_terms_show_parent_term$vid", 0),
    '#description' => t('The parent/child links prevent you from actually accessing the list of nodes of a parent term. This flag asks the system to add a link at the top to the list of nodes of the parent term being displayed.'),
  );
  $form['terms']["taxonomy_vtn_terms_show_nodes$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show parent nodes after the terms if any'),
    '#default_value' => variable_get("taxonomy_vtn_terms_show_nodes$vid", 0),
    '#description' => t('When displaying a parent term, if it has nodes, list them right after the list of children terms. (Note: you probably want to hide the parent term from the list of terms, i.e. previous checkbox.)'),
  );
  $form['terms']["taxonomy_vtn_terms_show_back_to_voc$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show') .' "<strong>'. t('Back to vocabularies') .'</strong>"',
    '#default_value' => variable_get("taxonomy_vtn_terms_show_back_to_voc$vid", 1),
  );
  $form['terms']["taxonomy_vtn_terms_show_hide_descriptions$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show') .' "<strong>'. t('Show / Hide descriptions') .'</strong>"',
    '#default_value' => variable_get("taxonomy_vtn_terms_show_hide_descriptions$vid", 1),
  );
  $form['terms']["taxonomy_vtn_terms_show_term_desc$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show descriptions'),
    '#default_value' => variable_get("taxonomy_vtn_terms_show_term_desc$vid", 1)
  );
  $form['terms']["taxonomy_vtn_terms_show_count_nodes$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show count of nodes'),
    '#default_value'  => variable_get("taxonomy_vtn_terms_show_count_nodes$vid", 1)
  );
  $form['terms']["taxonomy_vtn_terms_show_empty_terms$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show empty'),
    '#default_value' => variable_get("taxonomy_vtn_terms_show_empty_terms$vid", 1)
  );
  $form['terms']["taxonomy_vtn_terms_show_terms_index$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show index letters'),
    '#default_value' => variable_get("taxonomy_vtn_terms_show_terms_index$vid", 1)
  );
  $form['terms']["taxonomy_vtn_terms_show_synonyms$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show synonyms'),
    '#default_value' => variable_get("taxonomy_vtn_terms_show_synonyms$vid", 1)
  );
  $form['terms']["taxonomy_vtn_terms_show_related$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show related terms'),
    '#default_value' => variable_get("taxonomy_vtn_terms_show_related$vid", 0)
  );
  $form['terms']["taxonomy_vtn_terms_show_quick_index$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show a list of links at the top of all the letters'),
    '#default_value' => variable_get("taxonomy_vtn_terms_show_quick_index$vid", 0)
  );
  $form['terms']["taxonomy_vtn_terms_break_quick_index$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Break the quick index on two lines'),
    '#default_value' => variable_get("taxonomy_vtn_terms_break_quick_index$vid", 0)
  );
  $form['terms']["taxonomy_vtn_terms_show_statistics$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show statistics at the bottom of the page'),
    '#default_value' => variable_get("taxonomy_vtn_terms_show_statistics$vid", 0)
  );

  $options = array(
    '1' => t('One'),
    '2' => t('Two'),
    '3' => t('Three')
  );
  $form['terms']["taxonomy_vtn_terms_count_group_terms$vid"] = array(
    '#type' => 'select',
    '#title' => t('Letters to group'),
    '#description' => t('Group terms letters together. Example:') .' <em>A B C</em> '. t('or') .' <em>AB CD CE</em>',
    '#default_value' => variable_get("taxonomy_vtn_terms_count_group_terms$vid", 1),
    '#options' => $options
  );

  $options = array(
    '1' => t('One'),
    '2' => t('Two'),
    '3' => t('Three')
  );
  $form['terms']["taxonomy_vtn_terms_count_column_terms$vid"] = array(
    '#type' => 'select',
    '#title' => t('Number of columns'),
    '#default_value' => variable_get("taxonomy_vtn_terms_count_column_terms$vid", 2),
    '#options' => $options,
  );

  $options = array(
    'nodes' => t('List of nodes'),
    'taxonomy_term' => 'taxonomy/term/xxx',
    'taxonomy_term_all' => 'taxonomy/term/xxx/all',
  );
  // Question: should we also test that a view with a path to taxonomy_view exists?
  if (module_exists('views')) {
    $options['taxonomy_view'] = 'taxonomy_view/voc-xxx/term-xxx';
  }
  $form['terms']["taxonomy_vtn_terms_goto$vid"] = array(
    '#type' => 'select',
    '#title' => t('Where people are sent clicking a term'),
    '#default_value' => variable_get("taxonomy_vtn_terms_goto$vid", 'nodes'),
    '#options' => $options,
  );

  $form['terms']["taxonomy_vtn_terms_omit$vid"] = array(
    '#type' => 'textfield',
    '#title' => t('Exclude terms id from the terms table of this vocabulary'),
    '#description' => t('Example: 1, 3, 11, 5'),
    '#default_value' =>  variable_get("taxonomy_vtn_terms_omit$vid", '')
  );

  $form['terms']["taxonomy_vtn_terms_include$vid"] = array(
    '#type' => 'textfield',
    '#title' => t('Include terms id from the terms table of this vocabulary, leave empty to include all'),
    '#description' => t('Example: 1, 3, 11, 5'),
    '#default_value' =>  variable_get("taxonomy_vtn_terms_include$vid", '')
  );

  $form['terms']["taxonomy_vtn_terms_format$vid"] = array(
    '#type' => 'select',
    '#title' => t('Input format'),
    '#description' => t('Select the format for this taxonomy terms'),
    '#default_value' => variable_get("taxonomy_vtn_terms_format$vid", TAXONOMY_VTN_DEFAULT_FORMAT),
    '#options' => _taxonomy_vtn_get_formats(),
  );




  // nodes
  $form['nodes'] = array(
    '#type' => 'fieldset',
    '#title' => t('VTN Nodes'),
    '#description' => t('Set how the nodes index is displayed'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['nodes']["taxonomy_vtn_nodes_show_back_to_terms$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show') .' "<strong>'. t('Back to terms') .'</strong>"',
    '#default_value' => variable_get("taxonomy_vtn_nodes_show_back_to_terms$vid", 1),
  );
  $form['nodes']["taxonomy_vtn_nodes_show_count_comments$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show count of comments'),
    '#default_value' => variable_get("taxonomy_vtn_nodes_show_count_comments$vid", 1),
  );
  $form['nodes']["taxonomy_vtn_nodes_show_empty_count_comments$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show count for nodes without comments'),
    '#default_value' => variable_get("taxonomy_vtn_nodes_show_empty_count_comments$vid", 0),
  );
  $form['nodes']["taxonomy_vtn_nodes_show_nodes_index$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Show index letters'),
    '#default_value' => variable_get("taxonomy_vtn_nodes_show_nodes_index$vid", 0),
  );

  $options = array(
    '1' => t('One'),
    '2' => t('Two'),
  );
  $form['nodes']["taxonomy_vtn_nodes_count_column_nodes$vid"] = array(
    '#type' => 'select',
    '#title' => t('Number of columns'),
    '#default_value' => variable_get("taxonomy_vtn_nodes_count_column_nodes$vid", 2),
    '#options' => $options,
  );

  $form['nodes']["taxonomy_vtn_nodes_links_per_page$vid"] = array(
    '#type' => 'select',
    '#options' => drupal_map_assoc(array(10, 20, 30, 40, 50, 60, 70, 80, 90, 100)),
    '#title' => t('Links per page'),
    '#description' => t('How many links should be displayed per page'),
    '#default_value' => variable_get("taxonomy_vtn_nodes_links_per_page$vid", 10),
  );
  $form['nodes']["taxonomy_vtn_nodes_use_pager$vid"] = array(
    '#type' => 'checkbox',
    '#title' => t('Use pager for nodes'),
    '#default_value' => variable_get("taxonomy_vtn_nodes_use_pager$vid", FALSE),
  );

  $form['#submit'][] = '_taxonomy_vtn_form_vocabulary_submit';

  // this is ugly, but it is even worth to have the Save/Delete buttons before the end
  // (and if you know a cleaner way, post an issue with the solution!)
  $form['submit']['#weight'] = 10;
  $form['delete']['#weight'] = 11;
}

/**
 * Alter the terms form adding a long description.
 */
function _taxonomy_vtn_terms_form(&$form) {
  $tid = $form['tid']['#value'];

  $form['identification']["taxonomy_vtn_term_long_description$tid"] = array(
    '#type' => 'textarea',
    '#title' => t('Long description (Taxonomy VTN)'),
    '#default_value' => ($tid ? variable_get("taxonomy_vtn_term_long_description$tid", '') : ''),
    '#description' => t('Describes this term in details. This text appears at the top of the terms page showing the children of this term. You need to use the parent/child scheme of the Taxonomy VTN module, then this description will appear at the top of the page showing the children of this term. The usual Description of the term will be used as a teaser in the page where this term is listed.'),
  );

  $form['#submit'][] = '_taxonomy_vtn_form_term_submit';
}
