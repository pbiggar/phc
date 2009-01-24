<?php
	// Test that static attributes do not show up as instance attributes

	class C
	{
		static $s;
	}

	eval('$c = new C(); var_dump($c);');
?>
