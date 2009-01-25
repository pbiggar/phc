<?php
	/*
	 * Test the __call is invoked 
	 */

	eval(<<<PHP
	class C
	{
		function foo(\$x, \$y)
		{
			echo "C::foo(\$x, \$y)\n";
			\$this->x = 1;
		}

		function __call(\$fname, \$args)
		{
			echo "Call to \$fname with arguments:\n";
			var_dump(\$args);
		}
	}

	\$c = new C(); 
PHP
	);

	$c->foo(1, 2);
	$c->bar(1, 2);
?>
