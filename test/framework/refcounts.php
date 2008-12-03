<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Adds debug_zval_dump after each statement, then compared the outputs of the
 * compiled and interpreted code.
 */


array_push($tests, new Refcounts ());
class Refcounts extends CompiledVsInterpreted
{

	function get_dependent_test_names ()
	{
		return array ("CompiledVsInterpreted");
	}

	function get_phc_command ($subject, $exe_name)
	{
		global $phc;
		return "$phc -c --run plugins/tools/debug_zval.la $subject -o $exe_name";
	}

	function get_php_command ($subject)
	{
		global $phc;
		return "$phc --run plugins/tools/debug_zval.la --dump-uppered=plugins/tools/debug_zval.la $subject | ". get_php_command_line ($subject, "pipe");
	}
}

?>
