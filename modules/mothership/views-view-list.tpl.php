<?php
// $Id: views-view-list.tpl.php,v 1.3 2008/09/30 19:47:11 merlinofchaos Exp $
/**
 * @file views-view-list.tpl.php
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */

/*
  The $classes are defined in template_preprocess_views_view_list() 
  
*/
?>
<!-- views-view-list.tpl.php -->
<?php if (!empty($title)) { ?>
  <h3><?php print $title; ?></h3>
<?php } ?>

<<?php print $options['type']; ?>>

  <?php foreach ($rows as $id => $row): ?>
    
    <li 
      <?php if($classes[$id]){   ?>
        class="<?php print $classes[$id]; ?>"
      <?php } ?>
    >
      <?php print $row; ?>
    </li>
  <?php endforeach; ?>

</<?php print $options['type']; ?>>
<!-- /views-viewsiew-list.tpl.php -->