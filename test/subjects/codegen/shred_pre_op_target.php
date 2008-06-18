<?php

	// can we shred this?
	$x = array ('y' => 7);
	$x["y"]++;
	var_dump ($x);

	// or this?
	class Y { public $y = 12; }
	$y = new Y;
	++$y->y;
	var_dump ($y);

	$n1 = "y";
	$n2 = "y";
	++$$n1->$n2;

	var_dump ($x);

?>
