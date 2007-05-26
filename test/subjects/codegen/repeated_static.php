<?php
/*
 * It is allowed to repeat the static keyword.
 * Example due to jmarbas@hotmail.com
 */

	function f()
	{
		static $x = 0;
		static $x = 1;
		static $x = 2;
		var_dump($x);
		$x++;
	}

	f();
	f();
?>
