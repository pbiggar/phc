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
	$dir_name = dirname($subject);
	if ($pipe) $subject = "";
	return "$php -d include_path=./:$dir_name $subject 2>&1";
}


abstract class CompareWithPHP extends TwoCommandTest
{
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

	// Returns a command line with which to call php to interpret SUBJECT.
	// SUBJECT can be blank if you plan on piping to php
	abstract function get_command_line ($subject);

	function get_command_line2 ($subject)
	{
		return $this->get_command_line ($subject). " | ". get_php_command_line ($subject, "pipe");
	}

	function homogenize_output ($output)
	{
		$output = homogenize_filenames ($output);
		$output = homogenize_line_numbers ($output);
		$output = homogenize_break_levels ($output);
		return $output;
	}
}

?>
