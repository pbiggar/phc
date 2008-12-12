<?php

	require ("parsing/scalar_array.php");

	function write ($init, $insert)
	{
		echo "--------------------\n";
		echo "checking early write\n";
		$x = $init;
		$x[3] = $insert; // write in string
		var_dump ($x[2]);  // read val before
		var_dump ($x[3]); // read same val
		var_dump ($x[4]);  // read val after
		var_dump ($x[17]); // read out of string
		var_dump ($x);

		echo "--------------------\n";
		echo "checking late write\n";
		$x = $init;
		$x[17] = $insert;
		var_dump ($x[17]); // read same val
		var_dump ($x);

		echo "--------------------\n";
		echo "checking very early write\n";
		$x = $init;
		$x[-3] = $insert;
		var_dump ($x[-3]); // read same val
		var_dump ($x[-1]); // read early
		var_dump ($x);


		if (is_string ($init))
			return; // not supported, move to separate test case

		echo "--------------------\n";
		echo "checking early (ref) write\n";
		$x = $init;
		$x[3] =& $insert; // write in string
		var_dump ($x[2]);  // read val before
		var_dump ($x[3]); // read same val
		var_dump ($x[4]);  // read val after
		var_dump ($x[170]); // read out of string
		var_dump ($x);

		echo "--------------------\n";
		echo "checking late (ref) write\n";
		$x = $init;
		$x[170] =& $insert;
		var_dump ($x[170]); // read same val
		var_dump ($x);
	}
	
	function push ($init, $insert)
	{
		if (is_string ($init))
			return; // not supported. Move to separate test case

		// early and late dont make sense here
		echo "--------------------\n";
		echo "checking push\n";
		$x = $init;
		$x[] = $insert; // write in string
		var_dump ($x[2]);  // read val before
		var_dump ($x[3]); // read same val
		var_dump ($x[4]);  // read val after
		var_dump ($x[17]); // read out of string
		var_dump ($x);

		echo "--------------------\n";
		echo "checking (ref) push\n";
		$x = $init;
		$x[] =& $insert; // write in string
		var_dump ($x[2]);  // read val before
		var_dump ($x[3]); // read same val
		var_dump ($x[4]);  // read val after
		var_dump ($x[170]); // read out of string
		var_dump ($x);
	}

	foreach ($scalar_array as $init)
	{
		foreach ($scalar_array as $insert)
		{
			echo "--------------------\n";
			echo "Init: ";
			var_dump ($init);
			echo "Insert: ";
			var_dump ($insert);

			write ($init, $insert);
			push ($init, $insert);
		}
	}

	// TODO objects and resources

?>
