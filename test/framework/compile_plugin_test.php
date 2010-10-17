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
		global $working_directory, $plugin_dir, $base_dir;

		// copy the header files from the plugin's directory to
		// working dir
		$headers = preg_split ("/\n/", chop (`find $base_dir/plugins -name "*.h"`));
		$new_headers = array ();
		if ($headers !== array (""))
		{
			foreach ($headers as $header)
			{
				$dest = "$working_directory/".basename ($header);
				if (!copy ($header, $dest))
				{
					$this->async_failure ($subject, "Copying headers failed", "$header to $dest");
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
		global $phc, $trunk_CPPFLAGS, $phc_compile_plugin, $working_directory, $base_dir;

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
			$CPPFLAGS = "$trunk_CPPFLAGS";
		else
			$CPPFLAGS = "''";

		$CPPFLAGS[0] = ' ';
		$CPPFLAGS="CFLAGS='-Wno-deprecated $CPPFLAGS";

		$async->commands[0] = "$CPPFLAGS $phc_compile_plugin $plugin_name.cpp";
		$async->err_handlers[0] = "fail_on_output";
		$async->exit_handlers[0] = "fail_on_output";


		// Check it runs under phc
		$files = get_all_scripts ();
		$filename = $files[0];
		// --r-option is a special option for reduce_statements.la, which doesn't harm the other tests.
		$async->commands[1] = "$phc --run $plugin_name.la $filename --r-option 0:1";
		$async->err_handlers[1] = "fail_on_output";
		$async->exit_handlers[1] = "fail_on_output";

		$async->final = "async_success";

		$async->start ();
	}
}


array_push($tests, new CompilePluginTest ());

?>
