<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Run phc with the required plugin, checking for known success conditions.
 */

class PluginTest extends Test
{
	function __construct ($plugin_name)
	{
		$this->plugin_name = $plugin_name;
		parent::__construct();
	}

	function get_test_subjects ()
	{
		return get_non_erroneous_scripts();
	}

	function check_prerequisites ()
	{
		return check_for_plugin ("tests/". $this->plugin_name);
	}

	function get_name ()
	{
		return $this->plugin_name;
	}

	function get_command_line ($subject)
	{
		global $phc, $plugin_dir;
		$plugin = $this->plugin_name;
		return "$phc --run $plugin_dir/tests/$plugin.la $subject 2>&1";
	}

	function run_test ($subject)
	{
		$command = $this->get_command_line ($subject);
		list ($output, $return_value) = complete_exec($command);
# TODO check return value aswell
		if ($output == "Success\n")
		{
			$this->mark_success ($subject);
		}
		elseif ($output == "Skipped\n")
		{
			$name = $this->plugin_name;
			$this->mark_skipped ($subject, "Plugin $name returns skipped");
		}
		else
		{
			$this->mark_failure ($subject, $command, $return_value, $output);
		}
	}

}

?>
