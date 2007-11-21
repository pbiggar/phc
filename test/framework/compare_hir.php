<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test the output of a compiled script against php's output for the same script. 
 */

require_once ("lib/async_test.php");

class CompareHIR extends AsyncTest
{
	function get_dependent_test_names ()
	{
		return array ("Interpret_hir_as_ast");
	}

	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	function finish ($async)
	{
		if ($async->outs[0] !== $async->outs[1])
		{
			$output = diff ($async->outs[0], $async->outs[1]);
			$async->outs[] = $output;
			$this->mark_failure ("Unparsed files dont match", $async);
		}
		else
		{
			$this->mark_success ($async->subject);
		}

	}

	function run_test ($subject)
	{
		global $phc;
		$async = new AsyncBundle ($this, $subject);

		$async->commands[0] = "$phc --dump=hir_as_ast $subject";
		$async->exit_handlers[0] = "fail_on_output";
		$async->err_handlers[0] = "fail_on_output";

		$async->commands[1] = "$phc --dump=hir $subject";
		$async->exit_handlers[1] = "fail_on_output";
		$async->err_handlers[1] = "fail_on_output";

		$async->final = "finish";

		$async->start ();
	}
}
array_push($tests, new CompareHIR ());

?>
