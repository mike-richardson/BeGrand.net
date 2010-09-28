<?php
/*
 * Reports on users by role
 */
function usercount_by_role(){
    $sql = "select count(*) as count from users u where u.uid not in (select distinct uid from users_roles) and u.uid != 0";
    $result = db_query($sql);
    $data = db_fetch_object($result);
    $rows = array();
    $rows[] = array(t('Users with no special role'),$data->count);

    $sql = "select r.name as role, count(*) as count from role r, users_roles u where u.rid = r.rid group by r.rid;";
    $result = db_query($sql);
    while ($data = db_fetch_object($result)){
        $rows[] = array(
               array('data' => $data->role, 'class' => 'col1'),
               array('data' => $data->count, 'class' => 'col2')
               );
    }
    $header = array();
    return theme_table($header, $rows, array('class' => 'usercount'), t('Users by role'));
}

?>