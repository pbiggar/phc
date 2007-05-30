<?php

	class A
	{
		// if this moves into the constructor, it wont be initialized, since B doesnt call the constructor
		var $a = array ("7", "6");
	}

	class B extends A
	{
		function __construct ()
		{
			var_dump ($this->a);
		}
	}

	$b = new B ();
	var_dump ($b);
?>
