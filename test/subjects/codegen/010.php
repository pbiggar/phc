<?php
	function main()
	{
		$a = 1;
		$b = &$a;
		unset($a);
		var_dump($a);
		var_dump($b);
	}
?>
