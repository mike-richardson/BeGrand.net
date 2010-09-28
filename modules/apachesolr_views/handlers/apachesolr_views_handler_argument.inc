<?php

// $Id: apachesolr_views_handler_argument.inc,v 1.6 2010/02/02 23:52:01 scottreynolds Exp $

/**
 * Class that allows searching the site with Apache Solr through a view.
 */
class apachesolr_views_handler_argument extends views_handler_argument {
  
  /**
   * Add argument to query.
   */
  public function query() {
    if (!empty($this->options['break_phrase'])) {
      $this->value = explode(',', $this->argument);
    }
    else {
      $this->value = array($this->argument);
    }
    foreach ($this->value as $facet_value) {
      $this->query->add_filter($this->real_field, apachesolr_views_query::escape_term($facet_value));
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['break_phrase'] = array('default' => FALSE);

    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // allow for , delimited values
    $form['break_phrase'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow multiple terms per argument.'),
      '#description' => t('If selected, users can enter multiple arguments in the form of 1,2,3.'),
      '#default_value' => !empty($this->options['break_phrase']),
    );
  }
  
  /**
   * Provide a list of default behaviors for this argument if the argument
   * is not present.
   *
   * Provide fewer methods that the standard. Remove summary views
   */
  function default_actions($which = NULL) {
    $defaults = array(
      'ignore' => array(
        'title' => t('Display all values'),
        'method' => 'default_ignore',
        'breadcrumb' => TRUE, // generate a breadcrumb to here
      ),
      'not found' => array(
        'title' => t('Hide view / Page not found (404)'),
        'method' => 'default_not_found',
        'hard fail' => TRUE, // This is a hard fail condition
      ),
      'empty' => array(
        'title' => t('Display empty text'),
        'method' => 'default_empty',
        'breadcrumb' => TRUE, // generate a breadcrumb to here
      ),
      'default' => array(
        'title' => t('Provide default argument'),
        'method' => 'default_default',
        'form method' => 'default_argument_form',
        'has default argument' => TRUE,
        'default only' => TRUE, // this can only be used for missing argument, not validation failure
      ),
    );

    if ($which) {
      if (!empty($defaults[$which])) {
        return $defaults[$which];
      }
    }
    else {
      return $defaults;
    }
  }
  
}
