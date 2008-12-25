<?php
	// Invocation of a static class method
	// Both the class definition and the invocation are compiled 

	class C
	{
		static function foo()
		{
			echo "C::foo()\n";
		}
	}
	
	C::foo();
?>
