<?php

/**
 * Implements hook_views_plugins().
 */
function tabs2_views_plugins() {
  return array(
    'style' => array(
      'tabs' => array(
        'title' => t('Tabs'),
        'help' => t('Display rows as tabs.'),
        'handler' => 'tabs2_views_plugin_style_tabs',
        'theme' => 'tabs2_view_tabs',
        'theme file' => 'theme.inc',
        'theme path' => drupal_get_path('module', 'tabs2') . '/theme',
        'uses row plugin' => TRUE,
        'uses row class' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}

