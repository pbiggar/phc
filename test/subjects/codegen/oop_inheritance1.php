<?php
	class C
	{
		var $x = 1;

		function foo()
		{
			$this->x = 2;
			echo "C::foo\n";
		}
	}

	class D extends C
	{
		function bar()
		{
			$this->foo();
			echo "D::bar\n";
		}
	}

	$d = new D();
	$d->bar();
	var_dump($d);
?>
