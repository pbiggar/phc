<?php

	// Test our modelling of gettimeofday. Since it changes value between tests
	// (it being a time function) we should replace its digits with x.

	ob_start ();

//	var_dump (gettimeofday (X)); // undefined constant
	var_dump (gettimeofday (true));
	var_dump (gettimeofday (false));
	var_dump (gettimeofday ("str"));
	var_dump (gettimeofday (""));
	var_dump (gettimeofday (5));
	var_dump (gettimeofday (0));
	var_dump (gettimeofday (0.0));
	var_dump (gettimeofday (1.0));

	// Could go either way!
	var_dump (gettimeofday ($argv[1]));

	$output = ob_get_contents ();
	ob_end_clean ();
	$output = preg_replace ("/\d*/", "x", $output);

	print ($output);

?>
