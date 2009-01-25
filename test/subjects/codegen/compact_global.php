<?php

	// Check that 'global' does something at the global scope. It does - in this case, it sets $x to NULL (before it was uninit).

	var_dump (compact ("x"));
	global $x;
	var_dump (compact ("x"));


?>
