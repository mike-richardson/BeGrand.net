// Show/Hide Taxonomy VTN Descriptions
function taxonomy_vtn_show_hide_desc(what){
  var table = document.getElementById('taxonomy_vtn_'+what);
  if(table){
    var i,divy=table.getElementsByTagName('DIV');
    for(i=0;i<divy.length;i++){
      if(divy[i].className=='taxonomy-vtn-description'){
        if(divy[i].style.display==''){
          divy[i].style.display='none';
        }
        else{
          divy[i].style.display='';
        }
      }
    }
  }
}
