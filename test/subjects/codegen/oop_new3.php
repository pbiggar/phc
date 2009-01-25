<?php
	/*
	 * When a class instance is created, attributes should be added to the object
	 * (with value NULL) for every attribute listed in the class.
	 *
	 * As this test shows, this cannot be done in the implementation of new, 
	 * since when we call 'new' through an eval statement, the attributes are
	 * not added either.
	 */

	class C
	{
		var $x;
	}

	$c = new C();
	var_dump($c);

	eval('$c2 = new C();');
	var_dump($c2);
?>
