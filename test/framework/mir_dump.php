<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * We cant test that the MIR unparser works, but we can test that it doesn't
 * segfault (which can happen due to MIR_to_AST having bugs).
 */


array_push($tests, new MIR_Dump());
class MIR_Dump extends AsyncTest
{
	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	function get_dependent_test_names ()
	{
		return array ("cb_mir");
	}

	function run_test ($subject)
	{
		global $phc;
		$async = new AsyncBundle ($this, $subject);

		$async->commands[0]		= "$phc $subject --dump=mir";
		$async->err_handlers[0] = "fail_on_output";

		$async->final = "async_success";
		$async->start ();
	}
}
?>
