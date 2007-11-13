<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */
require_once ("support_file_test.php");

class RegressionTest extends SupportFileTest
{
	// Note that the name is the support file directory 
	function RegressionTest ($name, $command_line_options, $support_file_suffix, $dependencies = array ())
	{
		$this->name = $name;
		$this->options = $command_line_options;
		$this->suffix = $support_file_suffix;
		$this->dependencies = $dependencies;
		parent::__construct ();
	}

	function get_dependent_test_names ()
	{
		return array ("BasicParseTest");
	}

	function get_name ()
	{
		return $this->name;
	}

	function get_support_filename ($subject)
	{
		global $support_dir;
		$script_name = adjusted_name($subject, 1);
		return "$support_dir/{$this->name}/$script_name.{$this->suffix}";
	}

	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	function get_command_line ($subject)
	{
		global $phc;
		return "$phc {$this->options} $subject";
	}

	function run_test ($subject)
	{
		$regression_file = $this->get_support_filename ($subject);

		// read the expected output
		if (file_exists($regression_file))
		{
			$command = $this->get_command_line ($subject);
			$command .= " | diff -u $regression_file -";
			list ($diff, $err, $exit) = complete_exec($command);

			// compare to the existing files
			if ($diff)
			{
				$this->mark_failure ($subject, $command, $diff, $err, $exit);
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
		list ($out, $err, $exit) = complete_exec($command);

		if ($exit == 0)
		{
			$this->write_support_file ($out, $subject);
			$this->mark_success ($subject);
		}
		else
		{
			$this->mark_skipped ($subject, "Non zero exit code ($exit)");
		}
	}

}

?>
