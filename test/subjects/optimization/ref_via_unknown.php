<?php

	$x = array (1,2,3);
	if ($argc)
	{
		$a = "x";
	}
	else
	{
		$a = "somevar";
	}

	$$a =& $y;

	$y[2] = 0;

	var_dump ($x[0]);
	var_dump ($x[1]);
	var_dump ($x[2]);
	var_dump ($y[0]);
	var_dump ($y[1]);
	var_dump ($y[2]);

?>
