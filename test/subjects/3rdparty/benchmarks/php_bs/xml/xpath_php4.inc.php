<?php

if (!function_exists('domxml_open_mem')) die("domxml not installed");

function bench2() 
{
global $XML;

	$dom = domxml_open_mem($XML);
	$ctx = $dom->xpath_new_context();
	$nodes = $ctx->xpath_eval("//title/text()");
	foreach($nodes->nodeset as $v) {
		//$v = $v->first_child();
		$arr[] = $v->node_value();
	}
	$dom->free();
	return $arr;
}


?>