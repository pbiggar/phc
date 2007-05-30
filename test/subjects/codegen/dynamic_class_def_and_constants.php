<?php
	function x ($x = Foo::BAR, $y = UNDEF::CONST_)
	{
		var_dump ($x);
		var_dump ($y);
		echo "\n";
	}

	x ();

	// this is loaded at the start, so x () always has the value
	class Foo
	{
		const BAR = 7;
	}

	x ();



	// however, in the next instance, Xoo::XAR is only loaded when the statement
	// is processed. Another fine consistancy in PHP.

	y ();

	do
	{
		class Xoo
		{
			const XAR = 8;
		}
	} 
	while (false);

	function y ($y = Xoo::XAR)
	{
		var_dump ($y);
	}

	y ();

?>
