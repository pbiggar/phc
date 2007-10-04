<?php
	class C
	{
		var $x;
		var $y = 1;
	}

	$c = new C();
	var_dump(empty($c->x));
	var_dump(empty($c->y));
?>	
