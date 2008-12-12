<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Conduct a test which is compared to the output of the interpreter
 */

require_once ("async_test.php");


class CompareWithPHP extends AsyncTest
{
	function __construct ($name, $command_line, $dependecy)
	{
		$this->name = $name;
		$this->command_line = $command_line;
		$this->dependencies = array ($dependecy);
		parent::__construct ();
	}

	// TODO move the cache to AsyncTest
	public static $cache = array ();
	function get_test_subjects ()
	{
		return get_interpretable_scripts ();
	}

	// we intercept and wrap this to cache results
	function run_command ($command, $subject)
	{
		if ($command == $this->get_command_line1 ($subject))
		{
			if (isset (CompareWithPHP::$cache{$subject}))
			{
#				print "fetching cached results\n";
				return CompareWithPHP::$cache{$subject};
			}
			else
			{
#				print "running and caching\n";
				$results = parent::run_command ($command, $subject);
				CompareWithPHP::$cache{$subject} = $results;
#				var_dump (CompareWithPHP::$cache);
				return $results;
			}
		}
		else
		{
#			print "not command 1\n";
			return parent::run_command ($command, $subject);
		}
	}

	function get_command_line1 ($subject)
	{
		return get_php_command_line ($subject);
	}

	function get_command_line2 ($subject)
	{
		$command = $this->command_line;
		$pipe_command = get_php_command_line ($subject, "pipe");
		return get_phc_command_line ($subject) . " $command | $pipe_command";
	}

	function homogenize_output ($output, $bundle)
	{
		return homogenize_all ($output, $bundle->subject);
	}

	function get_name ()
	{
		return $this->name;
	}

	function run_test ($subject)
	{
		$async = new AsyncBundle ($this, $subject);

		$async->commands[0] = $this->get_command_line1 ($subject);
		$async->out_handlers[0] = "homogenize_output";

		$async->commands[1] = $this->get_command_line2 ($subject);
		$async->out_handlers[1] = "homogenize_output";

		$async->final = "two_command_finish";

		$async->start ();
	}
}

?>
