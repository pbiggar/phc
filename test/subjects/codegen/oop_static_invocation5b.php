<?php
	// Invalid: call a protected static member from outside the hierarchy 
	// Both class definition and method call are compiled 

	class C
	{
		protected static function foo()
		{
			echo "C::foo()\n";
		}
	}
	
	C::foo();
?>
