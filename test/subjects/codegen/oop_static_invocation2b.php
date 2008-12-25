<?php
	// Invocation of a static class method
	// Like 1b, but without the 'static' keyword on the function 

	class C
	{
		function foo()
		{
			echo "C::foo()\n";
		}
	}
	
	C::foo();
?>
