<?php

	// { phc-option: -O1 --dump=codegen }
	// { phc-regex-output: !/\$[abcdewz123]/ }

	function test ()
	{
		$e = $a;
		$d = 1;
		$x = 7; // not DEAD
		$c = $d;
		$b = $c;
		var_dump ($x);
		$a = $b;
		$x = 3;
		$y = 2;
		$z = 1;
	}

?>
