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

	function allow_failure ()
	{
		return false;
	}

	function end_timer ()
	{
		// do nothing - call the parent function in run_test instead
	}

	function run_test ($subject)
	{
		// run first command
		$command1 = $this->get_command_line1 ($subject);
		list ($expected, $return1) = complete_exec($command1);
		$expected = $this->homogenize_output ($expected);

		// run second command
		$command2 = $this->get_command_line2 ($subject);
		list ($actual, $return2) = complete_exec($command2);
		$actual = $this->homogenize_output ($actual);

		parent::end_timer($subject); // the diff can take a long time
		if ($actual !== $expected or 
				(!$this->allow_failure () and ($return1 != 0 or $return2 != 0)))
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
