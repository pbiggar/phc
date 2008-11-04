<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Encoding binary data with base64 and utf8_encode,base64,utf8_encode

//================================================ INIT



$f = fopen('03heart.jpg','rb');
$DATA = fread($f,1000000);
fclose($f);


//================================================ TEST CODE

function bench1() 
{
global $DATA;

	$d = base64_encode($DATA);
	return $d;
}

function bench2() 
{
global $DATA;

	$d = utf8_encode($DATA);
	return $d;
}


//================================================ BENCHMARK!

include_once("../bench.inc.php");
?>