<?php
	// Invalid: call a protected static member from outside the hierarchy 
	// Class *definition* is interpreted

	eval(<<<PHP
	class C
	{
		protected static function foo()
		{
			echo "C::foo()\n";
		}
	}
PHP
 );
	
	C::foo();
?>
