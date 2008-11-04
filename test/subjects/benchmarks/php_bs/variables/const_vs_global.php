<?php

/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Reading CONSTANTS versus Global Variables, Constants, Globals

//================================================ INIT

define('CONSTANT',1);
$CONSTANT = 1;

//================================================ TEST CODE

function bench1() 
{
	return CONSTANT+CONSTANT+CONSTANT;
}

function bench2() 
{
global $CONSTANT;

	return $CONSTANT+$CONSTANT+$CONSTANT;
}

//================================================ BENCHMARK!

include_once("../bench.inc.php");

?>