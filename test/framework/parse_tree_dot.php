<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unit test for dot output. Checks for syntax errors
 */

array_push($tests, new ParseTreeDot ());
class ParseTreeDot extends AsyncTest
{
	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	function get_dependent_test_names ()
	{
		return array ("BasicParseTest");
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

		$async = new AsyncBundle ($this, $subject);

		$async->commands[0]		= "$phc --dump-parse-tree $subject | $graphviz_gc";
		// there is output. Dont fail.
		$async->err_handlers[0] = "fail_on_output";

		$async->final = "async_success";
		$async->start ();
	}
}

?>
