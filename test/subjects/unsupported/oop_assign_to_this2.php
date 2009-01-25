<?php
	// Access an attribute in an object using a var-var 

	class C
	{
		var $x = 5;

		function foo()
		{
			$n = "this";
			var_dump($$n->x); // shows NULL
		}

		function bar()
		{
			$n = "this";
			$$n = new StdClass();
			var_dump($this);
		}
	}

	$c = new C();
	$c->foo();
	$c->bar();
	
?>
