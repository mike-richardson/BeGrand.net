<?php
/*
 * Implements some blogger activity reporting
 */

/*
 * Page callback
 */

function usercount_bloggers(){
    drupal_add_css(drupal_get_path('module','usercount') . '/usercount.css', 'module', 'all', FALSE);
    $sql = "select u.name, count(*) as count from node n, users u
            where n.status = 1
                and n.uid = u.uid
                and u.uid != 0
                and n.type = 'blog'
            group by u.name
            order by count desc
            limit 10";
    $result = db_query($sql);
    while ($data = db_fetch_object($result)){
        $rows[] = array(
            array('data' => $data->name, 'class' => 'col1'),
            array('data' => $data->count, 'class' => 'col2'),
        );
    }
    $header = array(t('Name'), t('Count'));
    $output .= theme_table($header, $rows, array('class' => 'usercount'), t('Top 10 bloggers to date'));
    /* for each month the site has been active, print a Top Ten list */
    $sql="select distinct FROM_UNIXTIME(created,'%Y-%m') AS yearmonth
        from node
        order by yearmonth";
    $result = db_query($sql);
    while ($data = db_fetch_object($result)){
        $output .= _query_usercount_bloggers($data->yearmonth);
    }
    return $output;
}

function _query_usercount_bloggers($month = NULL){
    $rows = array();
    $sql = "select u.name, count(*) as count
            from node n, users u
            where n.status = 1 and n.uid = u.uid and u.uid != 0 and n.type = 'blog'
            and FROM_UNIXTIME(n.created,'%Y-%m') = '%s'
            group by u.name
            order by count desc
            limit 10";
    $result = db_query($sql,$month);
    while ($data = db_fetch_object($result)){
        $rows[] = array(
                  array('data' => $data->name, 'class' => 'col1'),
                  array('data' => $data->count, 'class' => 'col2'),
        );
    }
    if(!count($rows)) return t('No blogs posted in ') . $month . '<br />';
    $header = array(t('Name'), t('Count'));    
    $output .= theme_table($header, $rows, array('class' =>'usercount'), t('Top bloggers for ') . $month );
    return $output;
}

?>