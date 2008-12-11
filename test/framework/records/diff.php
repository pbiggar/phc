<?php

	include ("common.php");

	function run_main ()
	{
		$old_rev = (int)$_GET["old_rev"];
		$new_rev = (int)$_GET["new_rev"];
		$unsafe_filename = $_GET["filename"];
		$sort_first = $_GET["sort"] or false;

		# Sanitize the revisions: 0 < old_rev < new_rev < 5000
		if (!(0 < $old_rev)) bad ();
		if (!($old_rev < $new_rev)) bad ();
		if (!($new_rev < 5000)) bad ();

		# Sanitize the inputs: the file should be within the results/$rev subdirectory
		$relative_filename = "results/$new_rev/$unsafe_filename";
		$real_filename = realpath ($relative_filename);

		# We find the dir by checking the fullname of this script, and stripping off the script name at the end
		$real_scriptname = realpath (__FILE__);
		$scriptname = "test/framework/records/diff.php";
		$script_dir = str_replace ($scriptname, "", $real_scriptname);

		# Check that the script is within these bounds
		if (strpos ($real_filename, $script_dir) !== 0) # FALSE is a fail, but 0 isnt
			bad ();

		$old_filename = realpath ("results/$old_rev/$unsafe_filename");
		$new_filename = realpath ("results/$new_rev/$unsafe_filename");

		if (!file_exists ($old_filename))
			die ("No old file");

		if (!file_exists ($new_filename))
			die ("No new file");

		$old = file_get_contents ($old_filename);
		if ($sort_first)
		{
			$split = split ("\n", $old);
			sort ($split);
			$old = join ("\n", $split);
		}

		$new = file_get_contents ($new_filename);
		if ($sort_first)
		{
			$split = split ("\n", $new);
			sort ($split);
			$new = join ("\n", $split);
		}


		echo "<pre>" .diff ($old, $new) ."</pre>\n";

	}

	function bad ()
	{
		die ("An error has been made with input variables");
	}


?>
