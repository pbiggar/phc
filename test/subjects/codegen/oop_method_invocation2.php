<?php
	/*
	 * Test that the $this pointer is properly set
	 */

	eval(<<<PHP
	class C
	{
		function foo()
		{
			echo "C::foo\n";
			\$this->x = 1;
		}
	}

	\$c = new C(); 
PHP
	);

	$c->foo();
	var_dump($c);
?>
