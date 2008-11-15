<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ 50 strings array - foreach (with keys) vs list($k&cedil;$v)=each,Foreach, List-Each

//================================================ INIT

for ($i=0; $i<50; $i++)
	$ARR[] = "ASDFGHJKL CVBNM ASDFGHJKL CVBNM ASDFGHJKL CVBNM ASDFGHJKL CVBNM 1234567890 ASDFGHJKL CVBNM";

//================================================ TEST CODE

function bench1() 
{
global $ARR;
	foreach($ARR as $k => $v) {
		$j[] = $v;
	}
	
	return $j;
}

function bench2() 
{
global $ARR;

	reset($ARR);
	while(list($k,$v) = each($ARR)) {
		$j[] = $v;
	}
	
	return $j;
}



//================================================ BENCHMARK!

include_once("../bench.inc.php");

?>