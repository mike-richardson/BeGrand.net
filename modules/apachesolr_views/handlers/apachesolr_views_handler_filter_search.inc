<?php

/* $Id: apachesolr_views_handler_filter_search.inc,v 1.2 2009/11/11 23:19:52 scottreynolds Exp $ */

/**
 * Class that allows searching the site with Apache Solr through a view.
 */
class apachesolr_views_handler_filter_search extends views_handler_filter_search {
  
  public function query() {
    if (!empty($this->value)) {
      $this->query->set_query($this->value);
    }
  }
  
   /**
   * Validate the options form.
   */
  function exposed_validate($form, &$form_state) {
    // @TODO decide what we want to do here if anything
  }
  
}
