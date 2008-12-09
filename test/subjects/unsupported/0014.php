<?php
	// Reduced with command line 'test/framework/reduce -r test/subjects/reduced/0010.php'
	$d = eval('function &g() { return $GLOBALS["a"]; }');
	$c = g();
	debug_zval_dump($c);
?>
