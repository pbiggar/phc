<?php
	// Reduced with command line 'test/framework/reduce -v test/subjects/codegen/return_by_reference_sep.php'
	
	function &f()
	{
	}
	
	$c =& f();
?>
