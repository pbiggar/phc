<?php
	// Declared attributes should be added to class instances with value NULL

	class C
	{
		var $a;
	}

	eval('$c = new C();');
	var_dump($c);
?>
