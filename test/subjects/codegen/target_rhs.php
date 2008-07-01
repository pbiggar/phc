<?php

	class Target
	{
		public $y = 42;
	}
	$r = "y";

	// Can't be simplified
	$x = $t->$y;
	var_dump ($x);

	// Can't be simplified
	$r = "y";
	$x = $t->$$r;
	var_dump ($x);



	// Array 
	$x = $t->y[$i];
	var_dump ($x);

	// Read only, doesnt affect the RHS.
	$T = $t->y;
	$x = $T[$i];
	var_dump ($x);


	// What about by-ref-  no longer read only
	$x =& $t->y[$i];
	var_dump ($x);

	// turn into:
	$T =& $t->y;
	$x =& $T[$i];
	var_dump ($x);
	// As long as we shred it by ref, its OK


	// Now with reflection
	$x = $t->$r[$i];
	var_dump ($x);

	// As above
	$T = $t->$r;
	$x = $T[$i];
	var_dump ($x);


	// And by-ref
	$x =& $t->$r[$i];
	var_dump ($x);

	// As above
	$T =& $t->$r;
	$x =& $T[$i];
	var_dump ($x);



	// Pre_op with reflection - can't shred
	++$t->$r[$i];
	var_dump ($x);

	// Pre-op -can't shred
	++$t->y;
	var_dump ($x);

?>
