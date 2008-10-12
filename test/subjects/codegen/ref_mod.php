<?php
	/*
		Is an equivalent to the following C program, with unrestricted pointers, possible in PHP:
	 	void f (int* x, int* y)
		{
			int* tmp = x;
			x = y;
			y = tmp;
			*y = *x;
		}
	*/

	function f (&$x, &$y)
	{
		$tmp =& $y; 
		$y =& $x;
		$x =& $tmp;

		$y = $x;
	}

	$x = 5;
	$y = 6;
	f ($x, $y);
	var_dump ($x, $y);

	unset ($x);
	unset ($y);
	f ($x[0], $y[0]);
	var_dump ($x, $y);
?>
