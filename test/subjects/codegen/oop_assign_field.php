<?php
	// Test all the various macros for assigning to fields

	class C
	{
		// Although normal attributes do not necessarily need to be declared,
		// static attributes *do* 
		var $a1, $a2, $a3, $a4;
		static $s1, $s2, $s3, $s4;
	}

	eval('$c = new C();');
	$g = -1;
	
	$c->a1 = 1;
	$c->a2 =& $g;
	C::$s1 = 3;
	C::$s2 =& $g;

	$x = "a3"; $c->$x = 5;
	$x = "a4"; $c->$x =& $g;
	$x = "s3"; C::$$x = 7;
	$x = "s4"; C::$$x =& $g;

	$g = 1234;

	eval(<<<PHP
	var_dump($\c);
	var_dump(C::\$s1);
	var_dump(C::\$s2);
	var_dump(C::\$s3);
	var_dump(C::\$s4);
PHP
	);
?>
