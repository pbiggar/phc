<?php

	function test ()
	{
		// { phc-option: --dump=codegen -O1  }

		// Check unused pure functinos are remove
		// { phc-regex-output: !/strlen/ }
		var_dump (strlen ("my_string"));

		// Check assign_array folded
		// { phc-regex-output: !/\$i = 5/ }
		$i = 5;
		$x[$i] = 0;
		var_dump ($x);

		// Check access_array folded
		// { phc-regex-output: !/my_string/ }
		$str = "my_string";
		echo ($str[6]);

		// Check uses of uninitialized vars are optimized to NULL
		// { phc-regex-output: !/uninit/ }
		$a1[$uninit] = 5;
		$c = 5 + $uninit;
		$x = !$uninit;
		echo ($x);
		echo ($c);
		echo ($a1);
	}

	test ();

?>
