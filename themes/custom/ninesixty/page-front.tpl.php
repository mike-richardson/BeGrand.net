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

<body class="<?php print $body_classes; ?>">
  <div id="page" class="container-16 clear-block ">

    <div id="site-header" class="clear-block">
      <div id="branding" class="grid-4 clear-block">
      <?php if ($linked_logo_img): ?>
        <span id="logo" class="grid-4 alpha omega"><?php print $linked_logo_img; ?></span>
      <?php endif; ?>
      <?php if ($linked_site_name): ?>
        <h1 id="site-name" class="grid-4 aplha omega"><?php print $linked_site_name; ?></h1>
      <?php endif; ?>
      <?php if ($site_slogan): ?>
        <div id="site-slogan" class="grid-4 alpha omega"><?php print $site_slogan; ?></div>
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

	
   <div id="home-intro"	class="grid-16 clear-block">
   
   		<div id="intro-text" class="grid-7 alpha">
   		<?php print $intro_text ?>
   		
   		</div>
   		
   		<div id="home-video" class="grid-5">
   		<?php print $home_video ?>
   		</div>
   		
   		<div id="join-home" class="grid-4 omega">
   		<?php print $join_home ?>
   		
   		</div>
   
   
   </div>

    <div id="main" class="column grid-16">
      
      <div class="clear-block">
     	 <div id="home-feature" class="grid-8 alpha">
			<?php print $home_feature ?>
     	</div>
     	<div id="home-topics" class="grid-4">
			<?php print $home_topics ?>
     	</div>
     	<div id="home-ages" class="grid-4 omega">
			<?php print $home_ages ?>
     	</div>
     	
     </div>
     
     <div class="clear-block">
     	<div id="home-poll" class="grid-3 alpha">
			<?php print $home_poll ?>
     	</div>
     	
     	<div id="home-expert" class="grid-5">
			<?php print $home_expert ?>
     	</div>
     	<div id="home-popular" class="grid-4">
			<?php print $home_popular ?>
     	</div>
     	<div id="home-comments" class="grid-4 omega">
			<?php print $home_comments ?>
     	</div>
     
     </div>
    </div>




  <div id="footer" class="prefix-1 suffix-1">
    <?php if ($footer): ?>
      <div id="footer-region" class="region grid-14 clear-block">
        <?php print $footer; ?>
      </div>
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
