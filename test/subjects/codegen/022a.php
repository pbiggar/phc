<?php
	function f($arg)
	{
		var_dump(&$arg);
		$arg = 6;
	}

	$a = 5;
	$b = &$a;
	f($b);

	var_dump($a);
?>
