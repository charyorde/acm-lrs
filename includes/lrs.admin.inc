<?php

/**
 * @file
 * Administration pages for LRS Integration
 */

/**
 * Admin settings form.
 */
function lrs_settings(&$form_state) {
  $form = array();

  $form['learninglocker_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('LearningLocker Configuration Parameters'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Enter your LearningLocker remote access credentials')
  );

  $form['learninglocker_config']['tincanapi_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#description' => t('Enter your remote LearningLocker instance URL. Defaults to !url', array('!url' => 'http://41.160.30.173/learninglocker/data/xAPI')),
    '#default_value' => variable_get('tincanapi_endpoint', 'http://41.160.30.173/learninglocker/data/xAPI')
  );

  $form['learninglocker_config']['tincanapi_version'] = array(
    '#type' => 'textfield',
    '#title' => t('Version'),
    '#description' => t('TinCanPHP API version. Defaults to latest version, !version', array('!version' => TinCanAPI_Version::latest())),
    '#default_value' => variable_get('tincanapi_version', TinCanAPI_Version::latest())
  );

  $form['learninglocker_config']['tincanapi_username'] = array(
    '#type' => 'textfield',
    '#title' => 'Username',
    '#description' => t('Your LearningLocker instance username.'),
    '#default_value' => variable_get('tincanapi_username', '')
  );
  
  $form['learninglocker_config']['tincanapi_password'] = array(
    '#type' => 'textfield',
    '#title' => 'Password',
    '#description' => t('Your LearningLocker instance password.'),
    '#default_value' => variable_get('tincanapi_password', '')
  );

  return system_settings_form($form);
}
