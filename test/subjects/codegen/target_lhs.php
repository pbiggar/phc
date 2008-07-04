<?php

	class X 
	{ 
		public $z = array (array (6,7,8,9), 1, 2, 3, 4, 5);
		public $x = array ("x" => "T");
	}


	$t = new X;
	$y = "z";
	$a = 0;
	$b = 1;

	var_dump ($t);

	$t->{$y}[$a][$b] = $t->x["x"];
	var_dump ($t);

?>
