<?php
	class C
	{
		var $x = 1; 
		var $y = "hello";
		var $z = 2.5;
	}

	eval('$c = new C(); var_dump($c);');
?>
