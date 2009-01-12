<?php

	// The first of a set of test cases establishing how magic methods are used.
	// We also want to determine how the internals object handlers are used.

	class A
	{
		function __get ($x)
		{
			echo "get\n";
		}

		function __call ($a, $b)
		{
			var_dump ($a, $b);
			echo "call\n";
		}
	}


	$x = new A;
	$y = new A;
	$a = new A;

	$a = $x + $y;
	$a = $x - $y;
	$a = $x * $y;
	$a = $x / $y;
	$a = $x < $y;
	$a = $x >= $y;

	$x->f();
