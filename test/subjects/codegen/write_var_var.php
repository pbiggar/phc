<?php
	$x = "y";
	$$x = 5;
	var_dump($y);

	$a = array(1,2,3);
	$b = "a";
	${$b}[1] = 10;
	var_dump($a);

	$d = 1.5;
	$e = "f";
	${$e} =& $d;
	$f = $f + 1.0;
	var_dump($d);
?>
