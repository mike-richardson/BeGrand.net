<p class="info">Template overridden.</p>
<?php

	if ($node->status==0) {
		echo "<p class='unpublished'>This page is UNPUBLISHED and will not be visible to users</p>";
	} 
?>

<?php
//	dsm($node->links);
	// foreach ($node->links as $key => $value) {
	// 	print $node->links[$key]['title'];
	// }

/*
	dsm(get_defined_vars())
	dsm($variables['template_files']);
  dsm($node);
  dsm($node->content);
  print $FIELD_NAME_rendered;
*/

/*
$links splitted up
<?php print $statistics_counter; ?>
<?php print $link_read_more; ?>
<?php print $link_comment; ?>
<?php print $link_comment_add ?>
<?php print $link_attachments; ?>
*/

/*
ad a class="" if we have anything in the $classes var
this is so we can have a cleaner output - no reason to have an empty <div class="" id=""> 
*/
if($classes){
   $classes = ' class="'. $classes . '"';
}

if($id_node){
  $id_node = ' id="'. $id_node . '"';  
}

global $user;
if ($user->uid==1) {
	echo "<pre>";
	print_r($user);
	echo "</pre>";
}

?>

<?php
	//foreach ($node->links as $link_id => $link) {
	  // we only want to move this bad boy out of $links if it is an actually link
	  // theme('links') can accept 'links' without href  ->  http://api.drupal.org/api/function/theme_links/6
	  //if (isset($link['href'])) {
	  //  $vars["{$link_id}_link"] = l($link['title'], $link['href'], $link);
	  //}
	//}
?>

<?php if ($page == 0){ ?>
<?php
global $user;
if ($user->uid==1) {
	echo "<pre>";
	print_r($user);
	echo "</pre>";
}
?>
<div<?php print $id_node . $classes; ?>>
	

	<?php if($node->title){	?>	
    <h2><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
	<?php } ?>

	<?php if ($node->picture) { ;?>
    <?php print theme('imagecache', 'preset_namespace', $node->picture, $alt, $title, $attributes); ?>
	<?php } ?>
	
	<div class="meta">
	<?php print theme('username', $node); ?>

	<?php print format_date($node->created, 'custom', "j F Y") ?> 
	</div>
	<?php print $content;?>	

	
  <?php if ($links){ ?>
  <div class="node-links">
    <?php print $links; ?>
   </div>
  <?php }; ?>
	  
</div>
	
<?php }else{ 
//Content
?>

<div<?php print $id_node . $classes; ?>>

	<h2><?php print $title;?></h2>		
  	
  
  <?php if ($submitted){ ?>
  	<?php if ($picture) { ;?>
  		<?php print $picture; ?>  
	  <?php } ?>
	<div class="author-info">
	  <?php print theme('username', $node); ?>

		<?php print format_date($node->created, 'custom', "j F Y") ?> 
		</div>
  <?php } ?>

	<?php if (count($taxonomy)){ ?>
	<div class="tags">
   	<?php print $terms ?>
   	</div> 
	<?php } ?>

	<?php print $content ?>

	<?php

		// Removed How to get more help paragraph
		// $channel = $node->field_bgn_story_channel;
		// if ($channel[0]['value']=='78') {
		//	print "<h3> How to get more help</h3><p class='online-advisors'>For confidential advice and support, get in touch with our expert <a href='/online-advisors'>online advisors</a>.</p>";
		// }
	?>
	<?php print $node_region_two;?>	

	<?php print $node_region_one;?>
		
	<?php if ($links){ ?>
	<div class="node-links">
    <?php  print $links; ?>
    </div>
	<?php } ?>
</div>
<?php } ?>