<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Runs tests with --generate-c. This creates a dependency for any
 * tests which generate code, and should save them from having to
 * run the generate-c step themselves. 
 */

require_once ("lib/async_test.php");

array_push($tests, new Generate_C ());
class Generate_C extends AsyncTest
{
	function get_dependent_test_names ()
	{
		return array ("cb_hir");
	}

	function get_test_subjects ()
	{
		return get_interpretable_scripts ();
	}

	function run_test ($subject)
	{
		global $phc;
		$bundle = new AsyncBundle ($this, $subject);

		$bundle->commands[0] = get_phc_command_line ($subject). " --generate-c";
		$bundle->final = "finish";

		$bundle->start ();
	}

	function finish ($bundle)
	{
		if ($bundle->errs[0])
			$this->async_failure ("Stderr not clear", $bundle);
		else if ($bundle->exits[0])
			$this->async_failure ("exit code not clear", $bundle);
		else if (strlen ($bundle->outs[0]) < 1428)
			$this->async_failure ("output is too short", $bundle);
		else
			$this->async_success ($bundle);
	}
}

?>
