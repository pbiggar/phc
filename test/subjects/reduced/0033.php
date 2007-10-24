<?php
	// Reduced with command line 'test/framework/reduce -v test/subjects/codegen/indexing_non_arrays.php'
	$x = "";
	$y = NULL;
	$x[NULL] =& $y;
?>
