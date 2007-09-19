<?php
	// Reduced with command line 'test/framework/reduce -v test/subjects/codegen/assignment.php'
	
	// Reference assignment, RHS is copy-on-write
	$Ah = 40;
	$Ai = $Ah;
	$Aj =& $Ai;
	$Aj = $Aj + $TLE3;
	$TSe8 = var_export($Ai);
?>
