<?php
	function x ($x = Foo::BAR, $y = UNDEF::CON_ST)
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

?>
