<?php
	function f(&$arg)
	{
		debug_zval_dump(&$arg);
		$arg = 6;
	}

	function main()
	{
		$a = 5;
		$b = &$a;
		f($b);

		debug_zval_dump($a);
	}
?>
