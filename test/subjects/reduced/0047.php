<?php
	// Reduced with command line 'test/framework/reduce -igenerate-c -U -v -v test/subjects/codegen/print.php'
	$z = 2;
	function f()
	{
		global $z;
		return $z;
	}
	$TLE4 = f();
	$TLE23 = '%s';
	printf($TLE23, $TLE4);
?>
