

$(document).ready(function() {

	$.fn.cleardefault = function() {
	return this.focus(function() {
		if( this.value == this.defaultValue ) {
			this.value = "";
		}
	}).blur(function() {
		if( !this.value.length ) {
			this.value = this.defaultValue;
		}
	});
};
$(".shout-message").cleardefault();
$("#edit-distance-postal-code").cleardefault();
$("#edit-distance-search-distance").cleardefault();
});

