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
//Content
?>

<script type="text/javascript" src="http://openspace.ordnancesurvey.co.uk/osmapapi/openspace.js?key=8AB64CFFBE92E0A2E0405F0AC86068B8"></script> 

<div<?php print $id_node . $classes; ?>
<?php 
	
	// Build nice balloon...
	$balloon  ="<p><img src=\"/".$node->picture."\" width=\"50\" height=\"50\"><br/><strong>".$title."</strong><br/>";
	$balloon .="Organised by ".$node->name."</p>";
?>
	<a class="map-link tipTip" href="#map" title="Click to scroll to map of location">Map</a>
	<h2><?php print $title;?> (<?php print $location['postal_code']; ?>)</h2>		
  
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
	<h3>Map</h3>
	<div id="map"></div>
	<script type="text/javascript">
		
		function onResult(mapPoint) {
			osMap.setCenter(mapPoint, 7);
/* 			var marker = osMap.createMarker(mapPoint); */
			var content = '<?php print $balloon; ?>';
    		var marker = osMap.createMarker(mapPoint, null, content);

		}

		var osMap, postcodeService;
		osMap = new OpenSpace.Map('map');
		markers = new OpenLayers.Layer.Markers("Markers");
		osMap.addLayer(markers);
		postcodeService = new OpenSpace.Postcode();
		postcodeService.getLonLat("<?php print $location['postal_code']; ?>", onResult);
		
	</script>
	</div>
	
	<?php print $node_region_two;?>	

	<?php print $node_region_one;?>
		
	<?php if ($links){ ?>
	<div class="node-links">
    <?php  print $links; ?>
    </div>
	<?php } ?>

<?php } ?>