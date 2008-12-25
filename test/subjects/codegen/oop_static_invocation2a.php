<?php
	// Invocation of a static class method
	// Like 1a, but without the 'static' keyword on the function 

	eval(<<<PHP
	class C
	{
		function foo()
		{
			echo "C::foo()\n";
		}
	}
PHP
 );
	
	C::foo();
?>
