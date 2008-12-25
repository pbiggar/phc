<?php
	// Invocation of a static class method of a superclass
	// Class *definition* is interpreted

	eval(<<<PHP
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
PHP
 );
	
	D::foo();
?>
