<?php
/*
 * Returning values by reference. Only the statement marked (*) will actually
 * create a reference to $a (so, both the function and the assignment must be
 * is_ref).
 */

	function &h()
	{
		// return an uninit var
		return $GLOBALS["x"];
	}

	$a = 5;
	$f =& h();
	$f = $f + 1;
	unset ($a);
	unset ($x);
	unset ($f);
	var_export($a);
	var_export($f);

// TODO:
	$eval_code = '
	$a = 5;
	$g =& h();
	$g = $f + 1;
	unset ($a);
	unset ($x);
	unset ($g);
	var_export($a);';
	eval ($eval_code);
?>
