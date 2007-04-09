<?php
	function main()
	{
		$a = 1;
		$b = $a;
		$c = &$a;
		debug_zval_dump($a);
		debug_zval_dump($b);
		debug_zval_dump($c);
	}
?>
