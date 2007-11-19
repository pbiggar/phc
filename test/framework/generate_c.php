<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Runs tests with --generate-c. This creates a dependency for any
 * tests which generate code, and should save them from having to
 * run the generate-c step themselves. 
 */


array_push($tests, new Generate_C ());
class Generate_C extends Test
{
	function get_dependent_test_names ()
	{
		return array ("Interpret_shred");
	}

	function get_test_subjects ()
	{
		return get_interpretable_scripts ();
	}

	function run_test ($subject)
	{
		global $gcc, $phc, $php;
		$dir_name = dirname($subject);

		// first check that phc returns 0
		$phc_command = "$phc --generate-c $subject";
		list ($phc_out, $phc_err, $phc_exit) = complete_exec($phc_command);

		if ($phc_exit or $phc_err)
		{
			$this->mark_failure ($subject,
				$phc_command, 
				$phc_out,
				$phc_err,
				$phc_exit,
				"exit or error set");
		}
		# Blank output wasnt being picked up
		else if (count (split ("\n", $phc_out)) < 170)
		{
			$this->mark_failure ($subject, $phc_command, $phc_exit, $phc_out, $phc_err, "output is too short"); 
		}
		else
		{
			$this->mark_success ($subject);
		}
	}
}

?>
