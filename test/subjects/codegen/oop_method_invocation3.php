<?php
	/*
	 * Test argument passing to methods 
	 */

	eval(<<<PHP
	class C
	{
		// Simple arguments
		function fsimple(\$x, \$y)
		{
			echo "C::foo(\$x, \$y)\n";
		}
		
		function fref1(\$x)
		{
			\$x = 1;
			\$this->a1 =& \$x;
		}
		
		function fref2(\$x)
		{
			\$x = 1;
			\$this->a2 =& \$x;
		}

		function fref3(&\$x)
		{
			\$x = 1;
			\$this->a3 =& \$x;
		}
	}

	\$c = new C(); 
PHP
	);

	echo "** Simple argument passing test\n";
	$c->fsimple(1, 2);

	echo "** Pass by value\n";
	$g1 = 0; 
	$c->fref1($g1); var_dump($g1);
	$c->a1 = 2; var_dump($g1);

	echo "** Runtime pass-by-reference\n";
	$g2 = 0; 
	$c->fref2(&$g2); var_dump($g2);
	$c->a2 = 2; var_dump($g2);
	
	echo "** Compile-time pass-by-reference\n";
	$g3 = 0; 
	$c->fref3($g3); var_dump($g3);
	$c->a3 = 2; var_dump($g3);

	echo "** Final state of the object\n";
	var_dump($c);
?>
