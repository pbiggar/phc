<?php
	
	// Reduced with command line 'test/framework/reduce test/subjects/codegen/return_by_reference_evald_functions.php'
	$b = 'function &g()
	{
		return $GLOBALS["a"];
	}';
	eval($b);
	$c = g();
?>
