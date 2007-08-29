<?php
	// Reduced from test/subjects/codegen/functioncalls_evald_functions.php with phc arguments ""
	eval('function fun_r(&$x) { $x = \'x\'; }');
	fun_r(&$t);
?>
