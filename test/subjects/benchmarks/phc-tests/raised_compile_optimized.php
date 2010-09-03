<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compare compiled output to interpreted. But first, move the statements from
 * __MAIN__ into a different method, so that they arent anything special. This
 * allows us test more unusual constructs, as most of our tests just have a
 * __MAIN__ method.
 */


array_push($tests, new RaisedCompileOptimized ());
class RaisedCompileOptimized extends CompiledVsInterpreted
{

	function get_dependent_test_names ()
	{
		return array ("CompiledVsInterpreted", "InterpretRaisedOptimized");
	}

	function get_phc_command ($subject, $exe_name)
	{
		global $phc;
		return get_phc_command_line ($subject) . "-c --run=plugins/tests/raise_globals.la -O1 -o $exe_name";
	}

	function get_php_command ($subject)
	{
		global $phc;
		// Use codegen so we can add -O3 to the command line, and get the failing case.
		return "$phc --run=plugins/tests/raise_globals.la --convert-uppered --dump=codegen $subject | ". get_php_command_line ($subject, "pipe");
	}
}

?>
