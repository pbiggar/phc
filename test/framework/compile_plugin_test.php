<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compile a plugin using phc_compile_plugin, and check it works
 */

class CompilePluginTest extends AsyncTest
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

	function copy_headers ()
	{
		global $working_directory;

		// copy the header files from the plugin's directory to
		// working dir
		$headers = split ("\n", chop (`find plugins/ -name "*.h"`));
		$new_headers = array ();
		if ($headers !== array (""))
		{
			foreach ($headers as $header)
			{
				$dest = "$working_directory/".basename ($header);
				if (!copy ($header, $dest))
				{
					$this->mark_failure ($subject, "Copying headers failed", "$header to $dest");
					return;
				}
			}
		}
	}

	function run ()
	{
		$this->copy_headers ();
		parent::run ();
	}

	function run_test ($subject)
	{
		global $phc, $trunk_CPPFLAGS, $phc_compile_plugin, $working_directory;

		// setup the files
		$plugin_name = tempnam ($working_directory, "plugin");
		unlink ("$plugin_name");
		if (!copy ($subject, "$plugin_name.cpp"))
		{
			$this->mark_failure ($subject, "Copy failed");
			return;
		}

		$async = new AsyncBundle ($this, $subject);


		# phc_compile_plugin only allows CFLAGS and LDFLAGS, even
		# though we use CPPFLAGS
		if ($trunk_CPPFLAGS)
			$CPPFLAGS = "CFLAGS=$trunk_CPPFLAGS";
		else
			$CPPFLAGS = "";

		$async->commands[0] = "$CPPFLAGS $phc_compile_plugin $plugin_name.cpp";
		$async->err_handlers[0] = "fail_on_output";
		$async->exit_handlers[0] = "fail_on_output";


		// Check it runs under phc
		$files = get_all_scripts ();
		$filename = $files[0];
		$async->commands[1] = "$phc --run $plugin_name.la $filename";
		$async->err_handlers[1] = "fail_on_output";
		$async->exit_handlers[1] = "fail_on_output";

		$async->final = "finish";

		$async->start ();
	}

	function finish ($async)
	{
		$this->mark_success ($async->subject);
	}

}


array_push($tests, new CompilePluginTest ());

?>
