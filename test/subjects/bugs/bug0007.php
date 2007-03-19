<?php
	// Class attributes may be keywords

	class C
	{
		public $class;

		function C()
		{
			$this->class = "foo";
		}
	}

	$c = new C();

	echo "$c->class";
	echo $c->class;
	echo $c->class;
	echo "$c->class";
?>
