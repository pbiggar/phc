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

$default_labels		=	array("non-erroneous", "long",  "non-interpretable", "size-neutral", "non-includable");
$non_default_labels =	array("erroneous", "short", "interpretable", "size-dependent", "includable");
$labels =				array_merge($default_labels, $non_default_labels);
$opposite_label = array(
	"non-erroneous" => "erroneous",				"erroneous" => "non-erroneous",
	"long" => "short",								"short" => "long",
	"non-interpretable" => "interpretable",	"interpretable" => "non-interpretable",
	"size-neutral" => "size-dependent",			"size-dependent" => "size-neutral",
	"non-includable" => "includable",				"includable" => "non-includable");

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

function create_label_struct ($directory, $label_filename, $third_party_filename)
{
	global $default_labels;
	global $non_default_labels;
	global $opposite_label;
	global $labels;
	global $exceptions;

	// get all the php scripts in the file
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
	$third_party_lines = file ($third_party_filename);

	foreach($lines as $line)
	{
		$line = preg_replace("/#.*$/", "", $line); // remove comments
		$line = trim($line); // remove superfluous whitespace
		if ($line == "") continue; // skip blank lines
		process_label_file_line ($line, $files, &$labelled_files);
	}

	foreach($third_party_lines as $line)
	{
		$line = preg_replace("/#.*$/", "", $line); // remove comments
		$line = trim($line); // remove superfluous whitespace
		if ($line == "") continue; // skip blank lines
		process_label_file_line ("3rdparty/".$line, $files, &$labelled_files);
	}

	# init the label struct
	foreach ($labels as $label)
	{
		$label_struct{$label} = array();
	}
	# go over the labelled_files, and make an table indexed by label
	foreach ($files as $filename)
	{
		phc_assert(isset($labelled_files{$filename}), "file not found");

		// check the interpretable
		if ($labelled_files{$filename}{"non-interpretable"} === "check")
		{
			phc_assert (check_for_plugin ("tools/purity_test"), "purity not available");
			global $phc, $plugin_dir;
			if (`$phc --run $plugin_dir/tools/purity_test.la $filename 2>&1` == "")
			{
				$labelled_files{$filename}{"non-interpretable"} = 0;
			}
			else
			{
				$labelled_files{$filename}{"non-interpretable"} = 1;
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

function process_label_file_line ($line, $files, $labelled_files)
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
			else if (preg_match ("/no-(.*)/", $label, $matches))
			{
				if (isset($exceptions{$matches[1]}))
					array_push($exceptions{$matches[1]}, $filename);
				else
					$exceptions{$matches[1]} = array($filename);
			}
			else if ($label == "check-interpretable")
			{
				print "Marking $filename as check\n";
				$labelled_files{$filename}{"interpretable"} = "check";
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

// returns a list of php script which use the include feature
function get_includable_scripts()
{
	return get_scripts_labelled("includable");
}

function get_erroneous_scripts()
{
	return get_scripts_labelled("erroneous");
}

function get_non_erroneous_scripts()
{
	return get_scripts_labelled("non-erroneous");
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

	// this is run from the src directory
	$dirs = array($directory);

	$result = array();
	for($i = 0; $i < count($dirs); $i++)
	{
		$dir = $dirs[$i];
		// open the directory
		if ($dh = @opendir($dir)) 
		{
			// get the current file
			while (($file = readdir($dh)) !== false) 
			{
				// if its a directory recurse into it by adding it to the list
				if (is_dir($dir.$file))
				{
					if ($file != "." and $file != "..")
					{
						// you need the compound relative directory name to open it
						array_push($dirs, $dir.$file."/");
					}
				}
				elseif (preg_match("/\.php$/", $file)) // otherwise the the file(.php files only)
				{
					array_push($result, $dir.$file);
				}
			}
			closedir($dh);
		}
		else
		{
			mkdir($dir, 0755, true);
		}
	}

	return $result;
}

// returns a list of all the php files within a directory (non-recursively)
function get_scripts_in_dir($directory)
{
	$result = array();

	$dir = $directory;
	// open the directory
	if ($dh = opendir($dir)) 
	{

		// get the current file
		while (($file = readdir($dh)) !== false) 
		{
			// otherwise add the file(.php files only)
			if (preg_match("/\.php$/", $file)) 
			{
				array_push($result, $dir.$file);
			}
		}
		closedir($dh);
	}

	return $result;
}



?>
