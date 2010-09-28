<?php if (!empty($invalid_asin)) { print "<div class='invalid_asin'>This item is no longer valid on Amazon.</div>"; } ?>
<?php if (!empty($smallimage)) { print $smallimage; } ?>
<?php if (!empty($title)) { ?>
	<h3><?php print $title;?><h3>
	<p><strong><a href="<?php print $detailpageurl; ?>" target="_blank"><?php print $title; ?></strong></a></p>
<?php } ?>
