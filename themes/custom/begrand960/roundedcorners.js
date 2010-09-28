$(document).ready(function() {

$("img.rounded").load( function () {
	var img = $(this);
	
	// build wrapper
	var wrapper = $('<div class="rounded_wrapper"></div>');
	wrapper.width(img.width());
	wrapper.height(img.height());
	
	// move CSS properties from img to wrapper
	wrapper.css('float', img.css('float'));
	img.css('float', 'none')
	
	wrapper.css('margin-right', img.css('margin-right'));
	img.css('margin-right', '0')

	wrapper.css('margin-left', img.css('margin-left'));
	img.css('margin-left', '0')

	wrapper.css('margin-bottom', img.css('margin-bottom'));
	img.css('margin-bottom', '0')

	wrapper.css('margin-top', img.css('margin-top'));
	img.css('margin-top', '0')

	wrapper.css('display', 'block');
	img.css('display', 'block')

	// wrap image
	img.wrap(wrapper);
	
	// add rounded corners
	img.after('<div class="tl"></div>');
	img.after('<div class="tr"></div>');
	img.after('<div class="bl"></div>');
	img.after('<div class="br"></div>');
});

	
});
