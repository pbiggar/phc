<?php
	// Reduced with command line 'test/framework/reduce -v test/subjects/codegen/return_by_reference_sep.php'
	
	function &f()
	{
		return $GLOBALS["b"];
	}
	
	$c =& f();
	$c = 6;
	var_export($b);
?>
