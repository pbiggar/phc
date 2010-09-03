<?php

	// Not allowed
//	$x->$f = 5;
//	var_dump ($x);

	// NULL becomes "" here.
	$y[$i] = 6;
	var_dump ($y);

	// This is hard to test (trying to clear GLOBALS is tough). Hwoever, it acts
	// the same as $y[$i].
//	$$z = 7;
//	var_dump ($GLOBALS);

?>
