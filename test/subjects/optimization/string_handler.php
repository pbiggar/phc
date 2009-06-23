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

			$result = "Hit $count\n\n";
			echo $result;
			return $result;
		}
	}

	function name ($title)
	{
		echo "\n\n******** $title ********************\n";
	}

	$x = new Handled;

	name ("Call to explode");
	$a = explode ($x, $x);
	var_dump ($a);


	name ("Call to define");
	var_dump (define ($x, "ASD"));

	name ("Concatenation");
	$a1 = "" . $x;
	$a1a = $x . $x;
	$a1b = $x . "a string";
	var_dump ($a1, $a1a, $a1b);
	
	name ("Cast");
	$a2 = (string)($x);
	var_dump ($a2);

	name ("As a field index");
	$b->$x = 5;
	var_dump ($b);

	name ("As an array index");
	$c[$x] = 6;
	var_dump ($c);

	name ("In a var-var");
	$$x = 10;
	var_dump ($GLOBALS);



	name ("In a branch");
	if ($x)
	{
		echo "true\n";
	}
	else
	{
		echo "false\n";
	}

	name ("TODO: Others, which we can;t test so well:");
	name ("TODO: variable methods");
	name ("TODO: variable class instantiations");



?>
