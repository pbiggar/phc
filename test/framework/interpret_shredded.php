<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test an unparsed script interprets the same as the original after running
 * the shredder, using php command line.
 */
array_push($tests, new InterpretShredded ());
class InterpretShredded extends CompareWithPHP
{
	function allow_failure_exit_code ()
	{
		return true;
	}

	function get_command_line ($subject)
	{
		global $phc;
		return "$phc --run-shredder --pretty-print $subject 2>&1";
	}
}
?>
