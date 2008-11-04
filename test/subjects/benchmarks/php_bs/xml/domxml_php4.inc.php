<?php
if (!function_exists('domxml_open_mem')) die("domxml not installed");

function bench2() 
{
global $XML;

	$dom = domxml_open_mem($XML);
	$children = $dom->get_elements_by_tagname('title');
	
	foreach($children as $v) {
		$arr[] = $v->get_content();
	}
	$dom->free();
	return $arr;
}

?>