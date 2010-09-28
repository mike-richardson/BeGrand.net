<?php

/* 
	-----------------------------------------------------------------------------------------------------------

	@file 		user-profile.tpl.php
	@version 	1.31
	@date 		2010-04-16 (Fri, 16 Apr 2010)
	@author 	Mike Richardson <mikel@begrand.net>

	Copyright (c) 2010 BeGrand.net <http://begrand.net>

*/


	$extprofile['role']="user";
	if (in_array("administrator",$account->roles)) {
		$extprofile['role']="team";
	}
	if (in_array("contributor",$account->roles)) {
		$extprofile['role']="team";
	}
	
	if (in_array("Community manager",$account->roles)) {
		$extprofile['role']="team";
	}
	
	$shoutstr="update";
	$sql=sprintf("SELECT shouts.message FROM shouts WHERE shouts.uid=%d ORDER BY shouts.time DESC", $account->uid);
	$result = db_query($sql, $shout);
	while ($shouts = db_fetch_object($result)) {
        $shout[] = $shouts->message;
    }
	$latest_shout=$shout[0];
	$sql=sprintf("SELECT content_type_profile.field_bgn_pro_first_value, content_type_profile.field_bgn_pro_surname_value, content_type_profile.field_bgn_pro_about_value, content_type_profile.field_bgn_pro_city_value FROM node INNER JOIN content_type_profile ON node.nid = content_type_profile.nid WHERE node.uid=%d", $account->uid);
	$result = db_query($sql, $extprofile);
	while ($fields = db_fetch_object($result)) {
        $extprofile['first'] = $fields->field_bgn_pro_first_value;
        $extprofile['surname'] = $fields->field_bgn_pro_surname_value;
        $extprofile['about'] = $fields->field_bgn_pro_about_value;
		$extprofile['city'] = $fields->field_bgn_pro_city_value;
    }
    
    if ($extprofile['about']=="") {
    	$extprofile['about']="<p>This user has not entered a profile description yet</p>";
    }
        
    // Blog posts...
    $sql=sprintf("SELECT count(nid) AS blog_posts FROM node INNER JOIN users ON users.uid = node.uid WHERE users.uid =%d AND node.type='blog' AND node.status='1'", $account->uid);
	$result = db_query($sql, $blog_posts);
	while ($fields = db_fetch_object($result)) {
		$extprofile['blog_posts'] = $fields->blog_posts;
    }
    
    // Group posts
    $sql=sprintf("SELECT count(nid) AS group_posts FROM node INNER JOIN users ON users.uid = node.uid WHERE users.uid =%d AND node.type='bgn_group_post' AND node.status='1'", $account->uid);
	$result = db_query($sql, $group_posts);
	while ($fields = db_fetch_object($result)) {
		$extprofile['group_posts'] = $fields->group_posts;
    }

    // Comments
    $sql=sprintf("SELECT count(cid) AS comments FROM comments INNER JOIN users ON comments.uid = users.uid WHERE comments.uid=%d", $account->uid);    
	$result = db_query($sql, $comments);
	while ($fields = db_fetch_object($result)) {
       	$extprofile['comments'] = $fields->comments;
    }
    
    // Shouts
    $sql=sprintf("SELECT count(shout_id) AS shouts FROM shouts WHERE uid=%d", $account->uid);    
	$result = db_query($sql, $shouts);
	while ($fields = db_fetch_object($result)) {
        $extprofile['shouts'] = $fields->shouts;
    }
    

    // Galleries
    $sql=sprintf("SELECT count(nid) AS galleries FROM node WHERE uid=%d AND status=1 AND type='node_gallery_gallery'", $account->uid);    
	$result = db_query($sql, $galleries);
	while ($galleries = db_fetch_object($result)) {
        $extprofile['galleries'] = $galleries->galleries;
    }

    // Photos
    $sql=sprintf("SELECT count(nid) AS photos FROM node WHERE uid=%d AND status=1 AND type='node_gallery_image'", $account->uid);    
	$result = db_query($sql, $photos);
	while ($photos = db_fetch_object($result)) {
        $extprofile['photos'] = $photos->photos;
    }

	$ext_stats=	"<ul class='extended-stats'>";
	
    // Member since
    $extprofile['membersince']="<li class='member-since'>Joined ".format_date($account->created, 'custom', 'M j Y')."</li>";
    
    // Build extended stats list...
    $ext_stats.=$extprofile['membersince'];
    if ($extprofile['blog_posts']>0) {
    	$ext_stats.="<li class='blog-posts'>".$extprofile['blog_posts'];
    	if ($extprofile['blog_posts']==1){
    		$ext_stats.=" blog entry</li>";
    	} else {
    		$ext_stats.=" blog entries</li>";
    	}
    }
    if ($extprofile['group_posts']>0) {
    	$ext_stats.="<li class='group-posts'>".$extprofile['group_posts'];
    	if ($extprofile['group_posts']==1){
    		$ext_stats.=" group post</li>";
    	} else {
    		$ext_stats.=" group posts</li>";
    	}
    }	
    if ($extprofile['comments']>0) {
    	$ext_stats.="<li class='comments'>".$extprofile['comments'];
    	if ($extprofile['comments']==1){
    		$ext_stats.=" comment</li>";
    	} else {
    		$ext_stats.=" comments</li>";
    	}
    }
    
    
    // Galleries & photos
    if ($extprofile['galleries']>0) {
    	$ext_stats.="<li class='galleries'>".$extprofile['photos'];
    	if ($extprofile['photos']==1){
    		$ext_stats.=" photo in ";
    	} else {
    		$ext_stats.=" photos in ";
    	}
    	if ($extprofile['galleries']==1){
    		$ext_stats.=$extprofile['galleries']." gallery</li>";
    	} else {
    		$ext_stats.=$extprofile['galleries']." galleries</li>";
    	}
    	
    }
    
    
    if ($extprofile['shouts']>0) {
    	$ext_stats.="<li  class='shouts'>".$extprofile['shouts'];
    	if ($extprofile['shouts']==1){
    		$ext_stats.=" $shoutstr</li>";
    	} else {
    		$ext_stats.=" ".$shoutstr."s</li>";
    	}
    	
    }
    $ext_stats.="</ul>";
    
    // Show latest shout if available
	if ($latest_shout!="") {
		echo "<div class='latest-shout'><div>$latest_shout</div></div>"; 
	}
?>
<div class="content-profile-display <?php print $extprofile['role']; ?>" id="content-profile-display-profile">	
	<?php if ($account->picture!="") { ?>
		<img src="/<?php print $account->picture; ?>" class="right">
	<?php } ?>	<h2><?php print $account->name; ?></h2>
	<p>
	<?php print $extprofile['about']; ?></p>
	<?php
	$time_period = variable_get('user_block_seconds_online', 2700);
	$uid = $account->uid; // get the current userid that is being viewed.
	if ($account->access > time() - $time_period) {
		echo "<p class='user-online'>I'm online</li>";
	} else {
		echo "<p class='user-offline'>I'm offline</li>";
	}
	echo "</div>";
if ($logged_in && ($account->uid!=$user->uid)) {
 	echo "<h3>Actions</h3>";
	$relationship="none";
	echo "<ul class='profile-actions'>";
	if ($extprofile['blog_posts']>0){
		echo "<li class='view-blog'><a href='/blog/".$account->uid."'>View recent blog entries</a></li>";
	}
	echo "<li class='private-message'><a href='/messages/new/".$account->uid."?destination=user%2F".$account->uid."'>Send private message</a></li>";
	
	if ($relationships = user_relationships_load(array('between' => array($user->uid, $account->uid),'approved' => 0))) { 
		$relationship="pending";
		echo "<li class='friend-pending'>You have a pending friend request with ".$account->name."</li>";
	}
	
	if	($relationships = user_relationships_load(array('between' => array($user->uid, $account->uid),'approved' => 1))) { 
		$relationship="friend";
		echo "<li class='friend-approved'>You are friends with ".$account->name."</li>";
	}
	
	if ($relationship=="none") {
		echo "<li class='friend-request'><a href='/relationship/".$account->uid."/request/1?destination=user%2F".$account->uid."'>Become ".$account->name."'s friend</a></li>";
 	} 	
	echo "</ul>";
}
?>
<?php 
	echo "<h3>Statistics</h3>";
	echo $ext_stats;

	if ($user->uid==$account->uid) { 

		echo "<h3>Your groups</h3>";
		echo "<ul class=\"profile-groups\">";
		
		$groups = $account->og_groups;
		if($groups){
		    foreach($groups as $group){
		    echo "<li>";
		        print l($group[title], 'node/'.$group[nid]);
		    echo "</li>";
		    }
		}
		else {
		    echo "<li>You haven't joined any groups</li>";
		}
		echo "</ul>";
	}

	if ($extprofile['shouts']>0) {
		echo "<h3>Recent ".$shoutstr."s</h3>";
		echo "<ul class='recent-shouts'>";
	  	$nlimit = 5;
	  	$sql=sprintf("SELECT message AS message FROM shouts WHERE uid=%d LIMIT %d", $account->uid, $nlimit);
	  	$result = db_query($sql, $shouts);
	  	while ($shouts = db_fetch_object($result)) {
	  		if ($shouts->message!="") {
        		echo "<li>".$shouts->message."</li>";
        	}
	    }
	  	echo "</ul>";
	 }
	 
	 
	 if ($extprofile['photos']>0) {
		echo "<h3>Recent galleries</h3>";
		echo "<ul class='recent-galleries'>";
  		$nlimit = 5;
  		//Get all the users galleries...
		$sql=sprintf("SELECT * FROM node WHERE type='node_gallery_gallery' AND uid=%d LIMIT %d" , $account->uid, $nlimit);
		$result=db_query($sql, $galleries);
  		while ($galleries = db_fetch_object($result)) {
			echo "<li><a href='/node/".$galleries->nid."'>".$galleries->title."</a></li>";
	    }
	    echo "</ul>";
	    
	    // Get the users pictures next...
	    echo "<h3>Recent photos</h3>";
		echo "<ul class='recent-photos'>";
  		$nlimit = 4;
	    $sql=sprintf("SELECT node.nid, node.title, node_galleries.gid FROM node INNER JOIN node_galleries ON node.nid = node_galleries.nid WHERE node.type IN ( 'node_gallery_image' ) AND node.uid = %d ORDER BY node_galleries.gid ASC LIMIT %d", $account->uid, $nlimit);
	    $result=db_query($sql, $photos);
  		while ($photos = db_fetch_object($result)) {
  			// Check the thumbnail exists
  			$thumbpath="/var/www/pressflow/sites/default/files/imagecache/thumbnail/".$account->uid."/".$photos->gid."/".$photos->title;
  			if (!file_exists($thumbpath)) {
  				// Add a jpg extension if its missing
  				$thumbfile="/sites/default/files/imagecache/thumbnail/".$account->uid."/".$photos->gid."/".$photos->title.".jpg";
  			} else {
  				$thumbfile="/sites/default/files/imagecache/thumbnail/".$account->uid."/".$photos->gid."/".$photos->title;
  			}
			if (file_exists("/var/www/pressflow".$thumbfile)) {
				echo "<li><a href='/node/".$photos->nid."'><img src='$thumbfile'/></a></li>";
			}
	    }
	    echo "</ul>";	    
	    
	    //SELECT node_galleries.nid FROM node_galleries WHERE gid=%d//
		
		
  		$sql=sprintf("SELECT nid, title FROM node WHERE type='node_gallery_image' AND uid=%d ORDER BY changed DESC LIMIT %d", $account->uid, $nlimit);
  		$result=db_query($sql, $photos);
  		while ($photos = db_fetch_object($result)) {
			//echo "<li><a href='/node/".$photos->nid."'><img src='/sites/default/files/imagecache/thumbnail/".$account->uid."/".$photos->nid."/".$photos->title."'></img></a></li>";
	    }
  		echo "</ul>";
	} 
 	
 	if ($extprofile['photos']>0) {
		//echo "<h3>Recent pictures</h3>";
		//echo "<ul class='recent-pictures'>";
  		$nlimit = 5;
  		$sql=sprintf("SELECT nid, title FROM node WHERE type='node_gallery_image' AND uid=%d ORDER BY changed DESC LIMIT %d", $account->uid, $nlimit);
  		$result=db_query($sql, $photos);
  		while ($photos = db_fetch_object($result)) {
		//	echo "<li><a href='/node/".$photos->nid."'><img src='/sites/default/files/imagecache/thumbnail/".$account->uid."/".$photos->nid."/".$photos->title."'></img></a></li>";
	    }
  		//echo "</ul>";
	 }
	 
	 
	 
	if ($extprofile['blog_posts']>0) {
		echo "<h3>Recent blog posts</h3>";
		echo "<ul class='recent-blog-entries'>";
	  	$nlimit = 5;
	  	$result = db_query_range(db_rewrite_sql("SELECT n.created, n.title, n.nid, n.changed FROM {node} n WHERE n.uid = %d AND n.type='blog' AND n.status = 1 ORDER BY n.changed DESC"), $account->uid, 0, $nlimit);
	  	while ($entries = db_fetch_object($result)) {
        	echo "<li><a href='/node/".$entries->nid."'>".$entries->title."</a></li>";
	    }
	  	echo "</ul>";
	 }
	 
	 
	 
	if ($extprofile['group_posts']>0) {
		echo "<h3>Recent group posts</h3>";
		echo "<ul class='recent-group-posts'>";
	  	$nlimit = 5;
	  	$sql=sprintf("SELECT node.nid AS nid, node.title AS node_title, og_ancestry.group_nid FROM node node  LEFT JOIN og_ancestry og_ancestry ON node.nid = og_ancestry.nid INNER JOIN node node_og_ancestry ON og_ancestry.group_nid = node_og_ancestry.nid LEFT JOIN og_access_post og_access_post ON node.nid = og_access_post.nid WHERE (node.type in ('bgn_group_post')) AND (og_access_post.og_public <> 0) AND node.uid = %d AND node.status=1 GROUP BY node.nid ORDER BY node.created DESC LIMIT %d", $account->uid, $nlimit);
		$result = db_query($sql, $gposts);
	  	while ($gposts = db_fetch_object($result)) {
	  		$gsql=sprintf("SELECT node.title FROM node WHERE node.nid=%d",$gposts->group_nid);
	  		$gresult = db_query($gsql, $gtitles);
	  		while ($gtitles = db_fetch_object($gresult)) {
	  			$gtitle=$gtitles->title;
	  		}
        	echo "<li><a href='/node/".$gposts->nid."'>".$gposts->node_title."</a> in <em>$gtitle</em></li>";
	    }
		echo "</ul>";
	}	 
	 
	if ($extprofile['comments']>0) {
		echo "<h3>Recent comments</h3>";
		echo "<ul class='recent-comments'>";
	  	$nlimit = 5;
	  	$sql=sprintf("SELECT comments.cid, comments.nid AS comments_nid, comments.subject AS comments_subject, node.title FROM node INNER JOIN comments ON node.nid = comments.nid WHERE ( comments.status = 0 ) AND ( comments.uid = %d )ORDER BY comments.timestamp DESC LIMIT %d", $account->uid, $nlimit);
	  	$result = db_query($sql, $comments);
		while ($comments = db_fetch_object($result)) {
			echo "<li><a href='/node/".$comments->comments_nid."#comment-".$comments->cid."'>".$comments->comments_subject."</a> in response to <em>".$comments->title."</em></li>";
    	}
	  	echo "</ul>";
	 }
	 
	 $latestphotos="SELECT title FROM node WHERE type='node_gallery_image' AND uid=%d ORDER BY changed DESC LIMIT 6";

?>


