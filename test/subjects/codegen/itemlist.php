<?php
	class A {}
	$a = new A ();

	

	// This was found in the roadsend testsuite.
	$a->itemlist[] =& $a;
	$a->itemlist[] = 7;

	var_dump ($a);
?>
