<?php
	class Foo
	{
		static $x;
		  
		static $x = 10;
		static $x = FOO;
		static $x = FOO::bar;
	
		static $x, $y;
	
		static $x = array(1,2,3);
		static $x = array(1 => 2, 2 => 3);
		static $x = array(FOO => BAR, FOOBAR);

		static $x = +5;
		static $x = -5;
	}

	$y = Foo::$x;
?>
