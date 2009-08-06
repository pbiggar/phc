<?php

	// Reported by Stig Vestøl (Vestøl Data)
	// segfaults when compiling.

	class MyClass
	{

		function __construct ($var)
		{
			print "Constructor\n";
		}

	}

	class MyClass2
	{
		function __construct ($var = 5) // with required parameter
		{
			print "Constructor\n";
		}

	}

	$x = new MyClass ();  // Segmentation fault
	$x = new MyClass (1);  // works

	$x = new MyClass2 ();  // Segmentation fault
	$x = new MyClass2 (1);  // works

?>
