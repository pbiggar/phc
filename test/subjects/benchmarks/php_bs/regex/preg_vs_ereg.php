<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");
//================================================ INIT
//~~ Searching for substring with <b>perl-style regex</b> vs <b>ereg</b>, preg_match, ereg
$STR = "The elemental items magic roses happy systems happy systemsz";

//================================================ TEST CODE

function bench1() 
{
global $STR;
	preg_match('/z/',$STR);
}

function bench2() 
{
global $STR;

	ereg( 'z',$STR);
}

//================================================ BENCHMARK!
include_once("../bench.inc.php");
?>