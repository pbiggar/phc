<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that all scripts parse, with expected errors taken into account.
 */

// This is a regression test to check that all the scripts parse as we
// expect them to
require_once ("lib/async_test.php");
class BasicParseTest extends AsyncTest
{
	function get_test_subjects ()
	{
		return get_all_scripts();
	}

	function run_test ($subject)
	{
		global $phc;
		$async = new Async_steps ($this, $subject);

		$async->commands[0] = "$phc $subject";
		$async->final = "finish";
		$async->start ();
	}

	function finish ($async)
	{
		$subject = $async->subject;
		// check for expected errors and warnings
		$this->get_expected_warnings ($subject, $warnings);

		// exit codes mean errors, and vice-versa
		// TODO reinstate this
//		if ($async->exits[0] xor ($errors[0]))
//		{
//			$failure = "No exit code for expected error: $error";
//		}

		// convert output into a list of actual warnings and errors
		$actual_output = split ("\n", $async->errs[0]);
		$actual_output = preg_grep ("/./", $actual_output); 
		$actual_output = array_diff ($actual_output, array ("Note that line numbers are inaccurate, and will be fixed in a later release"));
		$actual_output = preg_replace ("/[^:]*:\d+:\s/", "", $actual_output);

		// Check that the results are not different
		$diff = array_diff ($actual_output, $warnings);
		if (count ($diff))
		{
			$failures = "";
			foreach ($diff as $warning)
			{
				if (in_array ($warning, $actual_output))
				{
					$failures .= "Unexpected warning found: $warning\n";
				}
				else
				{
					$failures .= "Expected warning not found: $warning\n";
				}
			}
			$async->outs[0] .= $failures;
			$this->mark_failure ($subject, $async);
			return;
		}

		if ($async->errs[0])
		{
			$this->expected_failure_count++;
			write_dependencies ($this->get_name (), $subject, false);
		}
		$this->mark_success ($subject);

	}

	function get_expected_warnings ($subject, &$warnings)
	{
		$out = file_get_contents ($subject);

		// match the errors
		$lines = split ("\n", $out);
		$pregs = array ("/#(.*)$/", "/\/\/(.*)$/", "/\/\*(.*)\*\//");
		$error = false;
		$warnings = array ();
		foreach ($lines as $line)
		{
			// get single line comments
			foreach ($pregs as $preg)
			{
				if (preg_match ("$preg", $line, $line_match))
				{
					// extract the error/warning from the comment
					if (preg_match ("/\s*\{\s*(\S.*\S)\s*\}\s*$/", $line_match[1], $comment_match))
					{
						$warnings[] = $comment_match[1];
					}
				}
			}
		}
	}


	# we override tests run in order to add a line at the end
	function run ()
	{
		parent::run ();
		$num_skipped = $this->expected_failure_count;
		echo "\n($num_skipped expected errors)\n";
	}
}
array_push($tests, new BasicParseTest());

?>
