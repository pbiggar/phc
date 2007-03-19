<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test an unparsed script interprets the same as the original, using php
 * command line and phc --compile-time-includes.
 */

array_push($tests, new CompileTimeInclude ());
class CompileTimeInclude extends TwoCommandTest
{
	function get_test_subjects ()
	{
		return get_includable_scripts ();
	}

	function get_command_line1 ($subject)
	{
		global $phc, $php;
		$dir_name = dirname($subject);
		return "cat $subject | $php -d include_path=./:$dir_name 2>&1";
	}

	function get_command_line2 ($subject)
	{
		global $phc, $php;
		$dir_name = dirname($subject);
		return "$phc --dump-php --compile-time-includes $subject 2>&1 | grep -v \"^[[:space:]]\\+include\" 2>&1 | grep -v \"^[[:space:]]\\+require\" 2>&1 | $php -d include_path=$dir_name 2>&1";
	}

	function homogenize_output ($output)
	{
		return $this->homogenize_filenames ($output);
	}
}

?>
