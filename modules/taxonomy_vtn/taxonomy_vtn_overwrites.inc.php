<?php
// $Id: taxonomy_vtn_overwrites.inc.php,v 1.1.2.3 2009/03/05 07:54:47 alexiswilke Exp $

/**
 * @file
 * own version of taxonomy_select_nodes to use no limit query - @param $count
 *
 */

/**
 * Finds all nodes that match selected taxonomy conditions.
 *
 * @param $tids
 *   An array of term IDs to match.
 * @param $operator
 *   How to interpret multiple IDs in the array. Can be "or" or "and".
 * @param $depth
 *   How many levels deep to traverse the taxonomy tree. Can be a nonnegative
 *   integer or "all".
 * @param $pager
 *   Whether the nodes are to be used with a pager (the case on most Drupal
 *   pages) or not (in an XML feed, for example).
 * @param $order
 *   The order clause for the query that retrieves the nodes.
 * @param $count
 *   If $pager is TRUE, the number of nodes per page, or -1 to use the
 *   backward-compatible 'default_nodes_main' variable setting.  If $pager
 *   is FALSE, the total number of nodes to select; or -1 to use the
 *   backward-compatible 'feed_default_items' variable setting; or 0 to
 *   select all nodes.
 * @return
 *   A resource identifier pointing to the query results.
 */
function _taxonomy_vtn_select_nodes($tids = array(), $operator = 'or', $depth = 0, $pager = TRUE, $order = 'n.sticky DESC, n.created DESC', $count = -1) {
  if (count($tids) > 0) {
    // For each term ID, generate an array of descendant term IDs to the right depth.
    $descendant_tids = array();
    if ($depth === 'all') {
      $depth = NULL;
    }
    foreach ($tids as $index => $tid) {
      $term = taxonomy_get_term($tid);
      $tree = taxonomy_get_tree($term->vid, $tid, -1, $depth);
      $descendant_tids[] = array_merge(array($tid), array_map('_taxonomy_get_tid_from_term', $tree));
    }

    if ($operator == 'or') {
      $args = call_user_func_array('array_merge', $descendant_tids);
      $placeholders = db_placeholders($args, 'int');
      $sql = 'SELECT DISTINCT(n.nid), n.sticky, n.title, n.created FROM {node} n INNER JOIN {term_node} tn ON n.vid = tn.vid WHERE tn.tid IN ('. $placeholders .') AND n.status = 1 ORDER BY '. $order;
      $sql_count = 'SELECT COUNT(DISTINCT(n.nid)) FROM {node} n INNER JOIN {term_node} tn ON n.vid = tn.vid WHERE tn.tid IN ('. $placeholders .') AND n.status = 1';
    }
    else {
      $joins = '';
      $wheres = '';
      $args = array();
      foreach ($descendant_tids as $index => $tids) {
        $joins .= ' INNER JOIN {term_node} tn'. $index .' ON n.vid = tn'. $index .'.vid';
        $wheres .= ' AND tn'. $index .'.tid IN ('. db_placeholders($tids, 'int') .')';
        $args = array_merge($args, $tids);
      }
      $sql = 'SELECT DISTINCT(n.nid), n.sticky, n.title, n.created FROM {node} n '. $joins .' WHERE n.status = 1 '. $wheres .' ORDER BY '. $order;
      $sql_count = 'SELECT COUNT(DISTINCT(n.nid)) FROM {node} n '. $joins .' WHERE n.status = 1 '. $wheres;
    }
    $sql = db_rewrite_sql($sql);
    $sql_count = db_rewrite_sql($sql_count);
    if ($pager) {
      if ($count == -1) {
        $count = variable_get('default_nodes_main', 10);
      }
      $result = pager_query($sql, $count, 0, $sql_count, $args);
    }
    else {
      if ($count == -1) {
        $count = variable_get('feed_default_items', 10);
      }

      if ($count == 0) {
        $result = db_query($sql, $args);
      }
      else {
        $result = db_query_range($sql, $args, 0, $count);
      }
    }
  }
  return $result;
}



/**
 * Finds the number of nodes that match selected taxonomy conditions.
 *
 * @param $tids
 *   An array of term IDs to match.
 * @param $depth
 *   How many levels deep to traverse the taxonomy tree. Can be a nonnegative
 *   integer or "all".
 * @return
 *   The number of nodes that match the selection
 */
function _taxonomy_vtn_count_nodes($tids, $depth) {
  if (count($tids) > 0) {
    // For each term ID, generate an array of descendant term IDs to the right depth.
    $descendant_tids = array();
    if ($depth === 'all') {
      $depth = NULL;
    }
    foreach ($tids as $index => $tid) {
      $term = taxonomy_get_term($tid);
      $tree = taxonomy_get_tree($term->vid, $tid, -1, $depth);
      $descendant_tids[] = array_merge(array($tid), array_map('_taxonomy_get_tid_from_term', $tree));
    }

    $args = call_user_func_array('array_merge', $descendant_tids);
    $placeholders = db_placeholders($args, 'int');
    $sql_count = 'SELECT COUNT(DISTINCT(n.nid)) FROM {node} n INNER JOIN {term_node} tn ON n.vid = tn.vid WHERE tn.tid IN ('. $placeholders .') AND n.status = 1';
    $sql_count = db_rewrite_sql($sql_count);
    $result = db_query($sql_count, $args);
    if ($result) {
      return (int)db_result($result);
    }
  }

  return 0;
}
