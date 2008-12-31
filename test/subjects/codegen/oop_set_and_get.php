<?php
	class C1
	{
		var $a1;

		// Attributes must be prefixed using $this; otherwise, it's a local var
		// Moreover, __set and __get do not get called for declared attributes
		function f1()
		{
			echo "<C1::f1>\n";
			$a1 = 1;
			$this->a1 = 2;
			var_dump($a1);
			var_dump($this->a1);
			echo "</C1::f1>\n";
		}

		// Set and get only get called if the attribute is undeclared *and*
		// has not yet been added to the class
		function f2()
		{
			echo "<C1::f2>\n";
			$this->a2 = 3; 				// calls __set
			var_dump($this->a2);	// does not call __get

			var_dump($this->a3);	// calls __get
			var_dump($this->a3);	// calls __get
			$this->a3 = 4;				// calls __set
			$this->a3 = 5;				// does not call __set 
			var_dump($this->a3);	// does not call __get

			echo "</C1::f2>\n";
		}

		// Behaviour is similar for "variable" attributes
		function f3()
		{
			echo "<C1::f3>\n";

			$x = "a4";

			var_dump($this->$x);	// calls __get
			$this->$x = 6;				// calls __set
			var_dump($this->$x);	// does not call __get

			echo "</C1::f3>\n";
		}

		function __get($var)
		{
			echo "C1::__get($var)\n";
			return $this->$var;
		}

		function __set($var, $value)
		{
			echo "C1::__set($var)\n";
			$this->$var = $value;
		}
	}

	// __get without __set
	class C2
	{
		function f1()
		{
			echo "<C2::f1>\n";
			var_dump($this->a1);
			$this->a1 = 7;
			var_dump($this->a1);
			echo "</C2::f1>\n";
		}

		function __get($var)
		{
			echo "C2::__get($var)\n";
			return $this->$var;
		}
	}
	
	// __set without __get
	class C3
	{
		function f1()
		{
			echo "<C3::f1>\n";
			var_dump($this->a1);
			$this->a1 = 7;
			var_dump($this->a1);
			echo "</C3::f1>\n";
		}

		function __set($var, $value)
		{
			echo "C3::__set($var)\n";
			$this->$var = $value;
		}
	}

	// neither __set nor __get
	class C4
	{
		function f1()
		{
			echo "<C4::f1>\n";
			var_dump($this->a1);
			$this->a1 = 7;
			var_dump($this->a1);
			echo "</C4::f1>\n";
		}
	}

	// __get is recursively called only for variables *other* than the argument
	// to __get
	class C5
	{
		function f1()
		{
			echo "<C5::f1>\n";
			var_dump($this->a1);	
			var_dump($this->a2);	
			echo "</C5::f1>\n";
		}

		function __get($var)
		{
			echo "C5::__get($var)\n";
			return $this->a2;
		}
	}
	
	// __set is recursively called only for variables *other* than the argument
	// to __set (just like __get)
	class C6
	{
		function f1()
		{
			echo "<C6::f1>\n";
			$this->a1 = 5;
			unset($this->a2);
			$this->a2 = 5;
			echo "</C6::f1>\n";
		}

		function __set($var, $value)
		{
			echo "C6::__set($var)\n";
			$this->a2 = $value;
		}
	}

	// However, setting an undeclared attribute within __get *does* result in
	// a call to __set, and getting an undeclared attribute within __set *does*
	// result in a call to __get
	class C7
	{
		function f1()
		{
			echo "<C7::f1>\n";
			var_dump($this->a1);
			unset($this->a2);
			echo "****\n";
			var_dump($this->a2);
			echo "****\n";
			$this->a3 = 5;
			echo "</C7::f1>\n";
		}

		function __get($var)
		{
			echo "C7::__get($var)\n";
			$this->a2 = 1;
			return $this->$var;
		}

		function __set($var, $value)
		{
			echo "C7::__set($var)\n";
			var_dump($this->a3);
			$this->$var = $value;
		}
	}

	// Even when an attribute is accessed in a function which is invoked by a
	// a call to __get for that same attribute, __get is not recursively called
	class C8
	{
		function f1()
		{
			echo "<C8::f1>\n";
			var_dump($this->a1);
			echo "</C8::f1>\n";
		}

		function __get($var)
		{
			echo "C8::__get($var)\n";
			return $this->g($var);
		}

		function g($var)
		{
			echo "C8::g($var)\n";
			return $this->$var;
		}
	}

	$c1 = new C1;

	$c1->f1();
	var_dump($a1);

	$c1->f2();
	$c1->f3();

	$c2 = new C2(); $c2->f1();
	$c3 = new C3(); $c3->f1();
	$c4 = new C4(); $c4->f1();
	$c5 = new C5(); $c5->f1();
	$c6 = new C6(); $c6->f1();
	$c7 = new C7(); $c7->f1();
	$c8 = new C8(); $c8->f1();
?>
