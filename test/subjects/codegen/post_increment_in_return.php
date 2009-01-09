<?php
	$i = 0;

	function f()
	{
		global $i;
		return $i++;
	}

	var_dump(f() + $i);
	var_dump(f() + $i);
	var_dump(f() + $i);
?>
