<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ + vs += integer operators, + integer, += integer
$s = '';
//================================================ INIT



//================================================ TEST CODE

function bench1() 
{
global $s;

	$s = $s + 1;
	$s = $s + 2;
	$s = $s + 3;
}

function bench2() 
{
global $s;

	$s += 1;
	$s += 2;
	$s += 3;
}

//================================================ BENCHMARK!

include_once("../bench.inc.php");

?>