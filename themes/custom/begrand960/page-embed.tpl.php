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
      <span id="logo" class="grid-4 alpha omega"><a href="/" rel="home"><img src="/sites/default/files/begrand960_logo.gif" alt="BeGrand.net" width="220" height="31" title="Home" class="tipTip"/></a>
        </span>
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
   
   		<div class="clear-block grid-7 alpha">
   		<div id="home-feature" class="grid-7 alpha">
			<?php print $home_feature ?>
     	</div>
     	<div id="home-stats" class="grid-7 alpha">
			<?php print $home_stats ?>
     	</div>
     	
     	</div>
   		
   		
   		
   		<div id="home-video" class="grid-5">
   		<?php print $home_video ?>
   		</div>
   		
   		<div id="join-home" class="grid-4 omega">
   		<?php print $join_home ?>
   		
   		</div>
   
   
   </div>

    <div id="main" class="column grid-16">
      
      <div class="clear-block row-2">
      <div id="intro-text" class="grid-8 alpha">
   		<?php print $intro_text ?>
   		
   		</div>
     	 
     	<div id="home-topics" class="grid-4">
			<?php print $home_topics ?>
     	</div>
     	<div id="home-ages" class="grid-4 omega">
			<?php print $home_ages ?>
     	</div>
     	
     </div>
     
     <div class="clear-block row-3">
     	<div id="home-poll" class="grid-4 alpha">
			<?php print $home_poll ?>
     	</div>
     	
     	<div id="home-podcast" class="grid-4">
			<?php print $home_podcast ?>
     	</div>
     	<div id="home-popular" class="grid-4">
			<?php print $home_popular ?>
     	</div>
     	<div id="home-comments" class="grid-4 omega">
			<?php print $home_comments ?>
     	</div>
     
     </div>
    </div>




<div id="footer" class="grid-16" >
    
    
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
  
 <script type="text/javascript">
 $(document).ready(function() {
	$("row-3 ul").equalHeights();
});
 </script>
</body>
</html>
