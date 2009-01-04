<?
	class C
	{
		var $a1, $a2;
		static $s1, $s2;
	}

	eval(<<<PHP
	\$c = new C();
	\$c->a1 = 1;
	\$c->a2 = 2;
	C::\$s1 = 3;
	C::\$s2 = 4;
PHP
	);

	$g1 =  $c->a1;
	$g2 =& $c->a2;
	$g3 =  C::$s1;
	$g4 =& C::$s2;

	$x = "a1"; $g5 =  $c->$x;
	$x = "a2"; $g6 =& $c->$x;
	$x = "s1"; $g7 =  C::$$x;
	$x = "s2"; $g8 =& C::$$x;

	eval('$c->a2 = 1234;');
	eval('C::$s2 = 4321;');

	var_dump($g1);
	var_dump($g2);
	var_dump($g3);
	var_dump($g4);
	var_dump($g5);
	var_dump($g6);
	var_dump($g7);
	var_dump($g8);
?>
