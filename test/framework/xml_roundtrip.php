<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check the XML output of a script is the same as if it was parsed from XML
 */

array_push($tests, new XML_roundtrip());
class XML_roundtrip extends AsyncTest
{
	function get_dependent_test_names ()
	{
		return array ("BasicParseTest");
	}

	function check_prerequisites ()
	{
		global $xerces_compiled_in;
		return parent::check_prerequisites () and
			$xerces_compiled_in != 'no';
	}
	
	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	// Dump after the last pass. Then dump after every pass, and reparse
	// it. Check that the final dump is that same.
	function run_test ($subject)
	{
		global $phc;
		$bundle = new AsyncBundle ($this, $subject);

		$passes = get_pass_list ();
		$last_pass = $passes [count ($passes) - 1];


		# Get the output going straight though the compiler
		$bundle->commands[0]	= $this->get_command_line (NULL, $last_pass, $subject);
		$bundle->commands[1] = $this->get_long_command_line ($subject, $last_pass);

		$bundle->final = "finish";

		$bundle->start ();

	}

	// Construct a command line which pipes the xml output of one pass into the
	// XML input of the next pass.
	function get_long_command_line ($subject, $last_pass)
	{
		$long_command = "";
		$prev_pass = NULL;
		$concatenator = "";
		foreach (get_pass_list () as $pass)
		{
			$long_command .= $concatenator . $this->get_command_line ($prev_pass, $pass, $subject);
			
			$subject = NULL; // we dont need it after the first one
			$concatenator = " | "; // we want to pipe  the commands together
			$prev_pass = $pass;

			// dont always give the full list
			if ($pass == $last_pass)
				break;
		}
		return $long_command;
	}


	function get_command_line ($in_pass, $out_pass, $subject)
	{
		global $phc;
		$command = "$phc --no-hash-bang";

		if (is_string ($subject)) $command .= " $subject";
		if (is_string ($in_pass)) $command .= " --read-xml=$in_pass";
		$command .= " --xdump=$out_pass";

		return $command;
	}

	function finish ($bundle)
	{
		global $opt_debug;
		$expected_final_xml = $bundle->outs[0];
		$final_xml = $bundle->outs[1];
		if ($final_xml === $expected_final_xml)
			$this->async_success ($bundle);
		else
		{
			$pass_string = "";
			if ($opt_debug) // this will take a while
			{
				$last_pass = end (get_pass_list ());
				// find the failing part
				foreach (get_pass_list() as $pass)
				{
					$command1 = $this->get_command_line (NULL, $pass, $bundle->subject);
					$command2 = $this->get_long_command_line ($bundle->subject, $pass);
					if (($result1 = complete_exec ($command1)) !== ($result2 = complete_exec ($command2)))
					{
						$bundle->commands[2] = $command1;
						list ($bundle->outs[2], $bundle->errs[2], $bundle->exits[2]) = $result1;

						$bundle->commands[3] = $command2;
						list ($bundle->outs[3], $bundle->errs[3], $bundle->exits[3]) = $result2;

						$pass_string = " in pass '$pass'";
						break;
					}
				}
			}

			$this->async_failure ("Final output doesnt match expected$pass_string", $bundle);
		}
	}

}
