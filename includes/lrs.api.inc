<?php

/**
 * @file
 * Helper functions for communicating with the TinCan API.
 */

/**
 * Create an api engine for calling the api.
 */
function lrs_tincanapi_remotelrs() {
  $path = lrs_tincanapi_library_path();
  if($path && file_exists($path . '/RemoteLRS.php')) {
    require_once('./'. $path . '/RemoteLRS.php');
    $endpoint = variable_get('tincanapi_endpoint', '');
    $version = variable_get('tincanapi_version', '');
    $username = variable_get('tincanapi_username', '');
    $password = variable_get('tincanapi_password', '');

    return new TinCanAPI_RemoteLRS($endpoint, $version, $username, $password);
  }
  else {
    drupal_set_message(t('Ooops! LRS Engine not initialized'), 'error', FALSE);
  }
}

/*
 * Determine the path to the TinCan API php library
 */
function lrs_tincanapi_library_path() {
  // A path can be configured to the location of the library
  $path = variable_get('lrs_tincanapi_library_path', FALSE);

  if(!$path) {
    // Check of the libraries module is installed
    if(module_exists('libraries')) {
      // Check if the library is found. If no library is found libraries_get_path()
      // will still return sites/all/libraries as a path.
      $libraries = libraries_get_libraries();
      if(isset($libraries['TinCanPHP'])) {
        $path = libraries_get_path('TinCanPHP');
      }
    }

    // Look for the library in sites/all/libraries and sites/default/libraries
    if(file_exists('sites/default/libraries/TinCanPHP/src/RemoteLRS.php')) {
      return 'sites/default/libraries/TinCanPHP/src';
    }
    if(file_exists('sites/all/libraries/TinCanPHP/src/RemoteLRS.php')) {
      return 'sites/all/libraries/TinCanPHP/src';
    }
  }
  return $path;
}

/**
 * Call a method on a given service.
 *
 * This function does the actual call.
 */
function _lrs_tincanapi_call($method, $params) {
  try {
    $lrs_remote_service = lrs_tincanapi_remotelrs();
    if($lrs_remote_service) {
      if(method_exists($lrs_remote_service, $method)) {
        $response = call_user_func_array(array($lrs_remote_service, $method), $params);
        return $response;
      }
      trigger_error(t('TinCanPHP method %method could not be found. Requested method was %method.', array('%method' => $method)), E_USER_WARNING);
    }
  }
  catch(Exception $e) {
    trigger_error($e->getMessage(), E_USER_ERROR); 
  }
  return NULL;
}
