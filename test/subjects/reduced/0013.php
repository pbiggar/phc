<?php
	// Reduced with command line 'test/framework/reduce test/subjects/codegen/return_by_reference_evald_functions.php'
	/*
 * See return_by_reference_compiled.php; eval'd function definitions.
 */
	
	$a = 'function f()
	{
		return $GLOBALS["a"];	
	}';
	eval($a);
	$d =& f();
?>
