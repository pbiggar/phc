<?php
	define("FOO", 1);

	class C
	{
		const X = 2;
	}


	class D
	{
		var $b = array(FOO => 3); 
		var $c = array(C::X => 3); 
	}

	$d = new D();
	var_dump($d->b);
	var_dump($d->c);

	function f()
	{
		static $y = array(FOO => 3);
		static $z = array(C::X => 2);

		var_dump($y);
		var_dump($z);
	}

	f();
?>
