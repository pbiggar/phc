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
			// if there was a warning or error, dont say this is
			// successful.
			if ($err)
			{
				$this->expected_failure_count++;
				write_dependencies ($this->get_name (), $subject, false);
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

	# we override tests run in order to add a line at the end
	function run ()
	{
		parent::run ();
		$num_skipped = $this->expected_failure_count;
		echo "($num_skipped expected errors)\n";
	}

}

?>
