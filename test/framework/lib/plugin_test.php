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

	function get_dependent_test_names ()
	{
		return array ("BasicParseTest");
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
		return "$phc --run $plugin_dir/tests/$plugin.la $subject";
	}

	function run_test ($subject)
	{
		$command = $this->get_command_line ($subject);
		list ($out, $err, $exit) = complete_exec($command);
		if ($out == "Success\n" and $exit == 0 and $err == "")
		{
			$this->mark_success ($subject);
		}
		elseif ($out == "Skipped\n")
		{
			$name = $this->plugin_name;
			$this->mark_skipped ($subject, "Plugin $name returns skipped");
		}
		else
		{
			$this->mark_failure ($subject, $command, $exit, $out, $err);
		}
	}

}

?>
