<?php

// **********************************************
// Modified by Mike Richardson (mike@begrand.net) 
// Date: Monday 26 Apr 2010
// **********************************************

if($classes){
   $classes = ' class="'. $classes . '"';
}

if($id_node){
  $id_node = ' id="'. $id_node . '"';  
}

$baloon="<p><strong>".$node->title."</strong></p>";

if ($page == 0){

?>
<h3>Event in <?php print $location->postal_code; ?></h3>

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
// Content
// Heavily modified for BeGrand.net by mike@begrand.net
?>


<div<?php print $id_node . $classes; ?>>
	<?php
		
		// Display a meesage if the event isn't free
	
		if($node->field_bgn_event_cost['0']['value']=="Yes") {
			echo "<p class=\"money\">This event is not free to attend, see <a href=\"#pricing\">how much it costs</a>.</p>";
		}
	?>
	<h2><?php print $title;?></h2>		
  
		<?php 
	
		// Creates the organisation details if it has been set
		// Friday July 9, 2010 - mike@begrand.net
	
		$related=$node->field_bgn_event_org['0'];

		if (!is_null($related['nid'])) {
			// echo "<p class=\"event-organised-by\">This is event is organised by ".$node->field_bgn_event_org['0']['view']."</p>";
			$result = db_query('SELECT node_revisions.body, node_revisions.title, files.filepath FROM content_type_event_organisers INNER JOIN node_revisions ON content_type_event_organisers.nid = node_revisions.nid INNER JOIN files ON content_type_event_organisers.field_bgn_org_logo_fid = files.fid WHERE content_type_event_organisers.nid = '. $related['nid']);
			if ($result) {
				while ($data = db_fetch_object($result)) {
					$org_name=$data->title;
					$org_logo=$data->filepath;
					$org_description=$data->body;
				}
			}		
			//$showmore="/events/organised-by?org_nid=".$node->field_bgn_event_org['0']['nid'];
			$about_org="<div class=\"about-event-org\"><h3>Organised by $org_name</h3><img src=\"/$org_logo\" class=\"right\"/>$org_description</div>";

		} else {
			$about_org="";
		}
	 ?>
	 
	<p class="event-type <?php echo $node->field_bgn_event_type['0']['value']; ?>"><?php echo $node->field_bgn_event_type['0']['view']; ?></p>
	
	<p class="event-date"><?php echo $node->field_bgn_event_date['0']['view']; ?></p>
	<a href="#map" class="map-link">View map</a>	 

	<p class="event-location"><?php echo $node->location['name']; ?><br/>
	<?php 
	
		// Build the address nicely without empty lines
		
		if ($node->location['street']) {
			echo $node->location['street']."<br/>";
		}
		if ($node->location['additional']) {
			echo $node->location['additional']."<br/>";
		}
		if ($node->location['city']) {
			echo $node->location['city']."<br/>";
		}
		if ($node->location['province_name'])  {
			echo $node->location['province_name']."<br/>";
		}
		echo $node->location['postal_code']."</p>";
	?> 
	
	<h3>Description</h3>
	<?php print $node->body; ?>
	<p><?php echo $node->field_bgn_event_url['0']['view']; ?></p>

	<h3><a name="map"></a>Map</h3>
	<div id="event-map"></div>
	<!- Is this being read?! -->
  
   	<!- Google maps v3 implementation -> 
  	<script type="text/javascript" src="http://maps.google.com/maps/api/js?sensor=false"></script>
  	<!- extInfowWindow stuff as well... -->
  	<script src="/sites/all/modules/gmap/thirdparty/extinfowindow/extinfowindow_packed.js" type="text/javascript"></script>
  	
  	<script type="text/javascript">
	  	var latlng = new google.maps.LatLng(<?php print $node->location['latitude']; ?>, <?php print $node->location['longitude']; ?>);  
		// Creating an object literal containing the properties we want to pass to the map  
		var options = {  
  			zoom: 11,  
  			center: latlng,  
			mapTypeId: google.maps.MapTypeId.ROADMAP  
		};  
		// Calling the constructor, thereby initializing the map  
		var map = new google.maps.Map(document.getElementById('event-map'), options); 
		// Set the marker...
		// var image= "/sites/all/modules/gmap/markers/bg_flag_pin.png";
		 var image = new google.maps.MarkerImage('/sites/all/modules/gmap/markers/bg_flag_pin.png',
      	// This marker is 20 pixels wide by 32 pixels tall.
      		new google.maps.Size(24, 32),
      		// The origin for this image is 0,0.
      		new google.maps.Point(0,0),
      		// The anchor for this image is the base of the flagpole at 0,32.
      		new google.maps.Point(0, 32));
		var shadow = new google.maps.MarkerImage('/sites/all/modules/gmap/markers/bg_pin_shadow.png',
     		// The shadow image is larger in the horizontal dimension
      		// while the position and offset are the same as for the main image.
      		new google.maps.Size(36, 32),
      		new google.maps.Point(0,0),
      		new google.maps.Point(0, 32));
      		// Shapes define the clickable region of the icon.
     		// The type defines an HTML <area> element 'poly' which
      		// traces out a polygon as a series of X,Y points. The final
      		// coordinate closes the poly by connecting to the first
      		// coordinate.
	  	var shape = {
	      	coord: [1, 1, 1, 20, 18, 20, 18 , 1],
	      	type: 'poly'
	  	};
		var marker = new google.maps.Marker({
      		position: latlng, 
      		map: map, 
      		icon: image,
      		shadow: shadow,
      		shape: shape,
      		title:"<?php echo $node->location['name']; ?>"
  		});  
  		// Build the info window
  		//var contentString = '<div class="title"><?php echo $node->location['name']; ?></div>';

		//var infowindow = new google.maps.InfoWindow({
    	//	content: contentString
		//});
		//google.maps.event.addListener(marker, 'click', function() {
  		//	infowindow.open(map,marker);
		//});
	
	</script> 
  
    <form action="http://maps.google.com/maps" method="get" target="_blank" id="event-directions">
    	<div>
			<label for="start-address">Enter your post code:</label>
			<input  class="form-text" type="text" name="saddr" id="start-address"/>
			<input type="hidden" name="t" value="m"/>
			<input type="hidden" name="daddr" value="<?php echo $node->location['postal_code']; ?>" />
			<input type="submit" value="Get directions" class="form-submit" />
		</div>
	</form>
	<?php
	
		// Display costs with an anchor
				
		if($node->field_bgn_event_cost['0']['value']=="Yes") {
			echo "<h3><a name=\"pricing\"></a>How much does it cost?</h3>";
			echo $node->field_bgn_event_cost_details['0']['view'];
		}
	?>
	
	<?php print $about_org ?>

	</div>
	
	<?php print $node_region_two;?>	

	<?php print $node_region_one;?>
		
	<?php if ($links){ ?>
	<div class="node-links">
    <?php  print $links; ?>
    </div>
	<?php } ?>

<?php } ?>