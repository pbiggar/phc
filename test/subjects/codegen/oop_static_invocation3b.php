<?php
	// Invocation of a static class method of a superclass
	// Both the class definition and the invocation are compiled 

	class C
	{
		static function foo()
		{
			echo "C::foo()\n";
		}
	}

	class D extends C
	{
	}
	
	D::foo();
?>
