<?php
	// Reduced with command line 'test/framework/reduce -v test/subjects/codegen/indexing_non_arrays.php'
	$x = true;
	$y = NULL;
	$x[] =& $y;
	var_dump($x);
?>
