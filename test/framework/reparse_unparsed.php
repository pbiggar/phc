<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that an unparsed script, when reparsed, has the same output.
 */

array_push($tests, new ReparseUnparsed ());
class ReparseUnparsed extends TwoCommandTest
{
	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	function get_dependent_test_names ()
	{
		return array ("InterpretUnparsed");
	}

	function get_command_line1 ($subject)
	{
		global $phc;
		return "cat $subject | $phc --pretty-print 2>&1";
	}

	function get_command_line2 ($subject)
	{
		global $phc;
		return "$phc --pretty-print $subject 2>&1 | $phc --pretty-print 2>&1";
	}

	function homogenize_output ($string)
	{
		// TODO ideally we would use the xml output, but there are problems there
//		return homogenize_xml ($string);
	}

}

?>
