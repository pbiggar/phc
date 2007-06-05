<?php

function bench2()
{
global $XML;

	$dom = new domDocument;
	$dom->loadxml($XML);
	
	$children = $dom->getElementsByTagName('title');
	
	foreach($children as $v) {
		$arr[] = $v->nodeValue;
	}
	return $arr;
}