<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * 
 */

function get_pass_list ()
{
	list ($out, $err, $exit) = complete_exec ("src/phc --list-passes");
	assert ($out and $err === "" and $exit === 0);

	preg_match_all ("/([a-zA-Z-_0-9]+)\s+\((enabled|disabled)\s+- (AST|HIR|MIR|LIR)\)\s+.+/", $out, $matches);

	return $matches[1];
}


class CompareBackwards extends AsyncTest
{
	function __construct ($last_pass, $dump = "dump", $dependency = "BasicParseTest")
	{
		$this->last_pass = $last_pass;
		$this->name = "cb_$last_pass";
		if ($dependency != "BasicParseTest")
			$dependency = "cb_$dependency";

		// this might be udump
		$this->dump = $dump;

		$this->dependencies = array ($dependency);
		parent::__construct ();

	}

	function get_name ()
	{
		return $this->name;
	}

	function get_test_subjects ()
	{
		return get_interpretable_scripts ();
	}

	function run_test ($subject)
	{
		global $phc;
		$bundle = new AsyncBundle ($this, $subject);

		$bundle->commands[0]		= get_php_command_line ($subject);
		$bundle->out_handlers[0] = "homogenize_output";
		$bundle->callbacks[0] = NULL;

		$commands = array ();
		foreach (get_pass_list () as $pass)
		{
			array_unshift ($commands, $this->get_command_line ($subject, $this->dump, $pass));
			if ($this->last_pass == $pass)
				break;
		}

		// A slightly different approach here. We add all the passes. As
		// soon as once succeeds, we pass the test. If none succeeds, the
		// fail.
		foreach ($commands as $command)
		{
			$bundle->commands[]	= $command;
			$bundle->out_handlers[] = "homogenize_output";
			$bundle->callbacks[] = "check_output";
		}

		$bundle->final = "finish";

		$bundle->start ();

	}

	function check_output ($out, $err, $exit, $bundle)
	{
		if ($bundle->outs[0] === $out
			&& $bundle->errs[0] === $err
			&& $bundle->exits[0] === $exit)
		{
			// correct
			if ($bundle->state == 1)
			{
				// right first time
				$this->mark_success ($bundle->subject);
			}
			else
			{
				// the pass which succeeded isnt the last pass
				$this->mark_failure ("Latest pass fails", $bundle);
			}
			return false; // dont process again
		}
		return true; // keep processing
	}


	function get_command_line ($subject, $dump, $pass_name)
	{
		global $phc;
		$pipe_command = get_php_command_line ($subject, "pipe");
		return "$phc --no-hash-bang --$dump=$pass_name $subject | $pipe_command";
	}

	function finish ($bundle)
	{
		$this->mark_failure ("Every pass fails", $bundle);
	}

	function homogenize_output ($output)
	{
		return homogenize_all ($output);
	}


}
