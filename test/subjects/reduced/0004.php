<?php
	/*
 * Like functioncalls_compiled, but using eval'd functions. 
 */
	
	eval('function fun($x) { $x = \'x\'; }');
	$h = $g;
	fun(&$h);
?>
