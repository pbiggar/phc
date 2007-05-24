<?php
/*
 * Fairly comprehensive test of assignments, dealing with "ordinary" variables,
 * arrays and variable variables, and testing normal assignment and reference 
 * assignment, and tests copy-on-write and change-on-write.
 * 
 * Does not deal with OO stuff, that should probably be tested separately.
 */

/*
 * Simple variables
 */
	// Normal assignment
	$Aa = 10;
	$Ab = $Aa;
	$Ab = $Ab + 1;
	var_export($Aa);
	var_export($Ab);

	// Reference assignment
	$Ac = 20;
	$Ad =& $Ac;
	$Ad = $Ad + 1;
	var_export($Ac);
	var_export($Ad);

	// Normal assignment, RHS is_ref
	$Ae = 30;
	$Af =& $Ae;
	$Ag = $Af;
	$Ag = $Ag + 1;
	var_export($Ae);
	var_export($Af);
	var_export($Ag);

	// Reference assignment, RHS is copy-on-write
	$Ah = 40;
	$Ai = $Ah;
	$Aj =& $Ai;
	$Aj = $Aj + 1;
	var_export($Ah);
	var_export($Ai);
	var_export($Aj);

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

/*
 * Variable variables
 */

	$Ca = "Da";
	$Cb = "Db";
	$Cc = "Dc";
	$Cd = "Dd";
	$Ce = "De";
	$Cf = "Df";
	$Cg = "Dg";
	$Ch = "Dh";
	$Ci = "Di";
	$Cj = "Dj";
	
	// Normal assignment
	$$Ca = 10;
	$$Cb = $$Ca;
	$$Cb = $$Cb + 1;
	var_export($$Ca);
	var_export($$Cb);
	var_export($Da);
	var_export($Db);

	// Reference assignment
	$$Cc = 20;
	$$Cd =& $$Cc;
	$$Cd = $$Cd + 1;
	var_export($$Cc);
	var_export($$Cd);
	var_export($Dc);
	var_export($Dd);

	// Normal assignment, RHS is_ref
	$$Ce = 30;
	$$Cf =& $$Ce;
	$$Cg = $$Cf;
	$$Cg = $$Cg + 1;
	var_export($$Ce);
	var_export($$Cf);
	var_export($$Cg);
	var_export($De);
	var_export($Df);
	var_export($Dg);

	// Reference assignment, RHS is copy-on-write
	$$Ch = 40;
	$$Ci = $$Ch;
	$$Cj =& $$Ci;
	$$Cj = $$Cj + 1;
	var_export($$Ch);
	var_export($$Ci);
	var_export($$Cj);
	var_export($Dh);
	var_export($Di);
	var_export($Dj);
?>
