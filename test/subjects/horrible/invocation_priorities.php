<?php
	class X
	{
		var $f;
		var $a;

		function X()
		{
			$this->f = "foo";
			$this->a = array("foo");
		}

		function foo()
		{
			echo "X::foo\n";
		}
	}

	function foo()
	{
		echo "foo\n";
	}

	$f = "foo";
	$a = array("foo");
	
	$x = new X();

	foo();					// foo
	$x->foo();				// X::foo
	$x->$f();				// X::foo
	$x->{"f" . "oo"}();	// X::foo
	$x->a[0]();				// foo
	$x->$a[0]();			// X::foo
?>
