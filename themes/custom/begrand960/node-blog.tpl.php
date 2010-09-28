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
<?php
	$node_author=user_load($node->uid);
	$author_class="";
	
	if (array_search("administrator",$node_author->roles )) {
		$author_class="-begrand";
	}
	if (array_search("Community manager",$node_author->roles )) {
		$author_class="-begrand";
	}
	if (array_search("contributor",$node_author->roles )) {
		$author_class="-begrand";
	}

?> 
<?php if ($page == 0){ ?>
<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?> post<?php print $author_class;?> clear-block">
	

	<?php if($node->title){	?>	
    <h3><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h3>
	<?php } ?>
<div class="meta post-info">
	<?php if ($submitted): ?>
	<p class="submitted<?php print $author_class; ?>">Posted by <?php print theme('username', $node); ?> on <?php print date('d M Y', $node->changed); 
	if ($author_class!=""){ echo "<br/><strong>BeGrand.net staff member</strong>";}
	?></span>
	  <?php endif; ?>
	 
  <?php if ($terms): ?>
    <div class="terms terms-inline"><?php print $terms ?></div>
  <?php endif;?>
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
<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?> post<?php print $author_class;?> clear-block">

	<h2><?php print $title;?></h2>		
  <div class="meta post-info">
	<?php if ($submitted): ?>
	<p class="submitted<?php print $author_class; ?>">Posted by <?php print theme('username', $node); ?> on <?php print date('d M Y', $node->changed); 
	if ($author_class!=""){ echo "<br/><strong>BeGrand.net staff member</strong>";}
	?></p>
	  <?php endif; ?>
	 
  <?php if ($terms): ?>
    <div class="terms terms-inline"><?php print $terms ?></div>
  <?php endif;?>
</div>


	<?php print $content ?>

	<?php print $node_region_two;?>	

	<?php print $node_region_one;?>
		
	<?php if ($links){ ?>
	<div class="node-links">
    <?php  print $links; ?>
    </div>
	<?php } ?>
</div>
<?php } ?>