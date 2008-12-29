<?php
	// Invalid: Call a private static member from a parent class 

	class C
	{
		private static function foo()
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
