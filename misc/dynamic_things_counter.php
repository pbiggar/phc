#!/usr/bin/env php
<?php

	$directory_name = "all_php_downloads/";

	$dirs = get_directories ($directory_name);

	foreach ($dirs as $dir)
	{
		$files = get_all_files ($dir);
		foreach ($files as $file)
		{
			$file_stats = get_file_stats ($file);

			add_stat ($dir, $file, $file_stats);
			echo "$file\n";
		}
	}

	dump_stats ();


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
		$results = split ("\n", `find $dir/ -type f -name "*.php"`);
		array_pop ($results);
		return $results;
	}

	function get_file_stats ($file)
	{
		$result = `src/phc $file --run plugins/tools/dynamic_things.la 2>/dev/null`;
		$result = rtrim ($result);

		if ($result == "")
			return array ("0", "0", "0");


		$result = split (":", $result);
		$result = split (",", $result[1]);
		return $result;
	}

	function add_stat ($package, $file, $file_stats)
	{
		global $stats;

		$stats[$package]["eval"] += $file_stats[0];
		$stats[$package]["include"] += $file_stats[1];
		$stats[$package]["dynamic_include"] += $file_stats[2];

		$stats["all"]["eval"] += $file_stats[0];
		$stats["all"]["include"] += $file_stats[1];
		$stats["all"]["dynamic_include"] += $file_stats[2];
	}

	function dump_stats ()
	{
		global $stats;

		foreach ($stats as $package => $actual_stats)
		{
			print "$package";
			foreach ($actual_stats as $key => $val)
			{
				print ", $key = $val";
			}
			print "\n";
		}
	}


?>
