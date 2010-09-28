<?php

/* $Id: apachesolr_views_handler_sort.inc,v 1.2 2009/10/08 20:47:16 scottreynolds Exp $ */

/**
 * Class for sorting for a field.
 */
class apachesolr_views_handler_sort extends views_handler_sort {
  
  /**
   * Places the sort into the search parameters.
   */
  public function query() {
    /* These fields have a special "*_sort" field for sorting: */
    $special_sort_fields = array(
      'name' => 'sort_name',
      'title' => 'sort_title',
    );
    $order = strtolower($this->options['order']);
    
    if (empty($special_sort_fields[$this->real_field])) {
      $this->query->add_sort($this->real_field, $order);
    }
    else {
      $this->query->add_sort($special_sort_fields[$this->real_field], $order);
    }
  }
  
}
