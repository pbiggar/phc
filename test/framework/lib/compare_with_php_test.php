<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Conduct a test which is compared to the output of the interpreter
 */

function get_php_command_line ($subject, $pipe = false)
{
	global $php;
	global $opt_long;

	if ($opt_long)
		$max_exe = 12;
	else
		$max_exe = 5;

	$dir_name = dirname($subject);
	if ($pipe) $subject = "";
	return "$php -d include_path=./:$dir_name -d max_execution_time=$max_exe $subject";
}


class CompareWithPHP extends TwoCommandTest
{
	function __construct ($name, $command_line, $dependecies = array ())
	{
		$this->name = $name;
		$this->command_line = $command_line;
		$this->dependencies = $dependecies;
		parent::__construct ();
	}

	public static $cache = array ();
	function get_test_subjects ()
	{
		return get_interpretable_scripts ();
	}

	function allow_failure_exit_code ()
	{
		return true;
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
		global $phc;
		$command = $this->command_line;
		$pipe_command = get_php_command_line ($subject, "pipe");
		return "$phc $command $subject | $pipe_command";
	}

	function homogenize_output ($output)
	{
		return homogenize_all ($output);
	}

	function get_name ()
	{
		return $this->name;
	}
}

?>
