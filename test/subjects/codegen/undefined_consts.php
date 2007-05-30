<?php
	function x ($x = Foo::BAR, $y = UNDEF::CONST_)
	{
		var_dump ($x);
		var_dump ($y);
		echo "\n";
	}

	x ();

	class Foo
	{
		const BAR = 7;
	}

	x ();

?>
