<?php
/*
 * Reference to a static variable
 * Example due to info@SyPlex.net
 */

	function &getStatic()
	{
		static $staticVar = 0;
		return $staticVar;
	}

	function f()
	{
		$x =& getStatic();
		var_export($x);
		$x++;
	}

	function g()
	{
		$y =& getStatic();
		var_export($y);
		$y++;
	}
	
	f();
	g();
	f();
	g();
?>
