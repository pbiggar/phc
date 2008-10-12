<?php
	// assign to an already-initialized variable
	$a = 1;
	$x = "a";
	$$x = 2;
	echo $a;

	// assign to a non-initialized variable
	$x = "b";
	$$x = 3;
	echo $b;
?>
