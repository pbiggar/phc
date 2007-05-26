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
class BasicParseTest extends SupportFileTest
{
	function get_test_subjects ()
	{
		return get_all_scripts();
	}

	function run_test ($subject)
	{
		global $phc;

		// check if we're expecting output
		$filename = $this->get_support_filename ($subject);
		if (file_exists ($filename))
		{
			// read the expectd output from the file
			$lines = file_get_contents ($filename);

			$check = preg_match ("/^return: (\d+)\noutput: (.*)$/s", $lines, $array);
			phc_assert ($check == 1, "wrong number of matches ($check)");

			list ($out1, $exit1, $err1) = $array;
			phc_assert ($out1 == $lines, "should match whole string");
			phc_assert ($exit1 != 0, "wrong return value");
			phc_assert ($err1 != "", "bad error");
		}
		else
		{
			$err1 = "";
			$exit1 = 0;
			$out1 = "";
		}

		// we now have expected output
		$command = $this->get_command_line ($subject);
		list ($out2, $err2, $exit2) = complete_exec ($command);

		if ($exit1 == $exit2 and $err1 == $err2 or $out1 or $out2)
		{
			$this->mark_success ($subject);
		}
		else
		{
			$this->mark_failure ($subject, $command, array($exit1, $exit2), array ($out1, $out2), array ($err1, $err2));
		}
	}

	function get_command_line ($subject)
	{
		global $phc;
		return "$phc $subject";
	}

	function get_support_filename ($subject)
	{
		global $support_dir;
		$script_name = adjusted_name ($subject);
		return "$support_dir/basic_parse_tests/$script_name.log";
	}

	function generate_support_file ($subject)
	{
		// get the output
		$command = $this->get_command_line ($subject);
		list ($out, $err, $exit) = complete_exec($command);

		$file_output = "return: $exit\noutput: $err";

		if ($exit == 0)
		{
			$this->mark_skipped ($subject, "No generated results to be stored");
		}
		else
		{
			$this->write_support_file ($file_output, $subject);
			$this->mark_success ($subject);
		}
	}
}


?>
