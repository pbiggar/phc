<?php
	// Invocation of a static class method
	// Class *definition* is interpreted

	eval(<<<PHP
	class C
	{
		static function foo()
		{
			echo "C::foo()\n";
		}
	}
PHP
 );
	
	C::foo();
?>
