<?php
/*
 * Fairly comprehensive test of assignments, dealing with "ordinary" variables,
 * arrays and variable variables, and testing normal assignment and reference 
 * assignment, and tests copy-on-write and change-on-write.
 * 
 * Does not deal with OO stuff, that should probably be tested separately.
 */

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
