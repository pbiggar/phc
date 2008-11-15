<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ short vs long variable names, short var name (1 char), long var name (72 chars),10000
//================================================ INIT



//================================================ TEST CODE

function bench1() 
{
	$a = 1;
}

function bench2() 
{
	/*echo strlen('a_very_long_variable_name_to_be_tested_here_and_there_and_more_than_that');
	die();*/
	$a_very_long_variable_name_to_be_tested_here_and_there_and_more_than_that = 1;
}

//================================================ BENCHMARK!

include_once("../bench.inc.php");

?>