<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test an unparsed script interprets the same as the original, using php
 * command line and phc --compile-time-includes.
 */

array_push($tests, new CompileTimeInclude ());
class CompileTimeInclude extends CompareWithPHP
{
	function get_test_subjects ()
	{
		return get_includable_scripts ();
	}

	function get_command_line ($subject)
	{
		global $phc;
		return "$phc --pretty-print --compile-time-includes $subject 2>&1 "
				. " | grep -v \"^[[:space:]]\\+include\" 2>&1"
				. " | grep -v \"^[[:space:]]\\+require\" 2>&1";
	}
}

?>
