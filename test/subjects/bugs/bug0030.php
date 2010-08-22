<?php

	// php_errormsg didn't work.
	// Bug report from jeanroch.rossi 

	ini_set("track_errors", true);

	function show_error()
	{
			  @strpos();
			  $error_message = $php_errormsg;
			  echo "inside the function : $error_message \n";
	}

	show_error();
?>
