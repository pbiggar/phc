#!/usr/bin/env php
<?php
/*
*
* Replaces define ("MYCONSTANT", "mydir/"); include (MYCONSTANT."myfile.php"); with include ("mydir/"."myfile.php");
* in all php files in downloaded_php/downloads
*
* TODO:  This isn't working properly.  Probably need to escape more characters passed to r-option.  This is probably best done in 
* the replace_include_constants plugin, however.
*/

	include ("test/framework/lib/header.php");

	function eh ($errno, $errstr)
	{
		if ($errno == E_NOTICE)
			return;

		print "$errno, $errstr";
	}

	set_error_handler ("eh", E_ALL);



	$directory_name = "downloaded_php/downloads/";

	$dirs = get_directories ($directory_name);
	foreach ($dirs as $dir)
	{
		$defines = "";
		$i = 0;
		$files = get_all_files ($dir);
		foreach ($files as $file)
		{
			if ($file != NULL)
			{
				$defines = $defines.get_defines ($file);	
				echo "Analysing $file\n";
			}
		}
		foreach ($files as $file)
		{
			echo "Applying changes to $file\n";
			apply_changes ($file, $defines);	
			
		}

	}



	function get_directories ($dirname)
	{
		$result = array ();

		foreach (new DirectoryIterator($dirname) as $fileInfo)
		{
			if ($fileInfo->isDot())
				continue;

			$result[] = $fileInfo->getPathname ();
		}

		return $result;
	}

	function get_all_files ($dir)
	{
		$results = split ("\n", _exec ("find $dir/ -type f -name \"*.php\""));
		array_pop ($results);
		return $results;
	}

	
	function _exec ($command)
	{
		// 20 seconds, max
		list ($output) = complete_exec ($command, NULL, 20);
		return $output;
	}

	function get_defines ($file)
	{
		$command = "src/phc $file --run plugins/tools/get_defines.la 2>/dev/null";
		return _exec ($command);
	}

	function apply_changes ($file, $defines)
	{
		$command = "src/phc $file --run plugins/tools/replace_include_constants.la --r-option='$defines' --dump=decomment 2>/dev/null";
		$newcode = _exec ($command);
		$fh = fopen ($file, "w");
		fwrite ($fh, $newcode);
		fclose ($fh);
	}
?>
