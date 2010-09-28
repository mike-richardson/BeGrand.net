<?php
// $Id: page.tpl.php,v 1.1.2.1 2009/02/24 15:34:45 dvessel Exp $
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

<body class="<?php print $body_classes; ?> ">
  <div id="page" class="container-16 clear-block">

    <div id="site-header" class="clear-block">
      <div id="branding" class="grid-4 clear-block">
      <?php if ($linked_logo_img): ?>
        <span id="logo" class="grid-4 alpha omega"><?php print $linked_logo_img; ?></span>
      <?php endif; ?>
      <?php if ($linked_site_name): ?>
        <h1 id="site-name" class="grid-4 alpha omega"><?php print $linked_site_name; ?></h1>
      <?php endif; ?>
      <?php if ($site_slogan): ?>
        <div id="site-slogan" class="grid-4 alpha omega"><h1><?php print $site_slogan; ?></h1></div>
      <?php endif; ?>
      </div>
       
    <?php if ($top_search): ?>
          <div id="top-search" class="region grid-12">
            <?php print $top_search; ?>
          </div> <!-- /#top_search -->
        <?php endif; ?>
        
         <div id="loggedin_status" class="grid-4">
        <?php print $loggedin_status; ?>
        
        </div>


    <?php if ($main_menu_links || $secondary_menu_links): ?>
      <div id="site-menu" class="grid-12">
        <?php print $main_menu_links; ?>
        <?php print $secondary_menu_links; ?>
      </div>
    <?php endif; ?>

   
    </div>

	
    	

    <div id="main" class="column <?php print ns('grid-16', $left, 4, $right, 4) . ' ' . ns('push-4', !$left, 4); ?>">
      <?php print $breadcrumb; ?>

      <?php // if ($title): ?>
        <!-- <h1 class="title" id="page-title"><?php // print $title; ?></h1> -->
      <?php // endif; ?>
      <?php if ($tabs): ?>
        <div class="tabs"><?php print $tabs; ?></div>
      <?php endif; ?>
      
      <?php 
      	// Don't display login/register link to non-registered users
      	// Hacked by Mike Richardson, Monday June 21, 2010
      	//print $messages; 
      ?>
      <?php print $help; ?>

      <div id="main-content" class="region clear-block">
      <?php if ($content_top): ?>
      		<?php print $content_top; ?>
      <?php endif; ?>
      <?php print $content; ?>
      <?php if ($content_bottom): ?>
 		 <?php print $content_bottom; ?>
      <?php endif; ?>
      </div>

      <?php print $feed_icons; ?>
    </div>

  <?php if ($left): ?>
    <div id="sidebar-left" class="column sidebar region grid-4 <?php print ns('pull-12', $right, 4); ?>">
      <?php print $left; ?>
    </div>
  <?php endif; ?>

  <?php if ($right): ?>
    <div id="sidebar-right" class="column sidebar region grid-4">
      <?php print $right; ?>
    </div>
  <?php endif; ?>


  <div id="footer" class="grid-16">
    
    
    <div class="clear-block" id="footer-blocks">
    	<div id="footer-block-1" class="grid-4 alpha footer-block">
    	<?php print $footer_block_1; ?>
    	</div>
    	<div id="footer-block-2" class="grid-4  footer-block">
    	<?php print $footer_block_2; ?>
    	</div>
    	<div id="footer-block-3" class="grid-4  footer-block">
    	<?php print $footer_block_3; ?>
    	</div>
    	<div id="footer-block-4" class="grid-4 omega footer-block">
    	<?php print $footer_block_4; ?>
    	</div>
    
    </div>
    
    <?php if ($footer): ?>
      <div id="footer-region" class="region grid-16 alpha omega clear-block">
        <?php print $footer; ?>
      </div>
    <?php endif; ?>

    <?php if ($footer_message): ?>
      <div id="footer-message" class="grid-16">
        <?php print $footer_message; ?>
      </div>
    <?php endif; ?>
  </div>


  </div>
  
  <?php print $closure; ?>
</body>
</html>
