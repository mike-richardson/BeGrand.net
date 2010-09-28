<?php
// $Id: imagefield_extended.admin.inc,v 1.1 2009/09/15 14:23:12 aland Exp $

/**
 * @file
 * Administration related functions.
 */

/**
 * Menu callback.
 * Used to define what field types will be available when
 * creating an imagefield with additional fields CCK field.
 */
function imagefield_extended_admin_settings_form() {
  $form = array();
  $form['imagefield_extended_textfields'] = array(
    '#type' => 'textarea',
    '#title' => t('Additional text fields'),
    '#default_value' => variable_get('imagefield_extended_textfields', ''),
    '#description' => t('A list of new textfields to make available. One textfield form API key / value per line. Key / value pairs must be entered seperated by pipes (|), such as "fapi_safe_key|Some readable option".'),
    '#cols' => 60,
    '#rows' => 5,
    '#element_validate' => array('imagefield_extended_options_validate'),
  );
  $form['imagefield_extended_checkboxes'] = array(
    '#type' => 'textarea',
    '#title' => t('Additional checkboxes fields'),
    '#default_value' => variable_get('imagefield_extended_checkboxes', ''),
    '#description' => t('A list of new checkboxes to make available. One checkbox form API key / value info per line. Key / value pairs must be entered seperated by pipes (|), such as "fapi_safe_key|Some readable option".'),
    '#cols' => 60,
    '#rows' => 5,
    '#element_validate' => array('imagefield_extended_options_validate'),
  );
  return system_settings_form($form);
}

/**
 * To parse a newline selection list into options.
 */
function imagefield_extended_options_validate($element, &$form_state) {
  $options = array();
  $rows = array_filter(explode("\n", trim($element['#value'])));
  foreach ($rows as $option) {
    $option = trim($option);
    if (strlen($option)) {
      if (preg_match('/^([^|]+)\|(.*)$/', $option, $matches)) {
        $matches[1] = trim($matches[1]);
        $matches[2] = trim($matches[2]);
        if (empty($matches[1]) || empty($matches[1])) {
          form_set_error(implode('][', $element['#array_parents']), t('Each option must be a key / value pair seperated by a pipe (|).'));
          return;
        }
        elseif (preg_match('/[^a-z_]/', $matches[1])) {
          form_set_error(implode('][', $element['#array_parents']), t('The specified key contains one or more illegal characters. Spaces or any other special characters except an underscore (_) are not allowed.'));
          return;
        }
        $options[] = $matches[1] .'|'. $matches[2];

      }
      else {
        form_error($element, t('Each option must be a key / value pair seperated by a pipe (|).'));
        return;
      }
    }
  }

  form_set_value($element, implode("\n", $options), $form_state);
}
