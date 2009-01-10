<?php
	// Invocation of a method on an object
	eval(<<<PHP
	class C
	{
		function foo()
		{
			echo "C::foo\n";
		}
	}

	class D
	{
		function foo()
		{
			echo "D::foo\n";
		}
	}

	\$c = new C(); 
	\$d = new D();
PHP
	);

	$c->foo();
	$d->foo();

	var_dump($c);
	var_dump($d);
?>
