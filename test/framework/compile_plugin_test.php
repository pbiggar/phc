<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compile a plugin using phc_compile_plugin, and check it works
 */

require_once ("lib/no_subject_test.php");
class CompilePluginTest extends NoSubjectTest
{
	function check_prerequisites ()
	{
		global $phc_compile_plugin;
		return check_for_program ($phc_compile_plugin);
	}

	function run_test ($subject)
	{
		global $phc;
		phc_assert ($subject == "All", "Shouldnt have test subjects passed here");
		global $phc_compile_plugin;

		$command = "cp plugins/tools/purity_test.cpp plugin.cpp 2>&1";
		list ($output, $return_value) = complete_exec ($command);
		if ($output || $return_value != 0)
		{
			$this->mark_failure ("All", $command, $return_value, $output);
			return;
		}


# TODO this -I stuff is very iffy. Use autovars
		$command = "CFLAGS=\"-I. -Isrc -I src/generated\" $phc_compile_plugin plugin.cpp 2>&1 > /dev/null "; # throw away stdout. Compiler errors come in on stderr
		list ($output, $return_value) = complete_exec ($command);
		if ($output || $return_value != 0)
		{
			$this->mark_failure ("All", $command, $return_value, $output);
			return;
		}

		$command = "$phc --run plugin.la test/subjects/general/if.php 2>&1 ";
		list ($output, $return_value) = complete_exec ($command);
		if ($return_value != 0) $this->mark_failure ("All", $command, $return_value, $output);
		else $this->mark_success ("All");
	}
}


array_push($tests, new CompilePluginTest ());

?>
