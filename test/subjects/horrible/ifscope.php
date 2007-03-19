<?php
	function testif($c)
	{

		$x = 200;
		echo "x: $x\n";

		if($c)
		{
			global $x;
			$x = 300;
		}
		else
		{
			$x = 400;
		}
		echo "x: $x\n";

		$x = 500;

	}

	$x = 100;
	echo "x: $x\n";
	testif(true);
	echo "x: $x\n";

	$x = 600;
	echo "x: $x\n";
	testif(false);
	echo "x: $x\n";

?>
