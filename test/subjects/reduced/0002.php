<?php
	// Reduced from test/subjects/codegen/functioncalls_evald_functions.php with phc arguments "--run=plugins/tools/debug_zval.la --dump=plugins/tools/debug_zval.la"
	$TLE1 = 'function fun_r(&$x) { $x = \'x\'; }';
	$TSe1 = eval($TLE1);
	$TSe42 = fun_r($r);
	$TSe306 = debug_zval_dump($r);
?>
