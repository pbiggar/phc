<?php

	// Tests for information we don't know.
	$x = 5;
	$y = array (6 => "str");
	class C
	{
		function __toString ()
		{
			global $z;
			$z = 12;
			echo "toString\n";
			return "result";
		}
	}

	$z = new C;
	$z = new C;

	$c->f = $x;

	eval ($argv[2]);

	echo ($z);
	echo ($y);
	echo ($x);
	var_dump ($c);
?>
