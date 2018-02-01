<?php

/**
 * @file
 * Views integration for the University of Iowa Tracker module.
 */

/**
 * Implements hook_views_data().
 */
function uiowa_tracker_views_data() {
  $data = array();
  $data['uiowa_tracker_log']['table']['group'] = t('UIowa Tracker');
  $data['uiowa_tracker_log']['table']['base'] = array(
    'field' => 'trackid',
    'title' => t('University of Iowa Tracker Data'),
    'help' => t('This table contains data about tracked node views by authenticated user.'),
    'weight' => -10,
  );
  $data['uiowa_tracker_log']['table']['join'] = array(
    'node' => array(
      'handler' => 'views_join',
      'left_table' => 'node',
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'users' => array(
      'handler' => 'views_join',
      'left_table' => 'users',
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  $data['uiowa_tracker_log']['trackid'] = array(
    'title' => t('Tracking id'),
    'help' => t('Tracking id.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_group_by_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_group_by_numeric',
    ),
  );
  $data['uiowa_tracker_log']['nid'] = array(
    'title' => t('Node id'),
    'help' => t('Node id.'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Node'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_node_nid',
      'numeric' => TRUE,
    ),
  );
  $data['uiowa_tracker_log']['path'] = array(
    'title' => t('Path'),
    'help' => t('Relative path of the node.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['uiowa_tracker_log']['pagetitle'] = array(
    'title' => t('Page title'),
    'help' => t('Page title.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['uiowa_tracker_log']['uid'] = array(
    'title' => t('User id'),
    'help' => t('User id.'),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'numeric' => TRUE,
    ),
  );
  $data['uiowa_tracker_log']['username'] = array(
    'title' => t('User name'),
    'help' => t('User name.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['uiowa_tracker_log']['rolename'] = array(
    'title' => t('Role name(s)'),
    'help' => t('Role name(s).'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['uiowa_tracker_log']['timestamp'] = array(
    'title' => t('Timestamp'),
    'help' => t('When user viewed node.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );
  return $data;
}
