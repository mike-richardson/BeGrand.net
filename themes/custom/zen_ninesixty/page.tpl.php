<?php
// $Id: page.tpl.php,v 1.1 2009/06/26 00:33:39 duvien Exp $
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>

<body class="<?php print $body_classes; ?>">
  <div id="page" class="container-16 clear-block">

    <div id="site-header" class="clear-block">
	<div id="header-inner">
      <div id="branding" class="grid-4 clear-block">
      <?php if ($linked_logo_img): ?>
        <span id="logo" class="grid-1 alpha"><?php print $linked_logo_img; ?></span>
      <?php endif; ?>
      <?php if ($linked_site_name): ?>
        <h1 id="site-name" class="grid-3 omega"><?php print $linked_site_name; ?></h1>
      <?php endif; ?>
      <?php if ($site_slogan): ?>
        <div id="site-slogan" class="grid-3 omega"><?php print $site_slogan; ?></div>
      <?php endif; ?>
      </div>

    <?php if ($main_menu_links || $secondary_menu_links): ?>
      <div id="site-menu" class="grid-12">
	  <div id="navbar-inner">
        <?php print $main_menu_links; ?>
        <?php print $secondary_menu_links; ?>
      </div>
	  </div> <!--//end #navbar-inner -->
    <?php endif; ?>

    <?php if ($search_box): ?>
      <div id="search-box" class="grid-6 prefix-10"><?php print $search_box; ?></div>
    <?php endif; ?>
    </div>

    <div id="site-subheader" class="prefix-1 suffix-1 clear-block">
    <?php if ($mission): ?>
      <div id="mission" class="<?php print ns('grid-14', $header, 7); ?>">
        <?php print $mission; ?>
      </div>
    <?php endif; ?>

    <?php if ($header): ?>
      <div id="header-region" class="region <?php print ns('grid-14', $mission, 7); ?> clear-block">
        <?php print $header; ?>
      </div>
    <?php endif; ?>
    </div>
	</div>

    <div id="main" class="column <?php print ns('grid-16', $left, 4, $right, 4) . ' ' . ns('push-4', !$left, 4); ?>">
	<div id="content"><div id="content-inner">
      <?php print $breadcrumb; ?>
      <?php if ($title): ?>
        <h1 class="title" id="page-title"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php if ($tabs): ?>
        <div class="tabs"><?php print $tabs; ?></div>
      <?php endif; ?>
      <?php print $messages; ?>
      <?php print $help; ?>

		<?php if ($content_top): ?>
        <div id="content-top" class="region region-content_top">
          <?php print $content_top; ?>
        </div> <!-- /#content-top -->
      <?php endif; ?>

      <div id="main-content" class="region clear-block">
        <?php print $content; ?>
      </div> <!-- //end #main-content -->

      <?php print $feed_icons; ?>
    </div> <!--//end #main -->

	<?php if ($content_bottom): ?>
      <div id="content-bottom" class="region region-content_bottom">
        <?php print $content_bottom; ?>
      </div> <!-- /#content-bottom -->
    <?php endif; ?>

  </div></div> <!-- /#content-inner, /#content -->
  <?php if ($left): ?>
    <div id="sidebar-left" class="column sidebar region grid-4 <?php print ns('pull-12', $right, 4); ?>">
	<div id="sidebar-left-inner">
      <?php print $left; ?>
    </div>
    </div> <!-- //end #sidebar-left-inner -->
  <?php endif; ?>

  <?php if ($right): ?>
    <div id="sidebar-right" class="column sidebar region grid-4">
	<div id="sidebar-right-inner">
      <?php print $right; ?>
    </div>
    </div> <!--//end #sidebar-right-inner -->
  <?php endif; ?>

  <div id="footer" class="prefix-1 suffix-1">
    <?php if ($footer): ?>
      <div id="footer-region" class="region grid-14 clear-block">
	  <div id="footer-inner">
        <?php print $footer; ?>
      </div>
	  </div> <!--//end #footer-inner -->
    <?php endif; ?>

    <?php if ($footer_message): ?>
      <div id="footer-message" class="grid-14">
        <?php print $footer_message; ?>
      </div>
    <?php endif; ?>
  </div>

  </div>
  <?php print $closure; ?>
</body>
</html>