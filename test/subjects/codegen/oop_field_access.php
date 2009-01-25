<?
	/*
	 * For each of 
	 *
	 *   - object attribute access
	 *   - (static) class attribute access
	 *   - variable object attribute access
	 *   - variable (static) class attribute access
	 *
	 * we test that
	 *
	 *   - regular assignment works and that after a regular assignment,
	 *     assigning to either variable does not affect the other
   *   - reference assignment works and that after a reference assignment,
	 *     assinging to either variables *does* affect the other
	 *   - reference assignment separates the RHS, if necessary
	 *
	 * for a total of 4 * 3 = 12 tests.
	 */

	class C
	{
		var $a1, $a2, $a3, $a4, $a5, $a6;
		static $s1, $s2, $s3, $s4, $s5, $s6;
	}

	eval(<<<PHP
	\$c = new C();
	\$c->a1 = 10;
	\$c->a2 = 20;
	\$c->a3 = 30;
	C::\$s1 = 40;
	C::\$s2 = 50;
	C::\$s3 = 60;
	
	\$c->a4 = 70;
	\$c->a5 = 80;
	\$c->a6 = 90;
	C::\$s4 = 100;
	C::\$s5 = 110;
	C::\$s6 = 120;
PHP
	);

	// Object attribute access

	echo("** object attribute access, regular assignment **\n");
	$g1 = $c->a1;
	eval('var_dump($g1); $g1++; var_dump($c->a1); $c->a1++; var_dump($g1);');

	echo("** object attribute access, reference assignment **\n");
	$g2 =& $c->a2;
	eval('var_dump($g2); $g2++; var_dump($c->a2); $c->a2++; var_dump($g2);');

	echo("** object attribute access, separation **\n");
	eval('$a3_copy = $c->a3;');
	$g3 =& $c->a3;
	eval('var_dump($g3); $g3++; var_dump($a3_copy); var_dump($c->a3);');

	// Class attribute access 

	echo("** class attribute access, regular assignment **\n");
	$g4 = C::$s1;
	eval('var_dump($g4); $g4++; var_dump(C::$s1); C::$s1++; var_dump($g4);');

	echo("** class attribute access, reference assignment **\n");
	$g5 =& C::$s2;
	eval('var_dump($g5); $g5++; var_dump(C::$s2); C::$s2++; var_dump($g5);');
	
	echo("** class attribute access, separation **\n");
	eval('$s3_copy = C::$s3;');
	$g6 =& C::$s3;
	eval('var_dump($g6); $g6++; var_dump($s3_copy); var_dump(C::$s3);');

	// Variable object attribute access
	
	echo("** variable object attribute access, regular assignment **\n");
	$x = "a4"; $v1 = $c->$x;
	eval('var_dump($v1); $v1++; var_dump($c->a4); $c->a4++; var_dump($v1);');

	echo("** variable object attribute access, reference assignment **\n");
	$x = "a5"; $v2 =& $c->$x;
	eval('var_dump($v2); $v2++; var_dump($c->a5); $c->a5++; var_dump($v2);');

	echo("** variable object attribute access, separation **\n");
	eval('$a6_copy = $c->a6;');
	$x = "a6"; $v3 =& $c->$x;
	eval('var_dump($v3); $v3++; var_dump($a6_copy); var_dump($c->a6);');

	// Variable class attribute access

	echo("** variable class attribute access, regular assignment **\n");
	$x = "s4"; $v4 = C::$$x;
	eval('var_dump($v4); $v4++; var_dump(C::$s4); C::$s4++; var_dump($v4);');

	echo("** variable class attribute access, reference assignment **\n");
	$x = "s5"; $v5 =& C::$$x;
	eval('var_dump($v5); $v5++; var_dump(C::$s5); C::$s5++; var_dump($v5);');
	
	echo("** variable class attribute access, separation **\n");
	eval('$s6_copy = C::$s6;');
	$x = "s6"; $v6 =& C::$$x;
	eval('var_dump($v6); $v6++; var_dump($s6_copy); var_dump(C::$s6);');
?>
