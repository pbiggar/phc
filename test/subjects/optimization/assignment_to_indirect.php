<?php

	function test ()
	{
		global $a;
		$a = 5;
		$a = 8;
		f ();
		$a = 6;
		f ();
		$a = 7;
		f ();
	}

	function f ()
	{
		global $a;
		var_dump ($a);
	}

	test ();
