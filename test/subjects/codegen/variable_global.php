<?php
	function f($x)
	{
		global $$x;
		$y = 5;
	}

	f("y");
	var_dump($y);
?>
