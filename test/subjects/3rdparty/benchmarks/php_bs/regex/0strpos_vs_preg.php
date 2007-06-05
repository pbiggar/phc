<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");
//================================================ INIT

//~~ Searching for substring with <b>strpos</b> vs<b> perl-style regex</b>, strpos, preg_match

$STR = "The elemental items magic roses happy systems happy systemsz";

//================================================ TEST CODE

function bench1() 
{
global $STR;

	strpos($STR,'z');
}


function bench2() 
{
global $STR;
	preg_match('/z/',$STR);
}


//================================================ BENCHMARK!
include_once("../bench.inc.php");
?>