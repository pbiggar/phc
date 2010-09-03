<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that all scripts parse, without error, warning or exit code.
 */

require_once ("lib/async_test.php");

class BasicRaisedOptimizeTest extends AsyncTest
{
	function get_test_subjects ()
	{
		return get_all_scripts();
	}

	function run_test ($subject)
	{
		$bundle = new AsyncBundle ($this, $subject);

		$bundle->commands[0] = get_phc_command_line ($subject)." --run=plugins/tests/raise_globals.la -O1";
		$bundle->final = "finish";

		$bundle->start ();
	}

	function finish ($bundle)
	{
		if ($bundle->errs[0])
			$this->async_failure ("Stderr not clear", $bundle);
		else if ($bundle->outs[0])
			$this->async_failure ("Stdout not clear", $bundle);
		else if ($bundle->exits[0])
			$this->async_failure ("exit code not clear", $bundle);
		else
			$this->async_success ($bundle);
	}

	// No test that expects an exit code, stdout or stderr should get this
	// far. It should be removed by Annotated test.
	function get_dependent_test_names ()
	{
		return array ("cb_mir");
	}
}
array_push($tests, new BasicRaisedOptimizeTest());

?>
