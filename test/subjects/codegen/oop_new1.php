<?php
	$b =& $a;
	$b = new StdClass();
	var_dump($a);
	var_dump($b);

	$d =& $c;
	$d =& new StdClass();
	var_dump($c);
	var_dump($d);

	$x = "StdClass";

	$f =& $e;
	$f = new $x();
	var_dump($e);
	var_dump($f);

	$h =& $g;
	$h =& new $x();
	var_dump($g);
	var_dump($h);
?>
