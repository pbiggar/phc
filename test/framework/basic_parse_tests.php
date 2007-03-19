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

			list ($_, $expected_return_value, $expected_error) = $array;
			phc_assert ($_ == $lines, "should match whole string");
			phc_assert ($expected_return_value != 0, "wrong return value");
			phc_assert ($expected_error != "", "bad error");
		}
		else
		{
			$expected_error = "";
			$expected_return_value = 0;
		}

		// we now have expected output
		$command = $this->get_command_line ($subject);
		list ($error, $return_value) = complete_exec($command);

		if ($return_value == $expected_return_value and $error == $expected_error)
		{
			$this->mark_success ($subject);
		}
		else
		{
			$this->mark_failure ($subject, $command, "$return_value (expected $expected_return_value)", "'$error'\nExpected:\n'$expected_error'");
		}
	}

	function get_command_line ($subject)
	{
		global $phc;
		return "$phc $subject 2>&1";
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
		list ($output, $return_value) = complete_exec($command);

		$file_output = "return: $return_value\noutput: $output";

		if ($return_value == 0)
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
