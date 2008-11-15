<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Reading a binary file, fopen-fread-fclose, file_get_contents

//================================================ INIT





//================================================ TEST CODE

function bench1() 
{
	$fname = '03heart.jpg';
	$f = fopen($fname,'rb');
	$DATA = fread($f,filesize($fname));
	fclose($f);
	
	return $DATA;
}

function bench2() 
{
	$fname = '03heart.jpg';
	$DATA = file_get_contents($fname);
	return $DATA;
}

//================================================ BENCHMARK!

include_once("../bench.inc.php");

?>