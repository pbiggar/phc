<?php

function bench1() 
{
global $XML;
	
	$arr = array();
	$x = explode("<title>",$XML);
	foreach($x as $v) {
		$pos = strpos($v,'</title>');
		$v = substr($v,0,$pos);
		if ($v) $arr[] = $v;
	}
	return $arr;
}

?>