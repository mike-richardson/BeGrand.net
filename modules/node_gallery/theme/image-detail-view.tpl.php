<?php
// $Id: image-detail-view.tpl.php,v 1.1.2.2 2009/07/27 17:32:51 kmonty Exp $
?>
<div class="image-preview"><?php print $image; ?></div>
<?php if (!empty($extra)): ?>
  <div class="image-preview-extra"><?php print $extra; ?></div>
<?php endif; ?>