<?php
// $Id: gallery-teaser.tpl.php,v 1.1.2.3 2009/11/20 00:22:44 kmonty Exp $
?>
<div class="gallery-teaser">
  <?php
  if (is_array($gallery_teaser)) {
    print theme('item_list', $gallery_teaser);
  }
  else {
    print $gallery_teaser;
  }
?>
</div>