<?php

	/*
	 * Test everywhere an object might be converted into a string
	 */

	unset ($GLOBALS);

	class Handled
	{
		function __toString ()
		{
			static $count = 0;

			$count++;

			$result = "Hit $count\n";
			echo $result;
			return $result;
		}
	}

	$x = new Handled;

	// In a function taking a string
	$a = explode ($x, $x);
	var_dump ($a);


	var_dump (define ($x, "ASD"));


	// Concatenation
	$a1 = "" . $x;
	$a1a = $x . $x;
	$a1b = $x . "a string";
	var_dump ($a1, $a1a, $a1b);
	
	// Cast
	$a2 = (string)($x);
	var_dump ($a2);

	// As a field index
	$b->$x = 5;
	var_dump ($b);

	// As an array index
	$c[$x] = 6;
	var_dump ($c);

	// In a var-var
	$$x = 10;
	var_dump ($GLOBALS);



	// In a branch
	if ($x)
	{
		echo "true\n";
	}
	else
	{
		echo "false\n";
	}

	// Others, which we can;t test so well:
	// variable methods
	// variable class instantiations



?>
