<?php

	function j($j1, $j2)
	{
		global $i1;
		global $i2;
		echo $i1;
		echo $i2;

		echo $j1;
		echo $j2;

		if($i1 != "some value" and $i2 != "another value")
		{
			fail(__FILE__, __LINE__, "using variables in included function");
		}

		return 6;
	}


?>
