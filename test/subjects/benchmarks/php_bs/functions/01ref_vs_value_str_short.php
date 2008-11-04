<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Strings: Call by ref vs call by value for 1 char string, Call by Ref, Call by Value,1000

//================================================ INIT

$STR = 'Z';

//================================================ TEST CODE

function _b1(&$a)
{
	$z = $a;
}

function _b2($a)
{

	$z = $a;
}

function bench1() 
{
global $STR;

	_b1($STR);
}


function bench2() 
{

global $STR;

	_b2($STR);
}


//================================================ BENCHMARK!
include_once("../bench.inc.php");
?>