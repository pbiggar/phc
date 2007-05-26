<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test an unparsed script interprets the same as the original, using php
 * command line and phc --compile-time-includes.
 */

$tests[] = new CompileTimeInclude ();
class CompileTimeInclude extends CompareWithPHP
{
	function get_test_subjects ()
	{
		return get_includable_scripts ();
	}

	function get_dependent_test_names ()
	{
		return array ("InterpretUnparsed");
	}

	function __construct ()
	{
		parent::__construct ("CompileTimeInclude", "--pretty-print --compile-time-includes");
	}

	function get_command_line2 ($subject)
	{
		$command = parent::get_command_line2 ($subject);
		return $command
				. " | grep -v \"^[[:space:]]\\+include\" 2>&1"
				. " | grep -v \"^[[:space:]]\\+require\" 2>&1";
	}
}
?>
