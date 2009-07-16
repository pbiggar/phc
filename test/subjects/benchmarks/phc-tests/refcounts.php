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
		global $phc, $plugin_dir;
		return get_phc_command_line ($subject) . " -c --run $plugin_dir/tools/debug_zval.la -o $exe_name";
	}

	function get_php_command ($subject)
	{
		global $phc, $plugin_dir;
		return "$phc --run $plugin_dir/tools/debug_zval.la --convert-uppered --dump=$plugin_dir/tools/debug_zval.la $subject | ". get_php_command_line ($subject, "pipe");
	}
}

?>
