<?php

	$a = "x1";
	$b = "x2";
	$c = "x3";
	$d = "x4";
	$e = "x5";
	$f = "x6";
	$g = "x7";
	$h = "x8";

	class X { public $x2 = array("x3" => array ("x4" => NULL)) ; }
	class Y { public $x5 = array("x6" => 7) ; }
	$x1 = new X();
	$x1->x2["x3"]["x4"] = new Y ();
	$x7 = array ("x8" => 23);

	// Whats the most convoluted pre_op/op-assignment I can do?
	$$a->{$b}[$$c][$$d]->$e[$$f] += $$g[$$h];

	var_dump ($x1);
	var_dump ($x2);
	var_dump ($x3);
	var_dump ($x4);
	var_dump ($x5);
	var_dump ($x6);
	var_dump ($x7);
	var_dump ($x8);
?>
