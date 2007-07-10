<?php
/*
 * Fairly comprehensive test of assignments, dealing with "ordinary" variables,
 * arrays and variable variables, and testing normal assignment and reference 
 * assignment, and tests copy-on-write and change-on-write.
 * 
 * Does not deal with OO stuff, that should probably be tested separately.
 */

/*
 * Arrays
 */
	
	// Normal assignment
	$Ba[0] = 10;
	$Bb[0] = $Ba[0];
	$Bb[0] = $Bb[0] + 1;
	var_export($Ba);
	var_export($Bb);

	// Reference assignment
	$Bc[0] = 20;
	$Bd[0] =& $Bc[0];
	$Bd[0] = $Bd[0] + 1;
	var_export($Bc);
	var_export($Bd);

	// Normal assignment, RHS is_ref
	$Be[0] = 30;
	$Bf[0] =& $Be[0];
	$Bg[0] = $Bf[0];
	$Bg[0] = $Bg[0] + 1;
	var_export($Be);
	var_export($Bf);
	var_export($Bg);

	// Reference assignment, RHS is copy-on-write
	$Bh[0] = 40;
	$Bi[0] = $Bh[0];
	$Bj[0] =& $Bi[0];
	$Bj[0] = $Bj[0] + 1;
	var_export($Bh);
	var_export($Bi);
	var_export($Bj);

?>
