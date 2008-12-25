<?php
	// Invocation of a static class method of a superclass
	// Like 3b, but without the 'static' keyword on the function 

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
	
	D::foo();
?>
