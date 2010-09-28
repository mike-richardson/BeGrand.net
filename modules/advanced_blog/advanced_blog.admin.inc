<?php
// $Id: advanced_blog.admin.inc,v 1.1 2010/03/23 10:32:40 xeniox Exp $

/**
 * @file
 * Renders administrative pages for advanced_blog module
 */

function advanced_blog_admin_settings() {
  $form['advanced_blog_settings'] = array(
    '#type' => 'fieldset',
    '#weight' => -20,
    '#title' => t('Basic settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['advanced_blog_settings']['advanced_blog_maxdisp'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of advanced_blog'),
    '#default_value' => variable_get('advanced_blog_maxdisp', 10),
    '#description' => t("The maximum number of bloggers to display in the block."),
    '#maxlength' => 5,
    '#size' => 5,
  );

  $form['advanced_blog_settings']['advanced_blog_shownum'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show number of blog entries.'),
    '#default_value' => variable_get('advanced_blog_shownum', 0),
    '#description' => t("Display how many blog entries have been written, i.e: Samuel(7), Linda(10)."),
    '#maxlength' => 1,
    '#size' => 1,
  );

  $form['advanced_blog_settings']['advanced_blog_order'] = array(
    '#type' => 'radios',
    '#title' => t('Order by'),
    '#default_value' => variable_get('advanced_blog_order', 0),
    '#options' => array(t('none'), t('Name'), t('Post Count'), t('Date'), t('Random')),
    '#description' => t("No order, order by name, number of entries, date or random."),
  );

  $form['advanced_blog_settings']['advanced_blog_case'] = array(
    '#type' => 'select',
    '#title' => t('Case format'),
    '#default_value' => variable_get('advanced_blog_case', 0),
    '#options' => array(t('None'), t('Smallcase'), t('Uppercase'), t('Wordcase')),
    '#description' => t("Change the case format of bloggers' names displayed in lists."),
  );

  $form['advanced_blog_settings_advanced'] = array(
    '#type' => 'fieldset',
    '#weight' => -15,
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['advanced_blog_settings_advanced']['advanced_blog_on_blog_only'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show advanced_blog module when content type is blog only.'),
    '#default_value' => variable_get('advanced_blog_on_blog_only', 0),
    '#description' => t("Only show blog list on blog pages."),
    '#maxlength' => 1,
    '#size' => 1,
  );

  $form['advanced_blog_settings_avatar'] = array(
    '#type' => 'fieldset',
    '#weight' => -10,
    '#title' => t('Avatar settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['advanced_blog_settings_avatar']['advanced_blog_avatar'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show advanced_blog\'s avatar.'),
    '#default_value' => variable_get('advanced_blog_avatar', 0),
    '#description' => t("Display bloggers' avatars in lists."),
    '#maxlength' => 1,
    '#size' => 1,
  );

  $form['advanced_blog_settings_avatar']['advanced_blog_avatar_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Avatar width'),
    '#default_value' => variable_get('advanced_blog_avatar_width', 20),
    '#description' => t("Set avatar width in px. Set to 0 (zero) if you want to use original width. If you want to set 200 px width then just enter 200 (without px). Tip: to keep picture aspect ratio then you can set the width to certain value but set to 0 (zero) the height value."),
    '#maxlength' => 5,
    '#size' => 5,
  );

  $form['advanced_blog_settings_avatar']['advanced_blog_avatar_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Avatar height'),
    '#default_value' => variable_get('advanced_blog_avatar_height', 20),
    '#description' => t("Set avatar height in px. Set to 0 (zero) if you want to use original height."),
    '#maxlength' => 5,
    '#size' => 5,
  );

  return system_settings_form($form);
}