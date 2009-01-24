<?php
	$GLOBALS = array();
	a ();
	var_dump ($GLOBALS);

	function a ()
	{
		$GLOBALS["x"] = 5;
	}

?>
