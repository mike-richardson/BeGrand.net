// $Id: ajax_slideshow.js,v 1.1 2009/10/17 12:43:31 udig Exp $

/**
 * ajax_slideshow js code. basically it iterates all the nids inside the page, loading each node using ajax call.
 */
 
var index = 0;
var max = 0;
var nodes = new Array();
var current = 0;
var previous = 0;

/**
 * First step : Initialization
 * 1. Make sure at least 1 nid was returned by the view.
 * 2. Attach the placeholders (node-content0 and node-content1) for the nodes display.
 * 3. Iterate through the nids and make asynchronous call to the function which returns the nodes.
 * 4. While the asynch calls are on their way call the display function.
 */
Drupal.behaviors.ajax_slideshow = function() {
  max = $('span.field-content').size();
  if (max>0) {
    $('#default-content').append('<div id="slideshow-output-wrapper"><div id="node-content0"></div><div id="node-content1"></div></div>');
    $('span.field-content').each( function(i){
      nid = $('span.field-content').eq(i).text();
      $.get('/photos/get/photos/'+nid, null, function(data){
        var result = Drupal.parseJson(data);
        nodes[i] = result['node'];
      });
    });
    displayNodes();    
  }
}

/**
 * This function presents the nodes presumably brought back and saved inside the nodes array.
 * Since we are not sure if the data is ready yet(asynch calls) we check that the data exists before presenting it
 */
function displayNodes() {
  mod_index = index%max;
  // ensure the node already returned. 
  if (nodes[mod_index]) { 
    current = index % 2;
    previous = 1 - current;
    //first we render the node to the screen
    $('#node-content' + current).html(nodes[mod_index]);
    //then we wait for a second and uncover it switching from the current presented node to the newly rendered one.
    setTimeout("switchNodes()", 1000);
  } else {
    // if the nodes were not returned yet (from the server), try again in half a second.
    setTimeout("displayNodes()", 500);
  }
}

/**
 * Fade out the current shown node and fade in the newly rendered node.
 * if this is the first slide - hide the intro page.
 * Render the next slide past the interval asked by the admin.
 */
function switchNodes(){
  $('#node-content' + previous).fadeOut(2000);
  $('#node-content' + current).fadeIn(2000);

  // after the first slide kicked in we need to hide the intro slide.
  if (index == 0) {
    $('#slideshow-front-content').fadeOut(2000);
  }

  index++;
  setTimeout("displayNodes()", Drupal.settings.ajax_slideshow.slide_duration);
}

