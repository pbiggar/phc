<?php

/*
   (c) 2003-2004 John Lim
*/
error_reporting(E_ALL);
set_time_limit(300);

function getmicrotime()
{
	$t = microtime();
	$t = explode(' ',$t);
	return (float)$t[1]+ (float)$t[0];
}

function _bench1()
{
}

function dobench1($ITER)
{
	bench1();bench1();bench1();
	$t1 = getmicrotime();
	for ($i=$ITER; --$i >= 0;) {
		bench1();
	}
	return getmicrotime() - $t1;
}

function dobench2($ITER)
{
	bench2();bench2();bench2();
	$t1 = getmicrotime();
	for ($i=$ITER; --$i >= 0;) {
		bench2();
	}
	return getmicrotime() - $t1;
}

function DoBenchmark()
{
	if (PHP_VERSION < 4.1) {
	global $HTTP_GET_VARS;
		$_GET = $HTTP_GET_VARS;
	}
	$ITER = (isset($_GET['iter'])) ? (integer) $_GET['iter'] : 1000;
	$SWAP = function_exists('bench2') && !empty($_GET['swap']);
	
	if ($ITER > 10000) die("DOS attack?");
	flush();
	
	$t1 = getmicrotime();
	for ($i=$ITER; --$i >= 0;) {
		_bench1();
	}
	$overhead = getmicrotime() - $t1;
	
	//printf("oh=%8.6f ",$overhead);
	
	if ($SWAP) $time2 = dobench2($ITER) - $overhead;
	else $time1 = dobench1($ITER) - $overhead;
	
	if (function_exists('bench2')) {
		if ($SWAP)  $time1 = dobench1($ITER) - $overhead;
		else $time2 = dobench2($ITER) - $overhead;
		
		printf("##%8.4f##%8.4f##",abs($time1)*(1000.0/$ITER),abs($time2)*(1000.0/$ITER));
	} else {
		printf("##%8.4f##",$time1);
	}
}

/*******************************************/
if (empty($NOTEST)) {
	DoBenchmark();
}

if (PHP_VERSION < 4.1) $_GET = $HTTP_GET_VARS;

if (!isset($_GET['iter']) || $_GET['iter'] == 1) {
	echo "<pre>";
	echo "<h3>Bench1</h3>";
		$_RET1 = bench1();
		print_r($_RET1);
		if (is_string($_RET1)) echo "<br>strlen=".strlen($_RET1)."<br>";
	echo "<h3>Bench2</h3>";
		$_RET1 = bench2();
		print_r($_RET1);
		if (is_string($_RET1)) echo "<br>strlen=".strlen($_RET1)."<br>";
	
	if (function_exists('memory_get_usage')) echo "<p>memory usage=".memory_get_usage()."</p>";
}
?>