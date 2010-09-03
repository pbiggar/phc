<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that an unparsed script, when reparsed, has the same output.
 */

array_push($tests, new ReparseUnparsed ());
class ReparseUnparsed extends AsyncTest
{
	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	function get_dependent_test_names ()
	{
		return array ("BasicParseTest");
	}

	function run_test ($subject)
	{
		global $phc;

		$async = new AsyncBundle ($this, $subject);

		$async->commands[0] = "cat $subject | $phc --pretty-print";
		$async->commands[1] = "$phc --pretty-print $subject 2>&1 | $phc --pretty-print";

		$async->final = "two_command_finish";

		$async->start ();
	}
}

?>
