// $Id: ds.js,v 1.1.2.7 2010/01/29 14:22:40 swentel Exp $

/**
 * Move a field in the fields table from one region to another via select list.
 *
 * This behavior is dependent on the tableDrag behavior, since it uses the
 * objects initialized in that behavior to update the row.
 *
 * Based on nodeform cols.
 */
Drupal.behaviors.fieldDrag = function(context) {
  var table = $('table#fields');
  var tableDrag = Drupal.tableDrag.fields; // Get the fields tableDrag object.

  // Add a handler for when a row is swapped, update empty regions.
  tableDrag.row.prototype.onSwap = function(swappedRow) {
    checkEmptyRegions(table, this);
  };

  // A custom message for the fields page specifically.
  Drupal.theme.tableDragChangedWarning = function () {
    return '<div class="warning">' + Drupal.theme('tableDragChangedMarker') + ' ' + Drupal.t("The changes to these fields will not be saved until the <em>Save</em> button is clicked.") + '</div>';
  };

  // Add a handler so when a row is dropped, update fields dropped into new regions.
  tableDrag.onDrop = function() {
    dragObject = this;
      
    if ($(dragObject.rowObject.element).prev('tr').is('.region-message')) {
      var regionRow = $(dragObject.rowObject.element).prev('tr').get(0);
      var regionName = regionRow.className.replace(/([^ ]+[ ]+)*region-([^ ]+)-message([ ]+[^ ]+)*/, '$2');
      var regionField = $('select.field-region-select', dragObject.rowObject.element);
      var weightField = $('select.field-weight', dragObject.rowObject.element);
      var oldRegionName = weightField[0].className.replace(/([^ ]+[ ]+)*field-weight-([^ ]+)([ ]+[^ ]+)*/, '$2');

      if (!regionField.is('.field-region-'+ regionName)) {
        regionField.removeClass('field-region-' + oldRegionName).addClass('field-region-' + regionName);
        weightField.removeClass('field-weight-' + oldRegionName).addClass('field-weight-' + regionName);
        regionField.val(regionName);
      }
      // Manage classes to make it look disabled
      if(regionName == 'disabled') {
        $(dragObject.rowObject.element).addClass('region-css-disabled');
      }
      else {
        $(dragObject.rowObject.element).removeClass('region-css-disabled');
      }
    }
  };

  // Add the behavior to each region select list.
  $('select.field-region-select:not(.fieldregionselect-processed)', context).each(function() {
    $(this).change(function(event) {
      // Make our new row and select field.
      var row = $(this).parents('tr:first');
      var select = $(this);
      tableDrag.rowObject = new tableDrag.row(row);
      
      // Manage classes to make it look disabled
      if(select[0].value == 'disabled') {
        $(row).addClass('region-css-disabled');
      }
      else {
        $(row).removeClass('region-css-disabled');
      }

      // Find the correct region and insert the row as the first in the region.
      $('tr.region-message', table).each(function() {
        if ($(this).is('.region-' + select[0].value + '-message')) {
          // Add the new row and remove the old one.
          $(this).after(row);
          // Manually update weights and restripe.
          tableDrag.updateFields(row.get(0));
          tableDrag.rowObject.changed = true;
          if (tableDrag.oldRowElement) {
            $(tableDrag.oldRowElement).removeClass('drag-previous');
          }
          tableDrag.oldRowElement = row.get(0);
          tableDrag.restripeTable();
          tableDrag.rowObject.markChanged();
          tableDrag.oldRowElement = row;
          $(row).addClass('drag-previous');
        }
      });

      // Modify empty regions with added or removed fields.
      checkEmptyRegions(table, row);
      // Remove focus from selectbox.
      select.get(0).blur();
    });
    $(this).addClass('fieldregionselect-processed');
  });

  var checkEmptyRegions = function(table, rowObject) {
    $('tr.region-message', table).each(function() {
      // If the dragged row is in this region, but above the message row, swap it down one space.
      if ($(this).prev('tr').get(0) == rowObject.element) {
        // Prevent a recursion problem when using the keyboard to move rows up.
        if ((rowObject.method != 'keyboard' || rowObject.direction == 'down')) {
          rowObject.swap('after', this);
        }
      }
      // This region has become empty
      if ($(this).next('tr').is(':not(.draggable)') || $(this).next('tr').size() == 0) {
        $(this).removeClass('region-populated').addClass('region-empty');
      }
      // This region has become populated.
      else if ($(this).is('.region-empty')) {
        $(this).removeClass('region-empty').addClass('region-populated');
      }
    });
  };
};

/**
 * Drupal ds object.
 */
Drupal.DisplaySuite = Drupal.DisplaySuite || {};

/**
 * Show / hide fields or plugins content.
 */
Drupal.DisplaySuite.toggleDisplayTab = function(element) {
  $('#ds-tabs .tab').each(function() {
    var tab_id = $(this).attr('id');
    var content_id = tab_id.replace('-tab', '-content');
	if (tab_id == element) {
	  // Tabs.
      $(this).addClass('selected');
      $(this).removeClass('not-selected');
      // Content.
      $('#'+ content_id).show();
    }
    else {
      // Tabs.
      $(this).addClass('not-selected');
      $(this).removeClass('selected');
      // Content.
      $('#'+ content_id).hide();
    }
  });	
}
 
/**
 * Change the label of a field instance in a build mode.
 */
Drupal.DisplaySuite.changeLabel = function(element, title) {
 
  var changed = prompt(Drupal.t("Edit label"), title);
   
  if (changed == '') {
    alert(Drupal.t('Field can not be empty'));
    return false;
  }
   
  var labelcell = $(element).parents(".ds-label");
  labelcell.find(".label-field").text(changed);
  labelcell.find("input").val(changed);
}
