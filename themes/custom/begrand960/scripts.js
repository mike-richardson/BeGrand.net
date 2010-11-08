$(document).ready(function() {
		
	
        $('#main-content a').filter(function() {
         return this.hostname && this.hostname !== location.hostname;
        }).addClass('external-link');
        $('#main-content .buzzthis_button a').filter(function() {
         return this.hostname && this.hostname !== location.hostname;
        }).removeClass('external-link');
        
        
        $('.external-link').attr('rel', 'nofollow');
        
        
        $("a[href$='pdf']").addClass("pdf-link"); 
        $("a[href$='csv']").addClass("csv-link");
        $("a[href^='mailto']").addClass("mail-link"); 
        $("a[href^='/messages/new/']").addClass("message-link"); 
        $("a[href^='/podcasts']").addClass("podcast-link"); 
        $("#main-content .content p a[href^='/groups/']").addClass("groups-link");
        $("td a[href^='/og/subscribe/']").addClass("groups-join-link");
      	$("a[href^='/flag/']").addClass("flag_content"); 
      	
      	
      	
      	$("a[href^='/flag/flag/attendance']").addClass("tipTip"); 
      	$(".date-nav a").addClass("tipTip");
      	$("#main-content .rsvp_form_content a").addClass("tipTip");
      	$("#edit-submit-bgn-events-by-event-type").addClass("tipTip");
      	
      	$("#sidebar-left a[href^='/users/']").addClass("your-account"); 
      	$("#sidebar-left a[href^='/messages']").addClass("your-messages");
      	$("#sidebar-left a[href^='/blog/']").addClass("your-blog");
      	$("#sidebar-left a[href^='/relationships/']").addClass("your-friends");
      	$("#sidebar-left a[href^='/galleries']").addClass("photo-galleries");
      	$("#sidebar-left a[href^='/node/add/node-gallery-gallery']").addClass("add-photo-gallery");
      	$("#sidebar-left a[href^='/node/add/node-gallery-image']").addClass("add-image");
      	$("#sidebar-left a[href^='/logout']").addClass("log-out");
      	
      	$("#loggedin_status div a[href^='/logout']").addClass("log-out");
      	$("#loggedin_status a[href^='/users/']").addClass("your-account");
      	
      	$("#sidebar-left a[href='/local']").addClass("events-home");
      	$("#sidebar-left a[href^='/node/add/event']").addClass("add-event");
      	$("a[href^='/local/listings']").addClass("view-events-list");
      	$("a[href^='/local-calendar']").addClass("view-events-calendar");
      	$("#sidebar-left a[href^='/events-by-city']").addClass("events-by-city");
      	$("#sidebar-left a[href^='/local/type']").addClass("events-by-type");
      	$("#sidebar-left a[href^='/article/news/whats']").addClass("help-link");
      	
      	$("#site-menu a[href='/local']").addClass("events-menu-link");
      	
      	$("a[href^='/rsvp/create']").addClass("create-invitation");
      	$("a[href^='/signup/cancel']").addClass("cancel-signup");
      	
      	
      	$("#group-tools a[href^='/node/add/poll']").addClass("group-poll"); 
      	$("#group-tools a[href^='/node/add/bgn-group-post']").addClass("group-post"); 
      	$("#group-tools a[href^='/node/add/cck-gallery']").addClass("group-gallery"); 
      	$("#group-tools a[href^='/og/invite']").addClass("group-invite");
      	$("#group-tools a[href^='/og/users']").addClass("group-members");
      	$("#group-tools a[href^='/og/manage']").addClass("manage-membership");
      	
      	$(".blue-box p:last-child").addClass("last-child");
      	
      	
      	
      	$('#edit-distance-postal-code').attr('title', 'You only need to enter the first part of your postcode, for example "CB24"');
      	
      	$('#edit-submit-bgn-events-by-event-type').attr('title', 'Make sure you have entered your post code and a distance');
      	
      	$("#site-menu a").tipTip();
      	$("#sidebar-left  a").tipTip();
      	$("#your-begrand a").tipTip();
      	$(".tipTip").tipTip();
      	$(".form-required").tipTip();
      	$(".node-links a").tipTip();
      	$(".csv-link").tipTip();
      	$("#edit-distance-postal-code").tipTip();
      	
      	$(".gmap img").tipTip();
      	
      	$("img.right").tipTip({position:'right'});
      	$("img.left").tipTip({position:'left'});
      	
      	
      	$(".view-tracker").jScrollPane();
      	$(".twtr-timeline").jScrollPane();
      	
      	$(".stripes tbody tr:odd").addClass("odd");
      	$(".stripes tbody tr:even").addClass("even");
      	
      	
      	$(".front .blue-box img").addClass("corner").addClass("iradius5");
      	
      	$(".views-slideshow-controls-bottom img").addClass("corner").addClass("iradius5");
      	$(".field-slideshow-image-fid img").addClass("corner").addClass("iradius10");
      	
      	$("p.event-type:contains('Art and culture')").addClass("art");
      	$("p.event-type:contains('Childcare')").addClass("childcare");
      	$("p.event-type:contains('Days out')").addClass("dayout");
      	$("p.event-type:contains('Education and training')").addClass("education");
      	$("p.event-type:contains('Places to go')").addClass("places");
      	$("p.event-type:contains('Social')").addClass("social");
      	$("p.event-type:contains('Sport and activity')").addClass("sport");
      	$("p.event-type:contains('Support groups')").addClass("support");
      	
      	$(".field-etype:contains('Art and culture')").addClass("art");
      	$(".field-etype:contains('Childcare')").addClass("childcare");
      	$(".field-etype:contains('Days out')").addClass("dayout");
      	$(".field-etype:contains('Education and training')").addClass("education");
      	$(".field-etype:contains('Places to go')").addClass("places");
      	$(".field-etype:contains('Social')").addClass("social");
      	$(".field-etype:contains('Sport and activity')").addClass("sport");
      	$(".field-etype:contains('Support groups')").addClass("support");
      	
      	$("#sidebar-left div:contains('Events menu')").addClass("events-menu");
      	$("#sidebar-right div:contains('Upcoming events')").addClass("upcoming-events");
      	
        $('#edit-distance-search-units-wrapper').replaceWith('<span class="miles">Miles</span>');
        
        $('body.path-event #edit-title-wrapper label').replaceWith('<label for="edit-title">Name of activity <span class="form-required">*</span></label>');
        
        $('body.path-event #edit-locations-0-province-wrapper label').replaceWith('<label for="edit-locations-0-province">County</label>');
        
        $('body.path-event #edit-body-wrapper label').replaceWith('<label for="edit-body">Description of activity</label>');
        
        
        
       
        
        $('<h2>Add your listing</h2>').insertBefore('body.path-event #node-form');
        
        
        $('<h3 class="left">Filter activities by type</h3>').insertBefore('#views-exposed-form-bgn-events-by-type-page-1');
        
        $('.bef-select-all-none').attr('checked','checked');
        $(".bef-toggle").text('Select None');
        
        $('.bef-toggle').attr('title','Please select at least one event type!');
        $('.views_slideshow_singleframe_pager .pager-num-1 img').attr('title','Slide 1');
        $('.views_slideshow_singleframe_pager .pager-num-2 img').attr('title','Slide 2');
        $('.views_slideshow_singleframe_pager .pager-num-3 img').attr('title','Slide 3');
        $('.views_slideshow_singleframe_pager .pager-num-4 img').attr('title','Slide 4');
        $('.views_slideshow_singleframe_pager .pager-num-5 img').attr('title','Slide 5');
        $('.views_slideshow_singleframe_slide').attr('title','Hover over slide to pause slideshow, click slide to view article');
        
        $(".bef-toggle").tipTip();
        $(".views_slideshow_singleframe_pager img").tipTip();
      	$(".views_slideshow_singleframe_slide").tipTip();
      	$("#home-banner img").tipTip();
      	
      	$('a.close').click(function() {
        	$($(this).attr('href')).fadeOut();
        return false;
   		 });
      	
      	
      	$(".not-front #main-content img").lazyload({ 
    		effect : "fadeIn"
});
      	
      	$("#gmap-auto1map-gmap0").addClass("corner");
      	$("#gmap-auto1map-gmap0").addClass("iradius10");
      	
      	$(".node-type-bgn-story #main-content img").addClass("shadow");
      	$("#main-content .view .teaser img").addClass("shadow");
      	
      	$('#edit-search-block-form-1').bind('hastext', function () {
  			$('#edit-submit').removeClass('disabled').attr('disabled', false);
		});
	
		$('#edit-search-block-form-1').bind('notext', function () {
  			$('#edit-submit').addClass('disabled').attr('disabled', true);
		});
      	
  	
      	$('a#toTop').attr('title','Click for top of page');
      	$("a#toTop").tipTip();
      	$().UItoTop({ easingType: 'easeOutQuart' });
      	
      	$('#main-content a[href*=#]').click(function() {
    if (location.pathname.replace(/^\//,'') == this.pathname.replace(/^\//,'')
        && location.hostname == this.hostname) {
            var $target = $(this.hash);
            $target = $target.length && $target || $('[name=' + this.hash.slice(1) +']');
            if ($target.length) {
                var targetOffset = $target.offset().top;
                $('html,body').animate({scrollTop: targetOffset}, 1000);
                return false;
            }
        }
    });
      	
      });