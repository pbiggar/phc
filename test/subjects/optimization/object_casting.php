<?php

	// How do arrays and objects cast?

	$x = new stdclass;
	$x->f = 5;
	$x->g = array ();
	$x->foo = create_function ('', "echo 'x\n';");

	$w = (array)($x);


	var_dump ($w);

	// Not allowed $w is not an object
	//$w->foo ();


	$y = array ("f" => 1, 2 => "g", null => 5);
	$z = (object)($y);
	$y->foo = create_function ('', "echo 'x\n';");
	var_dump ($z);

	$y->foo ();

?>
