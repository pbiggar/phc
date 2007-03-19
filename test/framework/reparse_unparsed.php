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
		return get_non_erroneous_scripts ();
	}

	function get_command_line1 ($subject)
	{
		global $phc;
		return "cat $subject | $phc --dump-ast-xml 2>&1";
	}

	function get_command_line2 ($subject)
	{
		global $phc;
		return "$phc --dump-php $subject 2>&1 | $phc --dump-ast-xml 2>&1";
	}

	function homogenize_output ($string)
	{
		return $this->homogenize_xml ($string);
	}

}

?>
