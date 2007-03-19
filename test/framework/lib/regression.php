<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */
require_once ("support_file_test.php");

abstract class RegressionTest extends SupportFileTest
{
	abstract function get_command_line ($subject);

	function run_test ($subject)
	{
		$regression_file = $this->get_support_filename ($subject);

		// read the expected output
		if (file_exists($regression_file))
		{
			$command = $this->get_command_line ($subject);
			$command .= " | diff -u $regression_file - 2>&1";
			list ($diff, $return_value) = complete_exec($command);

			// compare to the existing files
			if ($diff)
			{
				$this->mark_failure ($subject, $command, $return_value, $diff);
			}
			else
			{
				$this->mark_success ($subject);
			}
		}
		else
		{
			$this->mark_skipped ($subject, "No regression support file at $regression_file");
		}

	}

	function generate_support_files ()
	{
		if (!$this->check_prerequisites ())
		{
			$this->mark_skipped ("All", "Prerequisites failed");
			return false;
		}

		$files = $this->get_test_subjects ();
		$this->ready_progress_bar (count ($files));

		foreach ($files as $subject)
		{
			if (!$this->check_test_prerequisites ($subject))
			{
				$this->mark_skipped ($subject, "Test prerequsites failed");
			}
			else
			{
				$this->generate_support_file ($subject);
			}
		}

		$this->finish_test ();
	}

	function generate_support_file ($subject)
	{
		// get the output
		$command = $this->get_command_line ($subject);
		list ($output, $return_value) = complete_exec($command);

		if ($return_value == 0)
		{
			$this->write_support_file ($output, $subject);
			$this->mark_success ($subject);
		}
		else
		{
			$this->mark_failure ($subject, $command, $return_value, $output);
		}
	}

}

?>
