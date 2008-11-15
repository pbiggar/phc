<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ 50 strings array -  foreach (no keys) versus reset and next, Foreach, Reset-Next

//================================================ INIT

for ($i=0; $i<50; $i++)
	$ARR[] = "ASDFGHJKL CVBNM ASDFGHJKL CVBNM ASDFGHJKL CVBNM ASDFGHJKL CVBNM 1234567890 ASDFGHJKL CVBNM";

//================================================ TEST CODE

function bench1() 
{
global $ARR;
	foreach($ARR as $v) {
		$j[] = $v;
	}
	return $j;
}


function bench2() 
{
global $ARR;

	$v = reset($ARR);
	do{
		$j[] = $v;
	} while ($v = next($ARR));
	
	return $j;
}



//================================================ BENCHMARK!

include_once("../bench.inc.php");

?>