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
		$bundle->commands[0]		= $this->get_command_line (NULL, $last_pass, $subject);


		// Construct a command line which pipes the xml output of one pass into the XML input of the next pass.
		$long_command = "";
		$prev_pass = NULL;
		$concatenator = "";
		foreach (get_pass_list () as $pass)
		{
			$long_command .= $concatenator . $this->get_command_line ($prev_pass, $pass, $subject);
			
			$subject = NULL; // we dont need it after the first one
			$concatenator = " | "; // we want to pipe  the commands together
			$prev_pass = $pass;
		}

		$bundle->commands[1] = $long_command;

		$bundle->final = "finish";

		$bundle->start ();

	}

	function get_command_line ($in_pass, $out_pass, $subject)
	{
		global $phc;
		$command = "$phc --no-hash-bang --xdump=$out_pass";

		if (is_string ($subject)) $command .= " $subject";
		if (is_string ($in_pass)) $command .= " --read-xml=$in_pass";

		return $command;
	}

	function finish ($bundle)
	{
		$expected_final_xml = $bundle->outs[0];
		$final_xml = $bundle->outs[1];
		if ($final_xml === $expected_final_xml)
			$this->mark_success ($bundle->subject);
		else
			$this->mark_failure ("Final output doesnt match expected", $bundle);
	}

}
