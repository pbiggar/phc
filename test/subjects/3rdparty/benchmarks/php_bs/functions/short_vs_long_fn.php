<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Strings: Calling function with short vs long name,1 char function name, long 72 char function name

//================================================ INIT
function a()
{
}

function a_very_long_variable_name_to_be_tested_here_and_there_and_more_than_that()
{
}

//================================================ TEST CODE


function bench1() 
{
	a();
}


function bench2() 
{
	a_very_long_variable_name_to_be_tested_here_and_there_and_more_than_that();
}


//================================================ BENCHMARK!
include_once("../bench.inc.php");
?>