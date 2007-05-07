<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test the output of a compiled script against php's output for the same script. 
 */


array_push($tests, new CompiledVsInterpreted ());
class CompiledVsInterpreted extends Test
{
	function check_prerequisites ()
	{
		global $gcc, $libphp;
#		if (!check_for_program ($gcc)) return false;
		if (!check_for_program ("$libphp/libphp5.so")) return false;
		return true;
	}

	function get_test_subjects ()
	{
		return get_interpretable_scripts ();
	}

	function run_test ($subject)
	{
		global $gcc, $phc, $libphp, $php;
		$dir_name = dirname($subject);

		// get the output from the interpreter for the file
		$command1 = "$php -d include_path=$dir_name:./ $subject 2>&1";
		list ($expected, $return1) = complete_exec($command1);
		$expected = $this->homogenize_output ($expected); 

		// first check that phc returns 0
		$phc_command1 = "$phc --generate-c $subject 2>&1 >/dev/null";
		list ($phc_output1, $phc_return1) = complete_exec($phc_command1);
		if ($phc_return1 != 0)
		{
			//$this->mark_failure($subject, $phc_command1, $phc_return1, $phc_output1);
			$this->mark_skipped($subject, $phc_output1); 
			return;
		}

		// generate C
		$phc_command2 = "$phc -c $subject 2>&1";
		list ($phc_output2, $phc_return2) = complete_exec($phc_command2);
		if ($phc_return2 != 0)
		{
			$this->mark_failure ($subject, $phc_command2, $phc_return2, $phc_output2);
			return;
		}

		// run the program
		$command2 = "LD_LIBRARY_PATH=$libphp:\$LD_LIBRARY_PATH ./a.out 2>&1";
		list ($actual, $return2) = complete_exec($command2);
		$actual = $this->homogenize_output ($actual); 

		if ($actual !== $expected or $return1 != 0 or $return2 != 0)
		{
			$output = diff ($expected, $actual);
			$this->mark_failure($subject, array($command1, $phc_command1, $phc_command2, $command2), array($return1, $phc_return1, $phc_return2, $return2), $output);
		}
		else
		{
			$this->mark_success ($subject);
		}
	}
}

?>
