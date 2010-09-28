<?php
// $Id: ajax_slideshow.views_default.inc,v 1.1.2.1 2009/10/17 14:08:48 udig Exp $

/**
 * Building the default view returning the nids presented by the slideshow
 * @return 
 */
function ajax_slideshow_views_default_views(){
$view = new view;
$view->name = 'ajax_slideshow_view';
$view->description = 'Required by ajax_slideshow module. Returns a list of nodes nids, that should appear within the slideshow.';
$view->tag = '';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('fields', array(
  'nid' => array(
    'label' => 'Nid',
    'link_to_node' => 0,
    'exclude' => 0,
    'id' => 'nid',
    'table' => 'node',
    'field' => 'nid',
    'relationship' => 'none',
  ),
));
$handler->override_option('filters', array(
  'status' => array(
    'operator' => '=',
    'value' => '1',
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'status',
    'table' => 'node',
    'field' => 'status',
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('items_per_page', 0);


$views[$view->name]=$view;
return $views;

}

 