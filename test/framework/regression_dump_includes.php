<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * Regression test for compile-time includes
 */

array_push($tests, new RegressionDumpIncludes ());
class RegressionDumpIncludes extends RegressionTest
{
	function get_test_subjects ()
	{
		return get_includable_scripts ();
	}

	function get_support_filename ($subject)
	{
		$script_name = adjusted_name($subject, 1);
		global $support_dir;
		return "$support_dir/regression_dump_includes/$script_name.unparsed";
	}

	function get_command_line ($subject)
	{
		global $phc;
		return "$phc --dump-php --tab=\"   \" --compile-time-includes $subject 2>&1";
	}
}

?>
