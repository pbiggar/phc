<?php
	// Method invocation on $this

	class C
	{
		function foo($x, $y)
		{
			echo "C::foo($x, $y)\n";
			$this->bar($y, $x);
		}

		function bar($x, $y)
		{
			echo "C::bar($x, $y)\n";
		}
	}

	$c = new C();
	$c->foo(1, 2);
?>
