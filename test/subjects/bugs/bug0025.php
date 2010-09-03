<?

	// Reported by Gary Wassermann.
	// August 17th, 2007

	// A::bar doesnt update A::q appropriately.
	class A
	{
		static $q = 2345;
		function bar()
		{
			A::$q++;
			echo A::$q, "\n";
		}
	}
	A::bar();
	var_dump (A::$q);
	A::bar();
	var_dump (A::$q);
	A::bar();
	var_dump (A::$q);


	$q = 2345;
	$q++;
	var_dump ($q);
	$q++;
	var_dump ($q);
	$q++;
	var_dump ($q);
?>
