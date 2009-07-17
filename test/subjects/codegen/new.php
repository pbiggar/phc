<?php


	class X
	{
		function __construct (&$param)
		{
			$param = 10;
		}

	}


	$y = new X ($a[3][2]);

	var_dump ($a);

?>
