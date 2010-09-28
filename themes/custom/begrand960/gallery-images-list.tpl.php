<?php
// $Id: gallery-images-list.tpl.php,v 1.1.2.3 2009/11/20 00:22:44 kmonty Exp $
?>
<p class="info">To view as a slide show click on an image and sit back and relax. You can pause and resume the slideshow at any time.</p>

<div class="gallery-images-list clear-block">
  <?php
  if (is_array($images_list)) {
    print theme('item_list', $images_list);
  }
  else {
    print $empty_message;
  }
  ?>
</div>