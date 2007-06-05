<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Parsing XML - perl regex vs explode,  explode, preg_match_all

//================================================ INIT


$XML = file_get_contents('rss.xml');

//================================================ TEST CODE


include_once('explode.inc.php');

function bench2() 
{
global $XML;

	if (preg_match_all('/<title>([^<]*)/',$XML,$parr))	
		return $parr[1];
	else 
		return array();
}

//================================================ BENCHMARK!

include_once("../bench.inc.php");

?>