<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");


// METADATA THAT IS READ BY ../bench.php:
//~~ 50 ints array - Testing for loop with more complicated -- and ++, for (--), for(++)

//================================================ INIT
for ($i=0; $i<50; $i++)
$ARR[] = "ASDFGHJKL CVBNM ASDFGHJKL CVBNM ASDFGHJKL CVBNM ASDFGHJKL CVBNM 1234567890 ASDFGHJKL CVBNM";
//================================================ TEST CODE

function bench1() 
{
global $ARR;

	for ($i=sizeof($ARR)-1; $i>=0; --$i) $j[] = $ARR[$i];
	
	return $j;
}


function bench2() 
{
global $ARR;

	for ($i=0, $max=sizeof($ARR); $i < $max; $i++) $j[] = $ARR[$i];
	
	return $j;
}


//================================================ BENCHMARK!
include_once("../bench.inc.php");
?>