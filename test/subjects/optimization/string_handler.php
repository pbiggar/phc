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

	echo "Call to explode\n";
	$a = explode ($x, $x);
	var_dump ($a);


	echo "Call to define\n";
	var_dump (define ($x, "ASD"));

	echo "Concatenation\n";
	$a1 = "" . $x;
	$a1a = $x . $x;
	$a1b = $x . "a string";
	var_dump ($a1, $a1a, $a1b);
	
	echo "Cast\n";
	$a2 = (string)($x);
	var_dump ($a2);

	echo "As a field index\n";
	$b->$x = 5;
	var_dump ($b);

	echo "As an array index\n";
	$c[$x] = 6;
	var_dump ($c);

	echo "In a var-var\n";
	$$x = 10;
	var_dump ($GLOBALS);



	echo "In a branch\n";
	if ($x)
	{
		echo "true\n";
	}
	else
	{
		echo "false\n";
	}

	echo "TODO: Others, which we can;t test so well:\n";
	echo "TODO: variable methods\n";
	echo "TODO: variable class instantiations\n";



?>
