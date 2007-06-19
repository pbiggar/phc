<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compile a plugin using phc_compile_plugin, and check it works
 */

class CompilePluginTest extends Test
{
	function check_prerequisites ()
	{
		global $phc_compile_plugin;
		return check_for_program ($phc_compile_plugin);
	}

	// all plugins are tests
	function get_test_subjects ()
	{
		return get_all_plugins ();
	}

	function get_dependent_test_names ()
	{
		return array (); // the subjects arent used elsewhere
	}

	function run_test ($subject)
	{
		global $phc;
		global $trunk_CPPFLAGS;
		global $phc_compile_plugin;
		$plugin_name = tempnam (".", "plugin");
		unlink ("$plugin_name");

		if (!copy ($subject, "$plugin_name.cpp"))
		{
			$this->mark_failure ($subject, "Copy failed");
			return;
		}

		// copy the header files from the plugin's directory to ./
		$dirname = dirname ($subject);
		$headers = split ("\n", chop (`find $dirname -name "*.h"`));
		$new_headers = array ();
		if ($headers !== array (""))
		{
			foreach ($headers as $header)
			{
				$dest = "./".basename ($header);
				if (!copy ($header, $dest))
				{
					$this->mark_failure ($subject, "Copying headers failed", "$header to $dest");
					return;
				}
				$new_headers[] = $dest; // we need to delete them later
			}
		}

		# phc_compile_plugin only allows CFLAGS and LDFLAGS, even though we use CPPFLAGS
		if ($trunk_CPPFLAGS)
			$CPPFLAGS = "CFLAGS=$trunk_CPPFLAGS";
		else
			$CPPFLAGS = "";

		$command = "$CPPFLAGS $phc_compile_plugin $plugin_name.cpp";
		list ($out, $err, $exit) = complete_exec ($command); # ignore stdout
		if ($err or $exit)
		{
			$this->mark_failure ($subject, $command, $exit, $out, $err);
			// dont delete the files - leave them as a trail
			return;
		}

		$files = get_all_scripts ();
		$filename = $files[0];
		$command = "$phc --run $plugin_name.la $filename";
		list ($out, $err, $exit) = complete_exec ($command);
		if ($exit != 0) $this->mark_failure ($subject, $command, $exit, $out, $err);
		else 
		{
			$this->mark_success ($subject);
			// add files created on other platforms here
			unlink ("$plugin_name.cpp");
			// TODO libtool --mode-clean plugin.lo will clean up these files
			unlink ("$plugin_name.o");
			unlink ("$plugin_name.lo");
			unlink ("$plugin_name.la");
			foreach ($new_headers as $header)
			{
				unlink ($header);
			}
		}
	}
}


array_push($tests, new CompilePluginTest ());

?>
