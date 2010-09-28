<div class="<?php print $classes; ?>">
<?php if (!empty($smallimage)) { print $smallimage; } ?>
<p><strong><?php print l($title, $detailpageurl, array('html' => TRUE)); ?></strong></p>
<p><strong><?php print t('Author'); ?>:</strong> <?php print $author; ?>, <strong>Price:</strong> <?php print $listpriceformattedprice; ?></p>
</div>
