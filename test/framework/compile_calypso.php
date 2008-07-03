<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Run the script through calypso and back, and test the output.
 */

require_once ("lib/async_test.php");

class CompileCalypso extends AsyncTest
{
	function get_dependent_test_names ()
	{
		return array ("CompiledVsInterpreted");
	}

	function get_test_subjects ()
	{
		return get_interpretable_scripts ();
	}

	function finish ($async)
	{
		if ($async->outs[0] !== $async->outs[7]
			or $async->errs[0] !== $async->errs[7]
			or $async->exits[0] !== $async->exits[7])
		{
			$output = diff ($async->outs[0], $async->outs[7]);
			$async->outs = $output;
			$this->async_failure ("Outputs dont match PHP outputs", $async);
		}
		else
		{
			$this->async_success ($async);
		}

	}

	function combine_xml ($x, $async)
	{
		$input = $async->outs[5];

		if ($input == "")
		{
			$this->async_failure ("No XML output", $async);
			return false;
		}

		// each Method starts with \"<MIR:Method>\n and ends with </MIR:Method>\n\"
		$input = preg_replace ("!^\"<MIR:Method>$!sm", "<MIR:Method>", $input);
		$input = preg_replace ("!^</MIR:Method>\n\"\n$!sm", "</MIR:Method>", $input);


		// combine them with header and footer
		$header = 
			  "<?xml version=\"1.0\"?>\n"
			. "<MIR:PHP_script xmlns:MIR=\"http://www.phpcompiler.org/phc-1.1\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
			. "<attrs>\n"
			. "<attr key=\"phc.filename\"><string>".$async->subject."</string></attr>\n"
			. "</attrs>\n"
			. "<MIR:Statement_list>";
		$footer = "</MIR:Statement_list>\n</MIR:PHP_script>\n";

		$combined_xml = "$header\n$input\n$footer";

		$async->ins[6] = $combined_xml;
	}

	function check_calypso (&$out, $async)
	{
		if (preg_match ("/^ERROR: .*/m", $out, $matches))
		{
			$this->async_failure ("Error in pass: $matches[0]", $async);
			return false;
		}

		if (preg_match ("/^WARNING: .*/m", $out, $matches))
		{
			$this->async_failure ("Warning in pass: $matches[0]", $async);
			return false;
		}

		return $out;
	}

	function homogenize_output ($string)
	{
		$string = homogenize_filenames_and_line_numbers ($string);
		$string = homogenize_reference_count ($string);
		return $string;
	}

	function get_php_command ($subject)
	{
		return get_php_command_line ($subject);
	}

	function run_test ($subject)
	{
		global $phc;
		// TODO this should all be moved into phc.
		$async = new AsyncBundle ($this, $subject);

		// Can't mess with the db names, so use separate logic dirs for each
		$logic_dir = wd_name ("${subject}_logic");
		mkdir ($logic_dir);
		$clpa = "3rdparty/clpa/bin/clpa --logic $logic_dir";

		$async->commands[0] = $this->get_php_command ($subject);
		$async->out_handlers[0] = "homogenize_output";

		# Unparsing into a .clp file
		$clp_file = wd_name ("$subject.clp");
		$async->commands[1] = "$phc --disable=dce --sdump=clar $subject > $clp_file";
		$async->exit_handlers[1] = "fail_on_output";

		# Read the .clp file into the mir DB
		$async->commands[2] = "$clpa --debug parse_warnings $clp_file";
		$async->exit_handlers[2] = "fail_on_output";

		# Split the program into functions, and create CFGs in the cfg DB
		$async->commands[3] = "$clpa src/analyse/do_cfg.clp";
		$async->exit_handlers[3] = "fail_on_output";
		$async->out_handlers[3] = "check_calypso";

		# Do optimizations; put the results in the optimized DB
		$async->commands[4] = "$clpa src/analyse/do_optimize.clp";
		$async->exit_handlers[4] = "fail_on_output";
		$async->out_handlers[4] = "check_calypso";

		# Unparse the optimized DB into XML
		$async->commands[5] = "$clpa src/analyse/xml_unparser.clp";
		$async->exit_handlers[5] = "fail_on_output";
		$async->out_handlers[5] = "combine_xml";

		# Read in the XML and compile
		$exe_name = wd_name ("$subject.out." . $this->get_name ());
		$async->commands[6] = "$phc --read-xml=pst -c -o $exe_name";
		$async->out_handlers[6] = "fail_on_output";
		$async->err_handlers[6] = "fail_on_output";

		$async->commands[7] = "./$exe_name";
		$async->out_handlers[7] = "homogenize_output";

		$async->final = "finish";

		$async->start ();
	}
}
array_push($tests, new CompileCalypso());

?>
