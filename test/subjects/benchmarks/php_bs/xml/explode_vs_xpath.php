<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Parsing XML - explode vs XPath, explode, xpath
//================================================ INIT

$XML = file_get_contents('rss.xml');

//================================================ TEST CODE

include_once('explode.inc.php');

if (PHP_VERSION>=5) include_once('xpath_php5.inc.php');
else include_once('xpath_php4.inc.php');
//================================================ BENCHMARK!

include_once("../bench.inc.php");



?>