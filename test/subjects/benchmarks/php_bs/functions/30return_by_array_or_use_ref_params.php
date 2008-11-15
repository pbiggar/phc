<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Strings: Return multiple values using Array or use ref params, Return using Array, Use Ref Params,10000

//================================================ INIT

function &_b1()
{
	$a = 1;
	$b = 2;
	$c = 3;
	return array($a,$b,$c);
}


function _b2(&$a,&$b,&$c)
{
	$a = 1;
	$b = 2;
	$c = 3;
}


//================================================ TEST CODE

function bench1() 
{

	$a = _b1();
	
	//return array($a,$b);
}


function bench2() 
{
	$a = ''; $b = ''; $c='';

	_b2($a,$b,$c);
	
	//return array($a,$b);
}





//================================================ BENCHMARK!
include_once("../bench.inc.php");
?>