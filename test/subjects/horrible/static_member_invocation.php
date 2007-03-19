<?php

	class X
	{
		static $foo;
		var $bar;
		function X()
		{
			$this->bar = "foobar";
		}	
	}

	echo X::$foo . "\n";
	
	$x = new X();
	echo $x->bar . "\n";
	
?>
