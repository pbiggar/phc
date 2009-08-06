<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Run phc with the required plugin, checking for known success conditions.
 */

require_once ("async_test.php");

class PluginTest extends AsyncTest
{
	function __construct ($plugin_name, $other_commands = "")
	{
		$this->other_commands = $other_commands;
		$this->commands_as_string = preg_replace ("/\s/", " ", $other_commands);
		$this->plugin_name = $plugin_name;
		parent::__construct();
	}

	function get_dependent_test_names ()
	{
		$result = array ("BasicParseTest");

		// if the plugin uses other commands, then the base plugin is probably a prerequisite
		if ($this->other_commands)
			$result[] = $this->plugin_name;
		return $result;
	}

	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	function check_prerequisites ()
	{
		return check_for_plugin ("tests/". $this->plugin_name);
	}

	function get_name ()
	{
		$name = "plugin_{$this->plugin_name}";
		if ($this->other_commands)
			$name .= "_with_". $this->commands_as_string;
		return $name;
	}

	function get_command_line ($subject)
	{
		global $phc, $plugin_dir;
		$plugin = $this->plugin_name;
		$commands = $this->other_commands;
		return "$phc $commands --run $plugin_dir/tests/$plugin.la $subject";
	}

	function finish ($async)
	{
		if ($async->outs[0] === "Success\n" 
			and $async->exits[0] === 0
			and $async->errs[0] === "")
		{
			$this->async_success ($async);
		}
		else
		{
			$this->async_failure ("Not success or skipped", $async);
		}
	}

	function run_test ($subject)
	{
		$async = new AsyncBundle ($this, $subject);

		$async->commands[0] = $this->get_command_line ($subject);

		$async->final = "finish";

		$async->start ();
	}

}

?>
