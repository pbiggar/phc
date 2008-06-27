<?php

	// In dce001, each statement takes 1 pass to remove. This tests it if we
	// know that a few things can be removed with each pass. This will mean that
	// the complexity of the algorithm is related to the depth of dependences
	// between live variables and their uses, instead of related to the number
	// of dead statements.

	// A series of dead assignments (the number is the pass in which they are eliminated).
	$e = $a; // 1
	$d = 1; // 4
	$c = $d; // 3
	$b = $c; // 2
	$a = $b; // 1
	$x = 3; // 1
	$y = 2; // 1
	$z = 1; // 1

?>
