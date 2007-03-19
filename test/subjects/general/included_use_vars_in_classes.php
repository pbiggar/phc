<?php

	class K
	{
		var $my_var;

		function K()
		{
			$my_var = 6;
		}

		function kk()
		{
			global $i1;
			global $i2;

			var_dump($i1);
			var_dump($i2);
			if($i1 != "some value" and $i2 != "another value")
			{
				fail(__FILE__, __LINE__, "using variables in included class");
			}

			return $my_var;
		}
	}

	
?>
