<?php
	class C
	{
		var $x;

		function __construct($x)
		{
			$this->x = $x;
		}

		function foo($that)
		{
			var_dump($this->x);

			$this = $that;
			var_dump($this->x);
		}
	}

	$c1 = new C(1);
	$c2 = new C(2);

	$c1->foo($c2);
?>
