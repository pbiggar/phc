<?

	class X
	{
		function y ()
		{
			$this->x = 5;
		}
	}

	$x1 = new X;
	var_dump ($x1);
	var_dump ($x3);
	$x1->y ();

	$x3 = $x1;

	var_dump ($x1);
	var_dump ($x3);

	$x2 = new X;
	var_dump ($x2);
	var_dump ($x4);
	$x2->y ();
	$x4 = $x2;
	var_dump ($x2);
	var_dump ($x4);
