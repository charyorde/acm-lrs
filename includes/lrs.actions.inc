<?php

/**
 * @file
 * Hooks for lrs actions
 */

/**
 * Implements hook_hook_info()
 */
function lrs_hook_info() {
  return array(
    'lrs' => array(
      'lrs' => array(
        'view_course_video' => array(
          'runs when' => t('LRS: When a learner views a course video')
        ),
        'pay_fees_completed' => array(
          'runs when' => t('LRS: When a user completes payment of fees')
        ),
        'student_application_completed' => array(
          'runs when' => t('LRS: When a student completes student application')
        )
      ),
    ),
  );
}

/**
 * Implementation of hook_action_info()
 */
function lrs_action_info() {
  return array(
    'view_course_video_action' => array(
      'type' => 'course',
      'description' => t('LRS: Queue viewing of course video'),
      'configurable' => FALSE,
      'behavior' => array('changes_node_property'),
      'hooks' => array(
        'lrs' => array('view_course_video')
      ),
    ),
    'learner_pays_fees_action' => array(
      'type' => 'fees',
      'description' => t('LRS: Queue learner completes fees payment'),
      'configurable' => FALSE,
      'behavior' => array('changes_node_property'),
      'hooks' => array(
        'lrs' => array('pay_fees_completed')
      ),
    ),
    'student_application_completed_action' => array(
      'type' => 'student_application',
      'description' => t('LRS: Queue learner completes student application'),
      'configurable' => FALSE,
      'behavior' => array('changes_node_property'),
      'hooks' => array(
        'lrs' => array('student_application_completed')
      )
    )
  );
}

/**
 * Implementation of hook_action_info_alter().
 */
function lrs_action_info_alter(&$actions) {
  // Allow general system actions to be triggered by lrs.
  foreach($actions as $key => $action) {
    // Key in lrs actions into system actions
    if($action['type'] == 'system') {
      $actions[$key]['hooks']['lrs'] = array('view_course_video');
    }
  }
}

/**
 * Implementation of a Drupal action.
 * Sends a course view count to LRS
 */ 
function view_course_video_action(&$course, $context = array()) {

}

/**
 * Implementation of a Drupal action.
 */
function learner_pays_fees_action(&$fees, $context = array()) {

}

/**
 * Implementation of a Drupal action.
 * Called when a student application is completed.
 */ 
function student_application_completed_action(&$student_application, $context) {

}

/**
 * Trigger a view course video action
 */
function lrs_trigger_view_course_video($course) {
  global $user;
  // Get the action ids.
  $aids = _trigger_get_hook_aids('lrs', 'view_course_video');
  if($aids) {
    // Get who view the course.
    $account = user_load($user->uid);
    foreach($aids as $aid => $action_info) {
      actions_do($aid, $course, array('user' => $account));
    } 
  }
}
