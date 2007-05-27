<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that all scripts parse, with expected errors taken into account.
 */

// This is a regression test to check that all the scripts parse as we expect
// them to. It now uses support_files, and not the embedded values in the
// scripts.

array_push($tests, new BasicParseTest());
class BasicParseTest extends Test
{
	function get_test_subjects ()
	{
		return get_all_scripts();
	}

	function run_test ($subject)
	{
		global $phc;

		// we now have expected output
		$command = $this->get_command_line ($subject);
		list ($out, $err, $exit, $failure) = run_command ($command, $subject);

		if ($failure === "")
		{
			$this->mark_success ($subject);
			// if there was a warning or error, dont say this is successful.
			// TODO this means we cant test warnings that are only generated
			// due to non-default passes, which needs to be fixed (later)
			if ($err)
			{
				global $successes;
				unset($successes[$this->get_name ()][$subject]);
			}
		}
		else
		{
			$this->mark_failure ($subject, $command, $exit, array ($out, $failure), $err);
		}
	}

	function get_command_line ($subject)
	{
		global $phc;
		return "$phc $subject";
	}

}


?>
