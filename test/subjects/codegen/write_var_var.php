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

	$g = array (1,array (2, 3, array (4,5,6)));
	$h = "g";
	${$h}[1][2][3] = 7;
	var_dump ($g);

	$i = array (8,9);
	${$h}[1][2][3] =& $i[0];
	var_dump ($g);

?>
