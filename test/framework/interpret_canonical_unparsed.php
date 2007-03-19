<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test a canonically unparsed script interprets the same as the original,
 * using php command line.
 */

array_push($tests, new InterpretCanonicalUnparsed ());
class InterpretCanonicalUnparsed extends TwoCommandTest
{
	function get_test_subjects ()
	{
		return get_interpretable_scripts ();
	}

	function allow_failure ()
	{
		return true;
	}

	function check_prerequisites ()
	{
		return check_for_plugin ("tests/canonical_unparser");
	}

	function get_command_line1 ($subject)
	{
		global $php;
		$dir_name = dirname($subject);
		return "cat $subject | $php -d include_path=$dir_name:./ 2>&1";
	}

	function get_command_line2 ($subject)
	{
		global $phc, $php;
		$dir_name = dirname($subject);
		return "$phc --run plugins/tests/canonical_unparser.la $subject 2>&1 | $php -d include_path=$dir_name:./ 2>&1";
	}

	function homogenize_output ($string)
	{
		return $this->homogenize_line_numbers ($string);
	}

}

?>
