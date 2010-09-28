<?php
// $Id: gallery-image-thumbnail.tpl.php,v 1.1.2.2 2009/07/27 17:32:51 kmonty Exp $
?>
<div class="image-thumbnail-view <?php if ($type) print "image-thumbnail-". $type; ?>">
  <div class="image-thumbnail"><?php print $image_output; ?></div>
  <?php if ($mode == NODE_GALLERY_VIEW_IMAGE_LIST): ?>
    <div class="image-title"><?php print $title_output; ?></div>
  <?php endif; ?>
</div>