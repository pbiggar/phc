<?php

	// Commented statements arent allowed by the parser

	// compare print and echo
	function f () { return "7\n"; }
	$x = "5\n";

//	print;
//	print ();
//	echo;

	print $x;
	echo $x;

	print f ();
	echo f ();

//	$y = echo 5;
	$y = print 5;

	echo f(), $x, f();
//	print f(), $x, f();

	print print print $x;
//	echo echo echo $x;
	echo print print $x;
	
	echo f(), print print $x, $x;

//	echo &f();
//	print &f();

//	echo &$x;
//	print &$x;

//	$y = &echo f ();
//	$y = &print f ();

	// we convert print to printf, which returns the length of the string.
	// Print, however, always returns 1.
	print print "a string of some length";

?>
