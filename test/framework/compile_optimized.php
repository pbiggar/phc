<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compare compiled output to interpreted.
 */


array_push($tests, new CompileOptimized ());
class CompileOptimized extends CompiledVsInterpreted
{

	function get_dependent_test_names ()
	{
		return array ("CompiledVsInterpreted");
	}

	function get_phc_command ($subject, $exe_name)
	{
		global $phc;
		return "$phc -c -O1 $subject -o $exe_name";
	}

	function get_php_command ($subject)
	{
		global $phc;
		return "$phc -O1 --dump=sua $subject | ". get_php_command_line ($subject, "pipe");
	}
}

?>
