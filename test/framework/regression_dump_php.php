<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Regression test for the PHP unparser
 */

array_push($tests, new RegressionDumpPHP ());
class RegressionDumpPHP extends RegressionTest
{
	function get_test_subjects ()
	{
		return get_non_erroneous_scripts();
	}

	function get_support_filename ($subject)
	{
		$script_name = adjusted_name($subject, 1);
		global $support_dir;
		return "$support_dir/regression_dump_php/$script_name.unparsed";
	}

	function get_command_line ($subject)
	{
		global $phc;
		return "$phc --dump-php $subject --tab=\"   \" 2>&1";
	}
}



?>
