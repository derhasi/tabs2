# tabs2

A Drupal module for rendering tabs

## Examples

### Usage as render array

```php
<?php
  $tabs = array(
    array(
      'id' => 'tab-1',
      'title' => t('Tab title one'),
      'content' => t('Tab content one'),
    ),
    array(
      'id' => 'tab-2',
      'title' => t('Tab title two'),
      'content' => t('Tab content two'),
    ),
    array(
      'id' => 'tab-3',
      'title' => t('Tab title three'),
      'content' => t('Tab content three'),
    ),
  );

  $content = array(
    '#theme' => 'tabs2',
    '#tabs' => $tabs,
  );
  
  print drupal_render($content);
?>
```
