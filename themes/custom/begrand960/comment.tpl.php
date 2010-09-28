<?php
/*
 * These two variables are provided for context.
 * - $comment: Full comment object.
 * - $node: Node object the comments are attached to.
 *
 * @see template_preprocess_comment()
 * @see theme_comment()
 */
?>

<?php
/*
ad a class="" if we have anything in the $classes var
this is so we can have a cleaner output - no reason to have an empty <div class="" id=""> 
*/
if($classes){
   $classes = ' class="' . $classes . '"';
}


$user_load = user_load($array = array('uid' => $node->uid));
if (in_array('Community manager', array_values($user_load->roles))) {
	$commentclass="admin-comment";
} else {
	$commentclass="comment";
}



?>
<?php
	
	$node_author=user_load($comment->uid);
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
<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?> post<?php print $author_class;?> clear-block">
	<div class="<?php print $commentclass; ?>">
	  <h3><?php print $title ?></h3>
	  <?php print $picture ?>    
	  	<div class="meta post-info">
		<?php if ($submitted): ?>
		<p class="submitted<?php print $author_class; ?>">Posted by <?php print theme('username', $comment); ?> on 
		<?php 
			print date('d M Y', $comment->timestamp); 
			if ($author_class!=""){ 
				echo "<br/><strong>BeGrand.net staff member</strong>";
			}
		?>
		</p>
	</div>
	  <?php endif; ?>
	  
	 
	  <?php if ($comment->new): ?>
	    <?php print $new ?>
	  <?php endif; ?>
	
	  <?php print $content ?>
	
	  <?php if ($signature): ?>
	    <?php print $signature ?>
	  <?php endif; ?>
	
	  <div class="comment-links">
	  <?php print $links ?> 
	  </div>
	</div>     
</div>

