<?php

	// { phc-error:  Class declarations may not be nested }

	class X
	{
		function x ()
		{
			class Y
			{
			}
		}
	}
?>
