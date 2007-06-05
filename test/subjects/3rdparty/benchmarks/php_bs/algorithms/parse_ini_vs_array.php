<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Testing parse_ini_file vs assoc arrays (see http://www.sitepoint.com/blog-post-view.php?id=154126),parse_ini_file,assoc

//================================================ INIT



$f = fopen('pride.txt','rb');
$DATA = fread($f,1000000);
fclose($f);


//================================================ TEST CODE

function bench1() 
{
	$options = parse_ini_file('testini.ini');
	return $options;
}

function bench2() 
{
	include("testini.php");
	return $options;
}


//================================================ BENCHMARK!

include_once("../bench.inc.php");
?>