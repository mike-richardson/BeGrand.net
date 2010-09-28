<?php
// $Id: views-view-unformatted.tpl.php,v 1.6 2008/10/01 20:52:11 merlinofchaos Exp $
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */

/*
  The $classes are defined in template_preprocess_views_view_list() 
*/
?>
<!-- views-view-unformatted.tpl.php -->
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>

    <div
      <?php if($classes[$id]){   ?>
        class="<?php print $classes[$id]; ?>"
      <?php } ?>
    >

    <?php print $row; ?>
  </div>
<?php endforeach; ?>
<!-- / views-view-unformatted.tpl.php -->