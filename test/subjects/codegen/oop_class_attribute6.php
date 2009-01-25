<?php
	// Test adding complex zvals (arrays) as class attributes

	class C
	{
		var $x = array(1,2,3);
	}

	$c = new C();
	$d = new C();
	var_dump($c);
	var_dump($d);

	// Make sure that each object has its own copy
	$c->x[4] = "extra";
	var_dump(count($c->x), count($d->x));
?>
