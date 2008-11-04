<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ 50 ints array - foreach (no keys) vs list(&cedil;$v)=each,Foreach, List-Each

//================================================ INIT
for ($i=0; $i<50; $i++)
	$ARR[] = $i;

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

	reset($ARR);
	while(list(,$v) = each($ARR)) {
		$j[] = $v;
	}
	
	return $j;
}



//================================================ BENCHMARK!

include_once("../bench.inc.php");

?>