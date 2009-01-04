<?php
	class C
	{
		const a = 1;

		function foo()
		{
			var_dump(a);
		}
	}

	$c = new C();
	$c->foo();
?>
