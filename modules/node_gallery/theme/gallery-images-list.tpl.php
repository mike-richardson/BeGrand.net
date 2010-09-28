<?php
// $Id: gallery-images-list.tpl.php,v 1.1.2.3 2009/11/20 00:22:44 kmonty Exp $
?>
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