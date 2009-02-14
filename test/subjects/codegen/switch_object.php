<?php

	class Obj
	{
		private $x;
		function Obj ($_x)
		{
			$x = $_x;
		}
	}
	$instance1 = new Obj (7);
	$instance2 = new Obj (new Obj ("asdasd"));
	$instance3 = new Obj (new Obj ("asdasd"));


	switch ($instance3)
	{
		case 0:
			echo "zero\n";
			break;
		case $instance2:
			echo "the same\n";
			break;
		case 7:
			echo "seven\n";
			break;
		default:
			echo "none of the above\n";
			break;
	}
?>
