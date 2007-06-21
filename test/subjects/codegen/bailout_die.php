<?php

	function my_error_handler ($errno, $errstr, $errfile, $errline, array $errcontext)
	{
		echo "errno: $errno\nerrstr: $errstr\nerrfile: $errfile\n$errline: $errline\n";
		var_export ($err_context);
	}

	set_error_handler ("my_error_handler", 
		E_ERROR| E_WARNING| E_PARSE| E_NOTICE| E_CORE_ERROR| E_CORE_WARNING|
		E_COMPILE_ERROR| E_COMPILE_WARNING| E_USER_ERROR| E_USER_WARNING|
		E_USER_NOTICE| E_ALL| E_STRICT| E_RECOVERABLE_ERROR);


	die ("asdasd");

?>
