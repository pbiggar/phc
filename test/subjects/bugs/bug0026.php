<?php

	// Reported by Ruslan Kosolapov

	class A { function x() { return "str"; } }
	$a = new A;
	$filename = "{$a->x($class)}{$chain}{$class}.php";
	echo $filename;
?>
