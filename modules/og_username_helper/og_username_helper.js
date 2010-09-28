// $Id: og_username_helper.js,v 1.3 2010/01/28 07:41:22 marvil07 Exp $
/* Add usernames to the one of the fields supported */

Drupal.og_username_helperAutoAttach = function() {
  function og_username_helperAction() {
    $("#edit-og-username-helper-text").val($.trim($("#edit-og-username-helper-text").val()));
    if ($("#edit-og-username-helper-text").val() != undefined && $("#edit-og-username-helper-text").val() != '') {
      var coma=',';
      if ( $("#edit-mails").val() != undefined) {
        if ( $("#edit-mails").val() == '')
          coma='';
        if ( $.inArray($("#edit-og-username-helper-text").val(), $("#edit-mails").val().split(",")) < 0)
          $("#edit-mails").val($("#edit-mails").val()+coma+$("#edit-og-username-helper-text").val());
      }
      else if ( $("#edit-og-names").val() != undefined ) {
        if ($("#edit-og-names").val()=='')
          coma='';
        if ( $.inArray($("#edit-og-username-helper-text").val(), $("#edit-og-names").val().split(",")) < 0)
          $("#edit-og-names").val($("#edit-og-names").val()+coma+$("#edit-og-username-helper-text").val());
      }
    }
    $("#edit-og-username-helper-text").val('');
    return false;
  }
  /* react on keys */
  $("#edit-og-username-helper-text").keyup(function(e) {
    /* take action on enter or tab */
    if (e.which != 13 && e.which != 9) {
      return true;
    }
    return og_username_helperAction();
  });
  /* react on clicks */
  $("#edit-og-username-helper-text-wrapper").click(function() {
    if ($("#autocomplete ul li div").length > 0) {
      return og_username_helperAction();
    }
  });
}

if (Drupal.jsEnabled) {
  $(document).ready(Drupal.og_username_helperAutoAttach);
}
