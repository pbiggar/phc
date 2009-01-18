<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compares phc's line numbers with the script they came from
 */

#array_push($tests, new LineNumbersTest ()); # disable
class LineNumbersTest extends Test
{
	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	function run_test ($subject)
	{
		global $phc, $plugin_dir;

		//print "testing script $subject\n";
		$command = "$phc --run $plugin_dir/tests/line_numbers.la $subject";
		list ($out, $err, $exit) = complete_exec($command);

		if (strlen($out) == 0)
		{
			$this->mark_skipped ();
		}
		else
		{
			//  we'll need to read the file
			$contents = file($subject);

			$ok = true;
			$test_output = "";

			// TODO convert both the token and the line into an equivalent format
			// (note that toekns are pre-escaped, and that you need to look at
			// things like \100 and \x40

			// The output is in the form "token:line_number--!!--!!--".  Newlines,
			// if they are there, are part of the token. This is to avoid
			// confusion over newlines in regex.
			$lines = explode("--!!--!!--", rtrim($out));

			foreach($lines as $line)
			{
				if ($line == "") continue; # skip blank lines

				$match = preg_match("/^(.*):(\d+)$/ms", $line, $matches);
				$token = $matches[1];
				$line_number = $matches[2];
				//print "trying to match '$line'\n";
				//print "matched $token on $line_number\n";

				// our plugin should only print out things that can be non-zero
				if ($line_number == 0 or !$match or !isset($token) or !isset($line_number))
				{
					$error = "Got line 0 for '$token'\n";
					$test_output .= $error;
					$ok = false;
					continue;
				}

				// get the line from the file
				if (count($contents) <= $line_number-1)
				{
					$file_size = count ($contents);
					$error = "Expected (line $line_number): '$token'\nOnly $file_size lines\n";
					$test_output .= $error;
					$ok = false;
				}
				else
				{
					$actual_line = $contents[$line_number-1]; # arrays index from 0, but phc uses 1

					if (@strpos($actual_line, $token) !== False)
					{
						//				print "Found $token in $actual_line\n";
					}
					else
					{
						$error = "Expected (line $line_number): '$token'\nActual line:'$actual_line'\n";
						//					print $error;
						$test_output .= $error;
						$ok = false;
					}
				}
			}

			if ($ok) $this->mark_success ($subject);
			else $this->mark_failure ($subject, $command, 0, $test_output);
		}
	}
}
?>
