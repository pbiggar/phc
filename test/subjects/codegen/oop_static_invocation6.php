<?php
	// Call a protected static member from a parent class 

	class C
	{
		protected static function foo()
		{
			echo "C::foo()\n";
		}
	}

	class D extends C
	{
		function bar()
		{
			C::foo();
		}
	}
	
	D::bar();
?>
