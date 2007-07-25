<?php
	$x = array(1 => "a", 2 => "b", 3 => "c");

	echo "** 1 **\n";
	foreach($x as $y)
	{
		echo "$y\n";
	}
	
	echo "** 2 **\n";
	foreach($x as $y[0])
	{
		echo "$y\n";
	}
	
	echo "** 3 **\n";
	foreach($x as $y{0})
	{
		echo "$y\n";
	}

	echo "** 4 **\n";
	$a = array ('b' => 'b');
	foreach($x as $a->b)
	{
		echo "($a) $a->b\n";
	}

	/* Breaks */
	/*
	echo "** 5 **\n";
	foreach($x as $y[0][0])
	{
		echo "$y\n";
	}
	*/

	$xx = "x";

	echo "** 6 **\n";
	foreach($$xx as $y)
	{
		echo "$y\n";
	}
	
	echo "** 7 **\n";
	foreach($$xx as &$y)
	{
		echo "$y\n";
	}
	
	// Needs the following to avoid corruption of the array
	unset($y);
	
	echo "** 8 **\n";
	foreach($$xx as $y => $z)
	{
		echo "$y => $z\n";
	}
	
	echo "** 9 **\n";
	foreach($$xx as $y => &$z)
	{
		echo "$y => $z\n";
	}
?>
