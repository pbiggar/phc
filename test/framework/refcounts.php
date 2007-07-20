<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Adds debug_zval_dump after each statement, then compared the outputs of the
 * compiled and interpreted code.
 */


array_push($tests, new Refcounts ());
class Refcounts extends CompiledVsInterpreted
{

	function get_dependent_test_names ()
	{
		return array ("Generate_C");
	}


	function run_test ($subject)
	{
		global $gcc, $phc, $php;
		$dir_name = dirname($subject);

		// get the output from the interpreter for the file
		$command1 = "$phc --run plugins/tools/debug_zval.la --udump=plugins/tools/debug_zval.la $subject | $php";
		list ($out1, $err1, $exit1) = complete_exec($command1);
		$out1 = $this->homogenize_output ($out1); 

		// compile
		// we expect output from the plugin, i think
		$phc_command = "$phc -c --run plugins/tools/debug_zval.la $subject";
		list ($phc_out, $phc_err, $phc_exit) = complete_exec($phc_command);
		if ($phc_exit or $phc_err)
		{
			$this->mark_failure ($subject,
				array($command1, $phc_command), 
				array($exit1, $phc_exit),
				$phc_out,
				array($err1, $phc_err));
			return;
		}

		// run the program
		$command2 = " ./a.out";
		list ($out2, $err2, $exit2) = complete_exec($command2);
		$out2 = $this->homogenize_output ($out2); 

		if ($out1 !== $out2 
			or $err1 !== $err2 
			or $exit1 !== $exit2) 
		{
			$output = diff ($out1, $out2);
			$this->mark_failure ($subject,
				array($command1, $phc_command, $command2),
				array($exit1, $phc_exit, $exit2),
				$output,
				array ($err1, $phc_err, $err2));
		}
		else
		{
			$this->mark_success ($subject);
		}
	}
}

?>
