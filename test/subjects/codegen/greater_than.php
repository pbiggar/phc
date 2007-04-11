<?php

	// We replace > with <= and switch the paramters, after a pattern in the
	// zend_parser. However, we need to get the order right.

	$x = 0;

	function f () { echo "F called\n"; global $x; return $x++;}
	function g () { echo "G called\n"; global $x; return $x++;}

	if (f () > g ()) print "F is greater\n";
	else print "G is greater\n";


	if (g () >= f ()) print "G is greater or equal\n";
	else print "F is greater\n";

	var_dump ($x);

?>
