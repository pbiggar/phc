<?php
	eval('function fun($x) { $x = \'x\'; }');
	$h = $g;
	fun(&$h);
	debug_zval_dump($h);
?>
