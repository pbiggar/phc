<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Testing foreach versus  array_map with php function with 50 int element array, Foreach, Array_Map

//================================================ INIT	
for ($i=0; $i<50; $i++)
	$ARR[] = $i;//"ASDFGHJKL CVBNM ASDFGHJKL CVBNM ASDFGHJKL CVBNM ASDFGHJKL CVBNM 1234567890 ASDFGHJKL CVBNM";


//================================================ TEST CODE

function v($v)
{
	return $v;
}

function bench2() 
{
global $ARR;
	return array_map('v',$ARR);
}


function bench1() 
{
global $ARR;

	foreach($ARR as $v) $j[] = $v;
	return $j;
}


//================================================ BENCHMARK!
include_once("../bench.inc.php");
?>