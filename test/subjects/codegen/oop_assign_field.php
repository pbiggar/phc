<?php
	/*
	 * This test is completely analogous to oop_field_assignments.php
   *
	 * For each of 
	 *
	 *   - object attribute assignment
	 *   - (static) class attribute assignment
	 *   - variable object attribute assignment
	 *   - variable (static) class attribute assignment
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

	eval('$c = new C();');

	$g1 = 10;
	$g2 = 20;
	$g3 = 30;
	$g4 = 40;
	$g5 = 50;
	$g6 = 60;

	$v1 = 10;
	$v2 = 20;
	$v3 = 30;
	$v4 = 40;
	$v5 = 50;
	$v6 = 60;

	// Object attribute assignment

	echo("** object attribute assignment, regular assignment **\n");
	$c->a1 = $g1;
	eval('var_dump($c->a1); $g1++; var_dump($c->a1); $c->a1++; var_dump($g1);');

	echo("** object attribute assignment, reference assignment **\n");
	$c->a2 =& $g2;
	eval('var_dump($c->a2); $g2++; var_dump($c->a2); $c->a2++; var_dump($g2);');

	echo("** object attribute assignment, separation **\n");
	eval('$g3_copy = $g3;');
	$c->a3 =& $g3;
	eval('var_dump($c->a3); $g3++; var_dump($g3_copy); var_dump($c->a3);');

	// Class attribute assignment 

	echo("** class attribute assignment, regular assignment **\n");
	C::$s1 = $g4;
	eval('var_dump(C::$s1); $g4++; var_dump(C::$s1); C::$s1++; var_dump($g4);');

	echo("** class attribute assignment, reference assignment **\n");
	C::$s2 =& $g5;
	eval('var_dump(C::$s2); $g5++; var_dump(C::$s2); C::$s2++; var_dump($g5);');
	
	echo("** class attribute assignment, separation **\n");
	eval('$g6_copy = $g6;');
	C::$s3 =& $g6;
	eval('var_dump(C::$s3); $g6++; var_dump($g6_copy); var_dump(C::$s3);');

	// Variable object attribute assignment
	
	echo("** variable object attribute assignment, regular assignment **\n");
	$x = "a4"; $c->$x = $v1;
	eval('var_dump($c->a4); $v1++; var_dump($c->a4); $c->a4++; var_dump($v1);');

	echo("** variable object attribute assignment, reference assignment **\n");
	$x = "a5"; $c->$x =& $v2;
	eval('var_dump($c->a5); $v2++; var_dump($c->a5); $c->a5++; var_dump($v2);');

	echo("** variable object attribute assignment, separation **\n");
	eval('$v3_copy = $v3;');
	$x = "a6"; $c->$x =& $v3;
	eval('var_dump($c->a6); $v3++; var_dump($v3_copy); var_dump($c->a6);');

	// Variable class attribute assignment

	echo("** variable class attribute assignment, regular assignment **\n");
	$x = "s4"; C::$$x = $v4;
	eval('var_dump(C::$s4); $v4++; var_dump(C::$s4); C::$s4++; var_dump($v4);');

	echo("** variable class attribute assignment, reference assignment **\n");
	$x = "s5"; C::$$x =& $v5;
	eval('var_dump(C::$s5); $v5++; var_dump(C::$s5); C::$s5++; var_dump($v5);');
	
	echo("** variable class attribute assignment, separation **\n");
	eval('$v6_copy = $v6;');
	$x = "s6"; C::$$x =& $v6;
	eval('var_dump(C::$s6); $v6++; var_dump($v6_copy); var_dump(C::$s6);');
?>
