<?php

	class C {}

	$x = $argv[2];
	if ($x)
		$y = new C;
	else if ($argv[3])
		$y = "str";
	else if ($argv[4])
		$y = 5;
	else
		$y[6] = 7;

	$z = (array)($y);
	$a = (object)($y);
	$a->f = 8;
	$z["a"] = 9;

	var_dump ($a);
	var_dump ($z);
	var_dump ($y);

?>
