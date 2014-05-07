<?php
/**
 * @file
 * Default template for rendering tabs2 tabs.
 */
?>
<div id="<?php print $id;?>"<?php print $attributes;?>>
  <?php print $links; ?>
  <?php foreach ($tabs as $id => $tab): ?>
    <div id="<?php print $tab['id']; ?>"<?php print $tab['attributes']; ?>>
      <?php print $tab['content']; ?>
    </div>
  <?php endforeach; ?>
</div>
