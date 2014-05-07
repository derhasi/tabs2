<?php

/**
 * Preprocessing template tabs2.tpl.php.
 *
 * - tabs: array of tabs containing
 *   - 'id'
 *   - 'title'
 *   - 'content'
 *   - 'attributes' optional array for providing attributes to the content.
 *   - 'tab_attributes'
 * - attributes_array
 * - menu_attributes
 * - settings: additional js settings for instantiating the tabs
 */
function template_preprocess_tabs2(&$vars) {

  // Unify attributes (string) and attributes_array.
  if (!isset($vars['attributes_array'])) {
    $vars['attributes_array'] = array();
  }

  if (isset($vars['attributes']) && is_array($vars['attributes'])) {
    $vars['attributes_array'] = array_merge($vars['attributes'], $vars['attributes_array']);
  }
  // The id has to be specified in $vars['id'] and will not be part of $attributes.
  if (isset($vars['attributes_array']['id'])) {
    if (!isset($vars['id'])) {
      $vars['id'] = $vars['attributes_array']['id'];
    }
    unset($vars['attributes_array']['id']);
  }

  $items = array();
  foreach ($vars['tabs'] as $id => $tab) {

    if (!isset($tab['tab_attributes'])) {
      $tab['tab_attributes'] = array(
        'class' => array('tab-title'),
      );
    }

    // We need to avoid the base url for making the fragment handling work. Due
    // to this we provide href as attribute and are not using l().
    // http://stackoverflow.com/questions/13999152/jquery-ui-tabs-reacting-weired
    $tab['tab_attributes']['href'] = '#' . $tab['id'];
    $attr = drupal_attributes($tab['tab_attributes']);

    $items[] = array(
      'data' => "<a $attr>". check_plain($tab['title']) . '</a>',
    );

    // Make sure tabs content is rendered.
    $vars['tabs'][$id]['content'] = render($tab['content']);

    // Provide attributes for each tab content element.
    if (!empty($tab['attributes'])) {
      if (is_array($tab['attributes'])) {
        $vars['tabs'][$id]['attributes'] = drupal_attributes($tab['attributes']);
      }
      else {
        $vars['tabs'][$id]['attributes'] = ' ' . trim($tab['attributes']);
      }
    }
    else {
      $vars['tabs'][$id]['attributes'] = '';
    }
  }

  $vars['id'] = (!empty($vars['attributes_array']['id'])) ? $vars['attributes_array']['id'] : drupal_html_id('tabs2');

  // We may provide additional
  $tabs_js_setting = (isset($vars['settings'])) ? $vars['settings'] : array();
  
  $links_array = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#attributes' => !empty($vars['menu_attributes_array']) ? $vars['menu_attributes_array'] : array(),
    '#attached' => array(
      'library' => array(
        array('tabs2', 'tabs'),
      ),
      'js' => array(
        array(
          'data' => array(
            'tabs2' => array(
              '#' . $vars['id'] => $tabs_js_setting,
            ),
          ),
          'type' => 'setting',
        ),
      ),
    ),
  );

  $vars['links'] = drupal_render($links_array);
}

/**
 * Preprocessing template tabs2-view-tabs.tpl.php.
 */
function template_preprocess_tabs2_view_tabs(&$vars) {
  
  // Unset class first.
  unset($vars['attributes_array']['class']);
  // Now set our classes. 
  $vars['attributes_array']['class'] = array('tabs2', 'tabs-list-thirds');
  // Render the tabs.
  $vars['tabs2'] = theme('tabs2__view', $vars);
  
  //$vars['attributes_array']['class'] = array('tabs-list-thirds');
}
