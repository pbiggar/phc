<?php
/*
 * (c) 2004 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");


// METADATA THAT IS READ BY ../bench.php:
//~~ Testing PHP5 exceptions (with 1 throw), No exceptions, With exceptions - throw 1 exception,1000

//================================================ INIT
if (PHP_VERSION < 5) echo "Requires PHP5 or later";
//================================================ TEST CODE

function bench1() 
{
	b1();
}

function b1()
{
}

function bench2() 
{
	try {
		b2();
	} catch(exception $e) {
		
	}
}

function b2()
{
	throw(new Exception("fail"));
}



//================================================ BENCHMARK!
include_once("../bench.inc.php");
?>