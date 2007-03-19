<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Regression test for the dot (AST) unparser
 */

array_push($tests, new RegressionDumpAST ());
class RegressionDumpAST extends RegressionTest
{
	function get_test_subjects ()
	{
		return get_non_erroneous_scripts();
	}

	function get_support_filename ($subject)
	{
		global $support_dir;
		$script_name = adjusted_name($subject, 1);
		return "$support_dir/regression_dump_ast/$script_name.dot";
	}

	function get_command_line ($subject)
	{
		global $phc;
		return "$phc --dump-ast-dot $subject 2>&1";
	}
}

?>
