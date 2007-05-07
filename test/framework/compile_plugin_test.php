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
		global $trunk_CPPFLAGS;
		phc_assert ($subject == "All", "Shouldnt have test subjects passed here");
		global $phc_compile_plugin;
		$plugin_name = tempnam (".", "plugin");
		unlink ("$plugin_name");

		if (!copy ("plugins/tools/purity_test.cpp", "$plugin_name.cpp"))
		{
			$this->mark_failure ("All", "Copy failed", 0, "");
			return;
		}

		# phc_compile_plugin only allows CFLAGS and LDFLAGS, even though we use CPPFLAGS
		if ($trunk_CPPFLAGS)
			$trunk_CPPFLAGS = "CFLAGS=$trunk_CPPFLAGS";

		$command = "$trunk_CPPFLAGS $phc_compile_plugin $plugin_name.cpp 2>&1 > /dev/null "; # throw away stdout. Compiler errors come in on stderr
		list ($output, $return_value) = complete_exec ($command);
		if ($output || $return_value != 0)
		{
			$this->mark_failure ("All", $command, $return_value, $output);
			// dont delete the files - leave them as a trail
			return;
		}

		$command = "$phc --run $plugin_name.la test/subjects/general/if.php 2>&1 ";
		list ($output, $return_value) = complete_exec ($command);
		if ($return_value != 0) $this->mark_failure ("All", $command, $return_value, $output);
		else 
		{
			$this->mark_success ("All");
			// add files created on other platforms here
			unlink ("$plugin_name.cpp");
			// TODO libtool --mode-clean plugin.lo will clean up these files
			unlink ("$plugin_name.o");
			unlink ("$plugin_name.lo");
			unlink ("$plugin_name.la");
		}
	}
}


array_push($tests, new CompilePluginTest ());

?>
