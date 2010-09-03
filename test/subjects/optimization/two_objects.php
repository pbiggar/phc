<?php

	// X has the exists() method, Y doesnt. Therefore, we can't be looking at
	// the instance of Y, or it would have failed.
	class X
	{
		var $var = 5;

		function exists ()
		{
		}
	}

	class Y
	{
		var $var = 7;
	}


	if ($argc)
	{
		$o = new X;
	}
	else
	{
		$o = new Y;
	}

	$o->exists ();

	echo ($o->var);

?>
