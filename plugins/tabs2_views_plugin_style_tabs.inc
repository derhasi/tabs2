<?php

class tabs2_views_plugin_style_tabs extends views_plugin_style_list {

  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['tab_title_field'] = array('default' => '');
    $options['tab_id_field'] = array('default' => '');
    $options['tabs_collapsible'] = array('default' => FALSE);
    $options['tabs_collapsed'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $field_labels = $this->display->handler->get_field_labels(TRUE);

    $form['tab_title_field'] = array(
      '#type' => 'select',
      '#title' => t('Tab title field'),
      '#options' => $field_labels,
      '#default_value' => $this->options['tab_title_field'],
      '#required' => TRUE,
      '#description' => t('Select the field to be used as tab title.'),
      '#weight' => -99,
    );
    $form['tab_id_field'] = array(
      '#type' => 'select',
      '#title' => t('Tab ID field'),
      '#options' => $field_labels,
      '#default_value' => $this->options['tab_id_field'],
      '#required' => TRUE,
      '#description' => t('Select the field to be used as tab id.'),
      '#weight' => -99,
    );
    $form['tabs_collapsible'] = array(
      '#type' => 'checkbox',
      '#title' => t('Make the tabs collapsible'),
      '#default_value' => $this->options['tabs_collapsible'],
      '#description' => t('Check this if you want to make the tabs collapsible.'),
      '#weight' => -90,
    );
    $form['tabs_collapsed'] = array(
      '#type' => 'checkbox',
      '#title' => t('Initially collapse all tabs'),
      '#default_value' => $this->options['tabs_collapsed'],
      '#description' => t('Display all tabs as collapsed by default.'),
      '#weight' => -89,
      '#dependency' => array(
        'edit-style-options-tabs-collapsible' => array(1),
      )
    );
  }

  /**
   * Render the grouping sets.
   *
   * Plugins may override this method if they wish some other way of handling
   * grouping.
   *
   * @param $sets
   *   Array containing the grouping sets to render.
   * @param $level
   *   Integer indicating the hierarchical level of the grouping.
   *
   * @return string
   *   Rendered output of given grouping sets.
   */
  function render_grouping_sets($sets, $level = 0) {
    $grouping = $this->options['grouping'];
    $tab_is_group = FALSE;
    $tab_group_level = NULL;

    $tab_title_field = $this->options['tab_title_field'];
    $tab_id_field = $this->options['tab_id_field'];


    $output = '';
    foreach ($sets as $set) {
      $additional_settings = array();
      $row = reset($set['rows']);
      // Render as a grouping set.
      if (is_array($row) && isset($row['group'])) {
        $output .= theme(views_theme_functions('views_view_grouping', $this->view, $this->display), array(
          'view' => $this->view,
          'grouping' => $this->options['grouping'][$level],
          'grouping_level' => $level,
          'rows' => $set['rows'],
          'title' => $set['group'])
        );
      }
      // Render as a record set.
      else {
        if ($this->uses_row_plugin()) {
          $tabs = array();

          if (!empty($this->options['tabs_collapsible'])) {
            // Make tabs collapsible.
            $additional_settings['collapsible'] = 'true';

            if (!empty($this->options['tabs_collapsed'])) {
              // Set default tab to -1 to collapse all.
              $additional_settings['selected'] = -1;
            }
          }

          foreach ($set['rows'] as $index => $row) {

            // We retrieve the tab title for each row.
            $tab_title = $this->get_field($index, $tab_title_field);
            $tab_id_raw = $this->get_field($index, $tab_id_field);
            $tab_id = drupal_html_id(strip_tags(htmlspecialchars_decode($tab_id_raw)));
            $attributes = array(
              'class' => array($this->tokenize_value($this->options['row_class'], $index)),
            );

            $this->view->row_index = $index;
            $set['rows'][$index] = $this->row_plugin->render($row);

            $tabs[] = array(
              'id' => $tab_id,
              'title' => $tab_title,
              'content' => $this->row_plugin->render($row),
              'attributes' => $attributes,
            );
          }
        }

        $output .= theme($this->theme_functions(), array(
            'view' => $this->view,
            'options' => $this->options,
            'grouping_level' => $level,
            'tabs' => $tabs,
            'title' => $set['group'],
            'attributes_array' => array(
              'class' => array($this->options['wrapper_class']),
            ),
            'menu_attributes_array' => array(
              'class' => array($this->options['class']),
            ),
            'settings' => $additional_settings,
          )
        );
      }
    }
    unset($this->view->row_index);
    return $output;
  }

}
