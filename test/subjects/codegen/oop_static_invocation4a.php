<?php
	// Invocation of a static class method of a superclass
	// Like 3a, but without the 'static' keyword on the function 

	eval(<<<PHP
	class C
	{
		function foo()
		{
			echo "C::foo()\n";
		}
	}

	class D extends C
	{
	}
PHP
 );
	
	D::foo();
?>
