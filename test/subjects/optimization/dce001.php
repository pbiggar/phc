<?php

	// A series of dead assignments
	$d = 1; // DEAD once $c = $d is dead
	$c = $d; // DEAD once $b = $c is dead
	$b = $c; // DEAD once $a = $b is dead
	$a = $b; // DEAD

?>
