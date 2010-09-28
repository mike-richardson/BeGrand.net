$(document).ready(function() {
		$.preloadCssImages();
		
	
        $('#main-content a').filter(function() {
         return this.hostname && this.hostname !== location.hostname;
        }).addClass('external-link');
        $('#main-content .buzzthis_button a').filter(function() {
         return this.hostname && this.hostname !== location.hostname;
        }).removeClass('external-link');
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
      	
      	$("#your-begrand a[href^='/users/']").addClass("your-account"); 
      	$("#your-begrand a[href^='/messages']").addClass("your-messages");
      	$("#your-begrand a[href^='/blog/']").addClass("your-blog");
      	$("#your-begrand a[href^='/relationships/']").addClass("your-friends");
      	$("#your-begrand a[href^='/galleries']").addClass("photo-galleries");
      	$("#your-begrand a[href^='/node/add/node-gallery-gallery']").addClass("add-photo-gallery");
      	$("#your-begrand a[href^='/node/add/node-gallery-image']").addClass("add-image");
      	$("#your-begrand a[href^='/node/add/event']").addClass("add-event");
      	$("#your-begrand a[href^='/events']").addClass("view-events-list");
      	$("#your-begrand a[href^='/event-calendar']").addClass("view-events-calendar");
      	$("a[href^='/logout']").addClass("log-out");
      	
      	
      	$("#group-tools a[href^='/node/add/poll']").addClass("group-poll"); 
      	$("#group-tools a[href^='/node/add/bgn-group-post']").addClass("group-post"); 
      	$("#group-tools a[href^='/node/add/cck-gallery']").addClass("group-gallery"); 
      	$("#group-tools a[href^='/og/invite']").addClass("group-invite");
      	$("#group-tools a[href^='/og/users']").addClass("group-members");
      	$("#group-tools a[href^='/og/manage']").addClass("manage-membership");
      	
      	
      	$("#site-menu a").tipTip();
      	$("#your-begrand a").tipTip();
      	$(".tipTip").tipTip();
      	$(".form-required").tipTip();
      	$(".csv-link").tipTip();
      	
      	$('a.close').click(function() {
        	$($(this).attr('href')).fadeOut();
        return false;
   		 });
      	
      	
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