<?php
	/*
	 * Constructor invocation
	 */

	class C
	{
		function __construct()
		{
			echo "C constructor called\n";
		}
	}

	$c = new C();
	var_dump($c);

	class D
	{
		function __construct($x, $y)
		{
			echo "D constructor called ($x, $y)\n";
		}
	}

	$d = new D(1, 2);
	var_dump($d);
?>
