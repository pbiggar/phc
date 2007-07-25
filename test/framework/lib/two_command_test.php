<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compare the output of two command lines
 */
abstract class TwoCommandTest extends Test
{
	abstract function get_command_line1 ($subject);
	abstract function get_command_line2 ($subject);

	// exit true if we allow the test1 or test2 to exit a non-zero
	// exit code. If true, scripts with minor errors, which we intend
	// to _kinda_ replicate, are allowed.
	function allow_failure_exit_code ()
	{
		return false;
	}

	function end_timer ()
	{
		// does nothing. The timer is manually ended in run_test
	}

	function run_test ($subject)
	{
		$command1 = $this->get_command_line1 ($subject);
		$command2 = $this->get_command_line2 ($subject);
		list ($out1, $err1, $exit1) = complete_exec($command1);
		list ($out2, $err2, $exit2) = complete_exec($command2);
		$out1 = $this->homogenize_output ($out1);
		$out2 = $this->homogenize_output ($out2);

		parent::end_timer($subject); // the diff can take a long time
		if ($out1 !== $out2 or 
				$err1 !== $err2 or
				(!$this->allow_failure_exit_code () and ($exit1 != 0 or $exit2 != 0)))
		{
			$output = diff ($out1, $out2);
			$this->mark_failure($subject, 
				array($command1, $command2),
				array($exit1, $exit2),
				$output,
				array ($err1, $err2));
		}
		else $this->mark_success ($subject);
	}
}
?>
