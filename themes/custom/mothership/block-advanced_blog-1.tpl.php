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
<div id="blog-mission">
  <?php if ($block->subject): ?>
    <h2><?php print $block->subject; ?></h2>
  <?php endif; ?>
  
  <!-- Added by Mike Richardson (mike@begrand.net) 16-Feb-2010 -->
  <img src="/<?php print $block->picture ?>" class="right">
  <?php print $block->content; ?>
  <?php print $edit_links; ?>
</div>