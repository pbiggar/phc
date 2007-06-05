<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Testing foreach with crc32 versus  array_map with php function with 50 element array, Foreach, Array_Map

//================================================ INIT	
for ($i=0; $i<50; $i++)
	$ARR[] = "ASDFGHJKL CVBNM ASDFGHJKL CVBNM ASDFGHJKL CVBNM ASDFGHJKL CVBNM 1234567890 ASDFGHJKL CVBNM";


//================================================ TEST CODE


function bench2() 
{
global $ARR;
	return array_map('crc32',$ARR);
}


function bench1() 
{
global $ARR;

	foreach($ARR as $v) $j[] = crc32($v);
	return $j;
}


//================================================ BENCHMARK!
include_once("../bench.inc.php");
?>