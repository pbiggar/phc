<?php
	// Reduced with command line 'test/framework/reduce -v -v -imir -u test/subjects/codegen/dont_shred_the_ref5.php'

	// This was a bug in phc, where we added temporary references which were
	// already in the source.
	function f($x)
	{
	}
	function g(&$x)
	{
	}
	f($c->c[$TLE2][$TLE3]);
	g($c->d[$TLE4][$TLE5]);
	var_dump($c);
?>
