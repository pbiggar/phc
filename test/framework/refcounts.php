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
	function run_test ($subject)
	{
		global $gcc, $phc, $php;
		$dir_name = dirname($subject);

		// get the output from the interpreter for the file
		$command1 = "$phc --run plugins/tools/debug_zval.la $subject | $php";
		list ($out1, $err1, $exit1) = complete_exec($command1);
		$out1 = $this->homogenize_output ($out1); 

		// first check that phc returns 0
		$phc_command1 = "$phc --generate-c $subject";
		list ($phc_out1, $phc_err1, $phc_exit1) = complete_exec($phc_command1);

		if ($phc_exit1 != 0)
		{
			$this->mark_skipped ($subject, "Generate C has non-zero status"); 
			return;
		}

		# Blank output wasnt being picked up
		if (count (split ("\n", $phc_out1)) < 170)
		{
			$this->mark_failure ($subject, $phc_command1, $phc_exit1, $phc_out1, $phc_err1); 
			return;
		}

		// compile
		// we expect output from the plugin, i think
		$phc_command2 = "$phc -c --run plugins/tools/debug_zval.la $subject";
		list ($phc_out2, $phc_err2, $phc_exit2) = complete_exec($phc_command2);
		if ($phc_exit2 or $phc_err2)
		{
			$this->mark_failure ($subject,
				array($command1, $phc_command1, $phc_command2), 
				array($exit1, $phc_exit1, $phc_exit2),
				$phc_out2,
				array($err1, $phc_err1, $phc_err2));
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
				array($command1, $phc_command1, $phc_command2, $command2),
				array($exit1, $phc_exit1, $phc_exit2, $exit2),
				$output,
				array ($err1, $phc_err1, $phc_err2, $err2));
		}
		else
		{
			$this->mark_success ($subject);
		}
	}
}

?>
