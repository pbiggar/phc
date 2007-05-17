<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test a canonically unparsed script interprets the same as the original,
 * using php command line.
 */

array_push($tests, new InterpretCanonicalUnparsed ());
class InterpretCanonicalUnparsed extends CompareWithPHP
{

	function allow_failure_exit_code ()
	{
		return true;
	}

	function check_prerequisites ()
	{
		return check_for_plugin ("tests/canonical_unparser");
	}

	function get_command_line ($subject)
	{
		global $phc, $php;
		return "$phc --run plugins/tests/canonical_unparser.la $subject 2>&1";
	}
}
?>
