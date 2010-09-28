<?php
// $Id: page.tpl.php,v 1.1.2.1 2009/02/24 15:34:45 dvessel Exp $
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html  xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title>BeGrand.net | The website for grandparents | Home</title>
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
        <?php print $loggedin_status; ?>&nbsp;
        </div>

    <?php if ($main_menu_links || $secondary_menu_links): ?>
      <div id="site-menu" class="grid-12">
        <?php print $main_menu_links; ?>
        <?php print $secondary_menu_links; ?>
      </div>
    <?php endif; ?>

   
    </div>
    
	<?php if ($home_survey): ?>
   		<div id="home-survey"	class="grid-16 clear-block">
    		<?php print $home_survey ?>
    	</div>
	<?php endif; ?>

	
   <div id="row-1"	class="grid-16 clear-block">
   
   		<div class="clear-block grid-8 alpha">
   		<div id="home-feature" class="grid-8 alpha">
			<?php print $home_feature ?>
     	</div>
     	
     	<?php if ($home_banner): ?>
   		<div id="home-banner" class="grid-8 alpha">
			<?php print $home_banner ?>
     	</div>
     	<?php endif; ?>
     	
     	</div>
   		
   		
   		
   		<div id="row1-block2" class="grid-4">
   		<?php print $row1_block2 ?>
   		</div>
   		
   		<div id="row1-block3" class="grid-4 omega">
   		<?php print $row1_block3 ?>
   		
   		</div>
   
   
   </div>

    <div id="main" class="column grid-16">
      
      <div class="clear-block row-2">
      <div id="row2-block1" class="grid-8 alpha">
   		
   		<?php print $row2_block1 ?>
   		
   		
     	
   		</div>
     	 
     	<div id="row2-block2" class="grid-4">
			
			<?php print $row2_block2 ?>
     	</div>
     	<div id="row2-block3" class="grid-4 omega">
			
			<?php print $row2_block3 ?>
     	</div>
     	
     </div>
     
     <div class="clear-block row-3">
     	<div id="row3-block1" class="grid-4 alpha">
			
			<?php print $row3_block1 ?>
     	</div>
     	
     	<div id="row3-block2" class="grid-4">
			
			<?php print $row3_block2 ?>
     	</div>
     	<div id="row3-block3" class="grid-4">
			
			<?php print $row3_block3 ?>
     	</div>
     	<div id="row3-block4" class="grid-4 omega">
			
			<?php print $row3_block4 ?>
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
  

</body>

</html>
