<?php
	
	// Reduced with command line 'test/framework/reduce -d test/subjects/codegen/return_by_reference_sep.php'
	function &f()
	{
		return $GLOBALS[$TLE0];
	}
	$TDEs2 = "\n\$c =& f();\n";
	$TDEr2 = eval($TDEs2);
?>
