<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Comparing checksums with crc32 and md5, crc32, md5

//================================================ INIT

define('CONSTANT',1);
$CONSTANT = 1;

//================================================ TEST CODE

function bench1() 
{
	crc32("The quality of mercy is not strained 1234567890");
}

function bench2() 
{
	md5("The quality of mercy is not strained 1234567890");
}

//================================================ BENCHMARK!

include_once("../bench.inc.php");

?>