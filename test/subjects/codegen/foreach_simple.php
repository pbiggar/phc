<?php

	$a = array ("a" => "A", "b" => "B", 0 => 7, "a" => "Z");
	foreach ($a as $key => $val)
	{
		$b = $a; // supposedly, copying arrays while using each () will lead to bad results
		var_export ($b);
	}
?>
