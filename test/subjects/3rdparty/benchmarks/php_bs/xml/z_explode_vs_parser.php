<?php
/*
 * (c) 2003 John Lim    jlim#natsoft.com
 */

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Parsing XML - explode vs XML parser (SAX), explode, xml parser (SAX), 100
//================================================ INIT


$XML = file_get_contents('rss.xml');

$XML2 = '<?xml version="1.0" ?>
<library>
	<book><title>Programming PHP</title><pages>507</pages></book>
	<book><title>Programming Perl</title><author>Larry Wall</author></book>
	<book><title>Programming C#</title></book>
	<book><title>PHP Performance Tuning</title></book>
</library>';

//================================================ TEST CODE


include_once('explode.inc.php');

/* SIMPLIFIED VERSION */
function char_handler($inParser,$inData)
{
global $ARR,$ISTITLE;

	if ($ISTITLE) {
		$ARR[] = $inData;
		$ISTITLE = false;
	}
}

function ele_handler($parser, $element, $attr)
{
global $ISTITLE;
	$ISTITLE = ($element == 'title');
}

function ele_end_handler($parser,$element)
{
}

function bench2() 
{
global $XML,$ARR;

	$ARR = array();
	$parser = xml_parser_create();
	xml_parser_set_option($parser,XML_OPTION_CASE_FOLDING,false);
	xml_set_element_handler($parser,'ele_handler','ele_end_handler');
	xml_set_character_data_handler($parser,'char_handler');
	xml_parse($parser,$XML);
	return $ARR;
}

//================================================ BENCHMARK!

include_once("../bench.inc.php");



?>