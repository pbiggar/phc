<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unit test for dot output. Checks for syntax errors
 */

array_push($tests, new ParseASTDot ());
class ParseASTDot extends Test
{

	function get_test_subjects ()
	{
		return get_non_erroneous_scripts();
	}

	function check_prerequisites ()
	{
		global $graphviz_gc;
		return check_for_program ($graphviz_gc);
	}

	function run_test ($subject)
	{
		global $phc;
		global $graphviz_gc;

		// this is a bit odd. It throws away STDOUT,
		// and traps STDERR instead.  Changing the
		// order of 2> and > changes this behaviour.
		// TODO this only works on systems with
		// /dev/null - ie probably not cygwin
		$command = "$phc --dump-ast $subject 2>&1 | $graphviz_gc 2>&1 >/dev/null";
		list ($output, $return_value) = complete_exec($command);

		if ($output)
		{
			$this->mark_failure ($subject, $command, $return_value, $output);
		}
		else
		{
			$this->mark_success ($subject);
		}
	}
}



?>
