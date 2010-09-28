// $Id: tag_editor.js,v 1.3 2008/12/10 22:24:41 Gurpartap Exp $

// Global varilables.
var tag_field = '';
var autocompleteTrigger = false;

/**
 * Strip out commans, double-quotes, and leading & trailing spaces.
 */
function tag_editor_replace(val) {
  return val.replace(/,/g, '').replace(/"/g, '').replace(/^\s*/, '').replace(/\s*$/, '');
}

/**
 * Appends a "token" as formatted HTML.
 */
function tag_editor_insert_tag(val) {
  if (tag_editor_replace(val) !== '') {
    $('#tokens').append('<div class="token"><span class="tag">' + val + '</span><a class="tag_editor_close" href="javascript:;" title="' + Drupal.t("Remove tag") + '">x</a></div>').val('');
  }
}

/**
 * Reflect the tags data in actual input field.
 */
function tag_editor_update_form() {
  var tags = [];
  $('.tag').each(function() {
    tags.push(tag_editor_replace(this.innerHTML));
  });
  $('#' + tag_field).val('').val('"' + tags.join('", "') + '"');
  $('.tag_editor_close').bind('click', function() {
    $(this).parent().hide(150, function() {
      $(this).remove();
    });
    tag_editor_update_form();
  });
}

/**
 * Bind actions to input fields and perform deletion and insertion operations.
 */
function tag_editor_detect() {
  $('#tag_editor_input').bind('keydown autocompleteTrigger', function(e) {
    $('#autocomplete').css({
      marginLeft: (this.offsetLeft-30) +'px'
    });
    if (typeof e == 'undefined') {
      var e = window.event;
    }
    var code = e.charCode ? e.charCode : e.keyCode;
    if (code == 8 && !this.value) {
      // Delete key.
      $('#tag_editor .token:last').hide(150, function() {
        $(this).remove();
      });
      tag_editor_update_form();
    }
    else if (code == 13 || code == 188 || autocompleteTrigger) {
      // Enter and comma key.
      this.blur();
      tag_editor_insert_tag(this.value);
      this.value = '';
      tag_editor_update_form();
      this.focus();
      autocompleteTrigger = false;
      return false;
    }
  }).bind('keyup', function(e) {
    $('#autocomplete').css({
      marginLeft: (this.offsetLeft - 30) + 'px'
    }).find('li').bind('mousedown', function() {
      // @todo This doesn't work for "first time clicked" items in autocomplete popup.
      autocompleteTrigger = true;
      $('#tag_editor_input').trigger('autocompleteTrigger');
    });
  });
}

/**
 * Implementation of Drupal.behaviors.hook(). ;)
 */
Drupal.behaviors.tag_editor = function() {
  tag_field = Drupal.settings.tag_editor.tag_field || null;
  if (!tag_field) {
    return true;
  }
  $('#' + tag_field).wrap('<div id="tag_editor"></div>')
    .clone().attr({'name': 'tag_editor_input_field', 'id': 'tag_editor_input'}).css({'width': '150px', 'background' : 'none'})
    .appendTo('#tag_editor').end().hide();
  $('#' + tag_field + '-autocomplete').clone().attr({'id': 'tag_editor_input_autocomplete'}).appendTo('#tag_editor');
  if (typeof Drupal.behaviors.autocomplete == 'function') {
    Drupal.behaviors.autocomplete('#tag_editor');
  }
  $('#tag_editor').prepend('<span id="tokens"></span>').bind('click', function() {
    $('#tag_editor_input').focus();
  });
  var tags = $('#tag_editor_input').val();
  tags = typeof tags != 'undefined' ? tags.split(",") : [];
  $.each(tags, function(i, val) {
    tag_editor_insert_tag(val);
  });
  $('#tag_editor_input').val('');
  tag_editor_detect();
  tag_editor_update_form();
};
