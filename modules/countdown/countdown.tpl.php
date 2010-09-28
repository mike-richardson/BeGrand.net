<?php
// $Id: countdown.tpl.php,v 1.1.2.1 2008/05/12 15:29:47 deekayen Exp $

/**
 * @file countdown.tpl.php
 *
 * Theme implementation to display a list of related content.
 *
 * Available variables:
 * - $items: the list.
 */
$time = time();
$difference = variable_get('countdown_timestamp', $time) - $time;
if ($difference < 0) {
  $passed = 1;
  $difference = abs($difference);
}
else {
  $passed = 0;
}



$accuracy  = variable_get('countdown_accuracy', 'd');
$days_left = floor($difference/60/60/24);
$hrs_left  = floor(($difference - $days_left*60*60*24)/60/60);
$min_left  = floor(($difference - $days_left*60*60*24 - $hrs_left*60*60)/60);
$secs_left = floor(($difference - $days_left*60*60*24 - $hrs_left*60*60 - $min_left*60));

if ($days_left>1) {
	$days_left.=" days";
} else {
	$days_left.=" day";
}

if ($hrs_left>1) {
	$hrs_left.=" hours";
} else {
	$hrs_left.=" hour";
}

if ($min_left>1) {
	$min_left.=" minutes";
} else {
	if ($min_left ==0) {
		$min_left="";
	} else {
		$min_left.=" minute";
	}
}

echo "<div class='blue-box'>";
echo "<p>Half term begins in $days_left, $hrs_left and $min_left.</p>";
?>
	<p><a href='/article/things-do/find-half-term-fun-local-venues'>Venues for local half term fun</a></p>
	<p><a href="/article/things-do/find-perfect-day-out">Days out under cover</a></p>
	<p><a href="/article/money/free-local-authority-fun">Free local authority fun</a></p>
	<p><a href="/article/money/exciting-money-saving-ways-help-older-children-get-out-there-and-enjoy">Help older children get out</a></p>
	<p><a href="/article/money/have-free-or-nearly-free-day-out-%E2%80%93-home">Free (or nearly free) day out at home</a></p>
<?php



//print t('%i days', array('%i' => $days_left));
//if ($accuracy == 'h' || $accuracy == 'm' || $accuracy == 's') {
//  print  t(', %i hours', array('%i' => $hrs_left));
//}
//if ($accuracy == 'm' || $accuracy == 's') {
// print  t(', %i minutes', array('%i' => $min_left));
//}
//if ($accuracy == 's') {
//  print t(', %i seconds', array('%i' => $secs_left));
//}
//print t(($passed) ? ' since %s.' : ' until %s.', array('%s' => variable_get('countdown_event_name', '')));

if ($accuracy != 'd') {
  $path = drupal_get_path('module', 'countdown');
  drupal_add_js($path .'/countdown.js');

  print <<<___EOS___
<script type="text/javascript"><!--
  init_countdown('$accuracy');
// --></script>
___EOS___;
echo "</div>";
}
