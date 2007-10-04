<?php
	// Make sure that the evaluation order of the arguments of isset
	// is the same after changing isset($x, $y) to isset($x) && isset($y)
	$ind = 1;

	function f()
	{
		global $ind;		// avoid reliance on 'static' 
		echo "f $ind\n";
		return $ind++;
	}
	
	$x[1] = 'a';
	
	if(isset($x[f()], $x[f()], $x[f()]))
	{
		echo "yes\n";
	}
	else
	{
		echo "no\n";
	}

	$x[4] = 'b';
	$x[5] = 'c';
	
	if(isset($x[f()], $x[f()], $x[f()]))
	{
		echo "yes\n";
	}
	else
	{
		echo "no\n";
	}

	$x[7] = 'd';
	$x[8] = 'e';
	$x[9] = 'f';
	
	if(isset($x[f()], $x[f()], $x[f()]))
	{
		echo "yes\n";
	}
	else
	{
		echo "no\n";
	}
?>
