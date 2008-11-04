<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Arrays: Call by ref vs call by value, Call by Ref, Call by Value

//================================================ INIT
for ($i=0; $i<50; $i++)
	$ARR[] = array($i,'TEST');

//================================================ TEST CODE

function _b1(&$a)
{
	reset($a);
}

function _b2($a)
{
	reset($a);
}

function bench1() 
{
global $ARR;
	_b1($ARR);
}


function bench2() 
{
global $ARR;

	_b2($ARR);
}


//================================================ BENCHMARK!
include_once("../bench.inc.php");
?>