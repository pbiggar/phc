<?php
	// We replace > with <= and switch the paramters, after a pattern in the
	// zend_parser. However, we need to get the order right.

	function f () { echo "F called\n"; }
	function g () { echo "G called\n"; }

	if (f () > g ()) print "F is greater\n";
	else print "G is greater\n";

	if (g () >= f ()) print "G is greater or equal\n";
	else print "F is greater\n";
?>
