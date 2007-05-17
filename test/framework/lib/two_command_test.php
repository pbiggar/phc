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

	// return true if we allow the test1 or test2 to return a non-zero exit
	// code. If true, scripts with minor errors, which we intend to _kinda_
	// replicate, are allowed.
	function allow_failure_exit_code ()
	{
		return false;
	}

	function run_command ($command, $subject)
	{
		// run first command
		list ($output, $return) = complete_exec($command);
		$output = $this->homogenize_output ($output);
		return array ($output, $return);
	}

	function end_timer ()
	{
		// does nothing. The timer is manually ended in run_test
	}

	function run_test ($subject)
	{
		$command1 = $this->get_command_line1 ($subject);
		$command2 = $this->get_command_line2 ($subject);
		list ($expected, $return1) = $this->run_command ($command1, $subject);
		list ($actual, $return2) = $this->run_command ($command2, $subject);

		parent::end_timer($subject); // the diff can take a long time
		if ($actual !== $expected or 
				(!$this->allow_failure_exit_code () and ($return1 != 0 or $return2 != 0)))
		{
			$output = diff ($expected, $actual);
			$this->mark_failure($subject, 
				array($command1, $command2),
				array($return1, $return2),
				$output);
		}
		else $this->mark_success ($subject);
	}
}
?>
