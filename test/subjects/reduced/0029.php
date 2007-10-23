<?php
	// Reduced with command line 'test/framework/reduce -v test/subjects/codegen/unset_with_null.php'
	$x = array ();
	unset($x[NULL]);
	unset($x["z"]);
	unset($x[5]);
?>
