<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Functions and data to parse and maniupulate label files
 */

$subject_dir =		"test/subjects/";
$label_file =		"test/subjects/labels";
$third_party_label_file =		"test/subjects/3rdparty/labels";

$default_labels		=	array("long",  "non-interpretable", "size-neutral");
$non_default_labels =	array("short", "interpretable", "size-dependent");
$labels =				array_merge($default_labels, $non_default_labels);
$opposite_label = array(
	"long" => "short",								"short" => "long",
	"non-interpretable" => "interpretable",	"interpretable" => "non-interpretable",
	"size-neutral" => "size-dependent",			"size-dependent" => "size-neutral");

$exceptions = array();

$label_struct = create_label_struct ($subject_dir, $label_file, $third_party_label_file);

if (!$opt_long)
{
	$label_struct = strip_long_files($label_struct);
}

function strip_long_files ($label_struct)
{
	global $labels;
	$long_files = $label_struct{"long"};
	foreach($labels as $label)
	{
		// remove the long files from 
		$label_struct{$label} = array_values (array_diff($label_struct{$label}, $long_files));
	}
	return $label_struct;
}

/* Returns true if this is a long test, and we're only doing short tests */
function skip_3rdparty ($filename)
{
	global $opt_long;
	return (!$opt_long && preg_match ("#/3rdparty/#", $filename));
}

function create_label_struct ($directory, $label_filename, $third_party_filename)
{
	global $default_labels;
	global $non_default_labels;
	global $opposite_label;
	global $labels;
	global $exceptions;
	global $opt_one;

	$files = get_all_scripts_in_dir ($directory);

	// labelled files is a table indexed by filename, containing tables indexed
	// by default labels, which are set to 1 or 0 for default and non-default
	// respectively
	foreach ($default_labels as $default)
	{
		foreach($files as $filename) { $labelled_files{$filename}{$default} = 1; }
	}
	foreach($files as $filename) 
	{ 
		$labelled_files{$filename}{"non-interpretable"} = "check"; 
	}

	// parse the file
	$lines = file($label_filename);
	if (file_exists ($third_party_filename)) 
		$third_party_lines = file ($third_party_filename);
	else 
		$third_party_lines = array ();

	foreach($lines as $line)
	{
		$line = preg_replace("/#.*$/", "", $line); // remove comments
		$line = trim($line); // remove superfluous whitespace
		if ($line == "") continue; // skip blank lines
		process_label_file_line ($line, $files, $labelled_files);
	}

	foreach($third_party_lines as $line)
	{
		$line = preg_replace("/#.*$/", "", $line); // remove comments
		$line = trim($line); // remove superfluous whitespace
		if ($line == "") continue; // skip blank lines
		process_label_file_line ("3rdparty/".$line, $files, $labelled_files);
	}

	# if -O is provided, remove all other files
	if ($opt_one)
	{
		foreach ($labelled_files as $key => $value)
		{
			if ($key !== $opt_one)
			{
				unset ($labelled_files[$key]);
				$files = array ($opt_one);
			}
		}
	}

	# init the label struct
	foreach ($labels as $label)
	{
		$label_struct{$label} = array();
	}
	# go over the labelled_files, and make an table indexed by label
	foreach ($files as $filename)
	{
		// If you have a ton of 3rd party files, dont spend time checking them
		// all, unless your actually going to use them 
		if (skip_3rdparty ($filename))
		{
			$labelled_files{$filename}{"non-interpretable"} = 0;
		}
		else
		{
			phc_assert(isset($labelled_files{$filename}), "file not found");

			// check the interpretable
			if ($labelled_files{$filename}{"non-interpretable"} === "check")
			{
				phc_assert (check_for_plugin ("tools/purity_test"), "purity not available");
				global $phc, $plugin_dir;
				if (`$phc --run $plugin_dir/tools/purity_test.la $filename 2>&1` == "")
				{
					log_status ("pure", "", $filename, "");
					$labelled_files{$filename}{"non-interpretable"} = 0;
				}
				else
				{
					log_status ("impure", "", $filename, "");
					$labelled_files{$filename}{"non-interpretable"} = 1;
				}
			}
		}

		foreach ($default_labels as $label)
		{
			if ($labelled_files{$filename}{$label})
			{
				array_push ($label_struct{$label}, $filename);
			}
			else
			{
				array_push ($label_struct{$opposite_label{$label}}, $filename);
			}
		}
	}

	// sort and generally fix up the arrays
	foreach ($labels as $label)
	{
		sort($label_struct{$label});
	}

	return $label_struct;
}

function process_label_file_line ($line, $files, &$labelled_files)
{
	global $default_labels;
	global $non_default_labels;
	global $opposite_label;
	global $labels;
	global $exceptions;

	// split into file and labels
	$split = preg_split("/\s+/", $line);

	$pattern = array_shift ($split);
	$pattern = "^test/subjects/$pattern";
	$matches = preg_grep ("!$pattern!", $files);
	/* allow that pattern, as 3rdparty directory may be empty */
	if ($pattern !== "^test/subjects/3rdparty/.*")
	{
		phc_assert(count($matches), "pattern !$pattern! matches no files");
	}

	// add to data structure
	foreach($split as $label)
	{
		foreach ($matches as $filename)
		{
			if (in_array($label, $default_labels))
			{
				$labelled_files{$filename}{$label} = 1;
			}
			else if (in_array($label, $non_default_labels))
			{
				$labelled_files{$filename}{$opposite_label{$label}} = 0;
			}
			else if (preg_match ("/no-(.*)/", $label, $exception_matches))
			{
				$exceptions{$filename}[] = $exception_matches[1];
			}
			else if ($label == "check-interpretable")
			{
				$labelled_files{$filename}{"non-interpretable"} = "check";
			}
			else
			{
				$label_names = join(", ", $labels);
				phc_unreachable ("Label file error: $label not a valid label (must be in $label_names)");
			}
		}
	}
}

function get_scripts_labelled($label)
{
	global $label_struct;
	phc_assert($label_struct !== null, "label structure not yet initialized");
	return $label_struct{$label};
}

function get_interpretable_scripts()
{
	return get_scripts_labelled("interpretable");
}

function get_non_interpretable_scripts()
{
	return get_scripts_labelled("non-interpretable");
}

function is_labelled($script, $label)
{
	global $label_struct;
	phc_assert($label_struct !== null, "label structure not yet initialized");
	# this doesnt return a simple true/false, so wrap it
	if (array_search($script, $label_struct{$label}) === false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// returns a list of all php scripts
function get_all_scripts()
{
	global $label_struct;
	phc_assert($label_struct !== null, "label structure not yet initialized");

	// returns an array of arrays
	$all_files = array_values($label_struct);

	// merge into a single array
	$result = array();
	foreach($all_files as $array)
	{
		$result = array_merge($result, $array);
	}
	$result = array_unique($result);
	return $result;
}


// returns a list of all the php files within a directory (recursively)
function get_all_scripts_in_dir($directory)
{
	phc_assert($directory != '', "Cant search blank directory");
	phc_assert(preg_match("/\/$/", $directory), "directory '$directory' must end in a '/'");

	$command = "find -L $directory -name \"*.php\"";
	$result = explode ("\n", trim (`$command`));
	if (count ($result) == 1 && $result[0] == "")
		return array ();

	# I have no idea why, but on OSX `find` returns two forward-slashes in some 
	# cases, and PHP won't open directories structured like that.
	foreach($result as &$line)
		$line = preg_replace("!//!", "/", $line);

	return $result;
}

function get_all_plugins ()
{
	global $base_dir;
	$command = "find $base_dir/plugins -name \"*.cpp\"";
	$result = preg_split ("/\n/", trim (`$command`));
	if (count ($result) == 1 && $result[0] == "")
		return array ();

	return $result;
}

?>
