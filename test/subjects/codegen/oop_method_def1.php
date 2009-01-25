<?php
	class C
	{
		function foo()
		{
			echo "C::foo()\n";
		}
	}
	
	class D
	{
		function foo()
		{
			echo "D::foo()\n";
		}
	}

	function foo()
	{
		echo "foo()\n";
	}

	eval(<<<PHP
	\$c = new C();
	\$d = new D();
	\$c->foo();
	\$d->foo();
	foo();
PHP
	);
?>
