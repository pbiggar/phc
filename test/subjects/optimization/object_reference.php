<?php

	class A{}

	$x = new A;
	$y =& $x;
	$y = 5;

	var_dump ($x);

?>
