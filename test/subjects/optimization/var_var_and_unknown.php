<?php

	// We shouldnt know the value of $y at the end.
	if ($argc)
	{
		$x = "some_var_name";
	}
	else
	{
		$x = "some_other_var_name";
	}

	$y = 7;

	$$x = 5;

	print ("$y \n");
	print ("{$$x} \n");


	// Now read via reference, this should lead to a lit of POSSIBLY edges.
	$z =& $$x;
	var_dump ($z);


	// This should be the same for arrays
	$x = array (0 => 10, 1 => 11);
	$aa =& $x[$argc];
	$aa = 7;
	print $x[1]."\n";
?>
