<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ + vs += string operators, + strings, += strings,10000

//================================================ INIT

$s = '';

//================================================ TEST CODE

function bench1() 
{
global $s;

	$s = $s +'1234567890';
	$s = $s + 'abcdefghijklmnopqrstuvwxyz';
	$s = $s +'1234567890';
}

function bench2() 
{
global $s;

	$s += '1234567890';
	$s += 'abcdefghijklmnopqrstuvwxyz';
	$s += '1234567890';
}

//================================================ BENCHMARK!

include_once("../bench.inc.php");

?>