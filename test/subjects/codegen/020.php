<?php
	function f($arg)
	{
		var_dump($arg);
	}

	function main()
	{
		$a = 5;
		var_dump($a);
		f($a);
	}	
?>
