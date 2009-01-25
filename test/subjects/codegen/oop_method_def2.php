<?php
	// Test that $this is added to the local variables
	class C
	{
		var $x;

		function f()
		{
			$this->x = 1;
			echo "C::f\n";
		}
	}

	eval('$c = new C(); $c->f(); var_dump($c);');
?>
