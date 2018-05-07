<?php

/**
 * @file
 * Views integration for the University of Iowa Tracker module.
 */

/**
 * Implements hook_views_default_views().
 */
function uiowa_tracker_views_default_views() {

  /* Exported uiowa_tracker_data view */
  $view = new view();
  $view->name = 'uiowa_tracker_data';
  $view->description = 'Tracking data of node views by authenticated users for the University of Iowa Tracker module.';
  $view->tag = 'default';
  $view->base_table = 'uiowa_tracker_log';
  $view->human_name = 'Tracker Data';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'UIowa Tracker Data';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access uiowa tracker data';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Clear All';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'trackid' => 'trackid',
    'nid' => 'nid',
    'pagetitle' => 'pagetitle',
    'path' => 'path',
    'uid' => 'uid',
    'username' => 'username',
    'rolename' => 'rolename',
    'timestamp' => 'timestamp',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'trackid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'pagetitle' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'path' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'username' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'rolename' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['caption'] = 'University of Iowa Tracker data for node views by authenticated users';
  $handler->display->display_options['style_options']['summary'] = 'University of Iowa Tracker data for node views by authenticated users, including user, page and timestamp.';
  /* Field: UIowa Tracker: Tracking id */
  $handler->display->display_options['fields']['trackid']['id'] = 'trackid';
  $handler->display->display_options['fields']['trackid']['table'] = 'uiowa_tracker_log';
  $handler->display->display_options['fields']['trackid']['field'] = 'trackid';
  $handler->display->display_options['fields']['trackid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['trackid']['separator'] = '';
  /* Field: UIowa Tracker: Node id */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'uiowa_tracker_log';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['separator'] = '';
  /* Field: UIowa Tracker: Page title */
  $handler->display->display_options['fields']['pagetitle']['id'] = 'pagetitle';
  $handler->display->display_options['fields']['pagetitle']['table'] = 'uiowa_tracker_log';
  $handler->display->display_options['fields']['pagetitle']['field'] = 'pagetitle';
  /* Field: UIowa Tracker: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'uiowa_tracker_log';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  /* Field: UIowa Tracker: User id */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'uiowa_tracker_log';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  /* Field: UIowa Tracker: User name */
  $handler->display->display_options['fields']['username']['id'] = 'username';
  $handler->display->display_options['fields']['username']['table'] = 'uiowa_tracker_log';
  $handler->display->display_options['fields']['username']['field'] = 'username';
  /* Field: UIowa Tracker: Role name(s) */
  $handler->display->display_options['fields']['rolename']['id'] = 'rolename';
  $handler->display->display_options['fields']['rolename']['table'] = 'uiowa_tracker_log';
  $handler->display->display_options['fields']['rolename']['field'] = 'rolename';
  $handler->display->display_options['fields']['rolename']['label'] = 'Role(s)';
  /* Field: UIowa Tracker: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'uiowa_tracker_log';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'long';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'long';
  /* Sort criterion: UIowa Tracker: Timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'uiowa_tracker_log';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  /* Filter criterion: UIowa Tracker: Role name(s) */
  $handler->display->display_options['filters']['rolename']['id'] = 'rolename';
  $handler->display->display_options['filters']['rolename']['table'] = 'uiowa_tracker_log';
  $handler->display->display_options['filters']['rolename']['field'] = 'rolename';
  $handler->display->display_options['filters']['rolename']['operator'] = 'word';
  $handler->display->display_options['filters']['rolename']['exposed'] = TRUE;
  $handler->display->display_options['filters']['rolename']['expose']['operator_id'] = 'rolename_op';
  $handler->display->display_options['filters']['rolename']['expose']['label'] = 'Filter by Role name(s)';
  $handler->display->display_options['filters']['rolename']['expose']['operator'] = 'rolename_op';
  $handler->display->display_options['filters']['rolename']['expose']['identifier'] = 'rolename';
  $handler->display->display_options['filters']['rolename']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_uiowa_tracker_data');
  $handler->display->display_options['path'] = 'uiowa_tracker_data';

  /* Display: CSV export */
  $handler = $view->new_display('views_data_export', 'CSV export', 'views_export_uiowa_tracker_data');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 0;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 1;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['newline_token'] = '1';
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 0;
  $handler->display->display_options['path'] = 'uiowa_tracker_data.csv';
  $handler->display->display_options['displays'] = array(
    'page_uiowa_tracker_data' => 'page_uiowa_tracker_data',
    'default' => 0,
  );

  // Add view to list of views to provide.
  $views[$view->name] = $view;

  return $views;
}
