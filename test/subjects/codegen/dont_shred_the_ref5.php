<?php
	// Creating a reference to a field in an object will create that field
	// if it does not yet exist (but just accessing the field will not).
	// Hence, an argument of the form ($c->x) cannot be shredded, because
	// this may or may not create a reference to $c->x.

	function f($x)
	{
	}

	function g(&$x)
	{
	}

	class C
	{
	}

	$c = new C();
	var_dump($c);

	f($c->x);
	var_dump($c);

	g($c->y);
	var_dump($c);

	f($c->a[0]);
	var_dump($c);

	g($c->b[1]);
	var_dump($c);
	
	f($c->c[2][3]);
	var_dump($c);

	g($c->d[4][5]);
	var_dump($c);
?>
