<?php
/*
 * Implements some blogger activity reporting
 */

/*
 * Page callback
 */

function usercount_commenters(){
    drupal_add_css(drupal_get_path('module','usercount') . '/usercount.css', 'module', 'all', FALSE);
    // NOTE comment.status is basackwards in Drupal < 7; published == 0.
    $sql = "select u.name, count(*) as count from comments c, users u
            where c.status = 0
                and c.uid = u.uid
            group by u.name
            order by count desc
            limit 10";
    $result = db_query($sql);
    while ($data = db_fetch_object($result)){
        if ((!$data->name) && $data->count) $data->name = variable_get('anonymous','Anonymous');
        $rows[] = array(
            array('data' => $data->name, 'class' => 'col1'),
            array('data' => $data->count, 'class' => 'col2'),
        );
    }
    $header = array(t('Name'), t('Count'));
    $output .= theme_table($header, $rows, array('class' => 'usercount'), t('Top 10 commenters to date'));

    /* for each month the site has been active, print a Top Ten list */
    $sql="select distinct FROM_UNIXTIME(created,'%Y-%m') AS yearmonth
        from node
        order by yearmonth";
    $result = db_query($sql);
    while ($data = db_fetch_object($result)){
        $output .= _query_usercount_commenters($data->yearmonth);
    }
    return $output;
}

function _query_usercount_commenters($month = NULL){
    $rows = array();
    $sql = "select u.name, count(*) as count
            from comments c, users u
            where c.status = 0 and c.uid = u.uid 
            and FROM_UNIXTIME(c.timestamp,'%Y-%m') = '%s'
            group by u.name
            order by count desc
            limit 10";
    $result = db_query($sql,$month);
    while ($data = db_fetch_object($result)){
        if ((!$data->name) && $data->count) $data->name = variable_get('anonymous','Anonymous');
        $rows[] = array(
                  array('data' => $data->name, 'class' => 'col1'),
                  array('data' => $data->count, 'class' => 'col2'),
        );
    }
    if(!count($rows)) return t('No comments posted in ') . $month . '<br />';
    $header = array(t('Name'), t('Count'));    
    $output .= theme_table($header, $rows, array('class' =>'usercount'), t('Top commenters for ') . $month );
    return $output;
}

?>