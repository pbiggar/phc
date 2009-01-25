<?php
	// When a function uses a var-var, its local variables must be added to a
	// hashtable rather than added declared as local variables in the generated
	// C code. However, $this should never be added to the hashtable (see
	// function "foo" in test/subjects/unsupported/oop_assign_to_this2.php)

	class C
	{
		var $x = 5;

		function f()
		{
			$x = 1;
			$y = "x"; 
			$$y = 2; // use a var-var to force locals in the hashtable

			var_dump($x);
			var_dump($this->x);
		}
	}

	$c = new C();
	$c->f();
?>
