<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compare the output of two command lines
 */

require_once ("test.php");
abstract class TwoCommandTest extends Test
{
	abstract function get_command_line1 ($subject);
	abstract function get_command_line2 ($subject);

	function run_test ($subject)
	{
		$command1 = $this->get_command_line1 ($subject);
		$command2 = $this->get_command_line2 ($subject);
		list ($out1, $err1, $exit1) = complete_exec($command1);
		list ($out2, $err2, $exit2) = complete_exec($command2);
		$out1 = $this->homogenize_output ($out1);
		$out2 = $this->homogenize_output ($out2);

		if ($out1 !== $out2 or 
				$err1 !== $err2 or
				$exit1 !== $exit2)
		{
			$output = diff ($out1, $out2);
			$this->mark_failure($subject, 
				array($command1, $command2),
				$output,
				array ($err1, $err2),
				array($exit1, $exit2),
				"Outputs or exit codes differ");
		}
		else $this->mark_success ($subject);
	}
}
?>
