<?php
	$a = array(1,2,3,4,5);

	foreach($a as &$x1)
	{
		foreach($a as &$x2)
		{
			echo "$x1 $x2\n";
			$x1++;
			$x2++;
		}
	}

	var_dump($a);
?>
