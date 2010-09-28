<?php
/*
ad a class="" if we have anything in the $classes var
this is so we can have a cleaner output - no reason to have an empty <div class="" id=""> 
*/
if($classes){
   $classes = ' class="' . $classes . '"';
}

if($id_block){
  $id_block = ' id="' . $id_block . '"';  
}
?>

<div class="friends">
  <?php if ($block->subject): ?>
    <h4><?php print $block->subject; ?></h4>
  <?php endif; ?>
  <?php print $block->content; ?>
  <?php print $edit_links; ?>
</div>