<?php
	
	// Reduced with command line 'test/framework/reduce test/subjects/codegen/return_by_reference_evald_functions.php'
	$TLE1 = 'function &g()
	{
		return $GLOBALS["a"];
	}';
	$TSe1 = eval($TLE1);
	$c = g();
?>
