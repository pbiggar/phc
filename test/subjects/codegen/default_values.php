<?php
	function f($a, $b = 2, $c = 3)
	{
		var_export($a);
		var_export($b);
		var_export($c);
	}

	function g($d = array(1,2))
	{
		var_export($d);
	}

	function h($e = array(1,array(2 => 3, 'a' => 4),True,"hi",2.5))
	{
		var_export($e);
	}

	f(0);
	f(0,0);
	f(0,0,0);

	g();
	g(0);

	h();
	h(0);
?>
