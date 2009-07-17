#!/usr/bin/env php
<?php

	$directory_name = "all_php_downloads/";

	$dirs = get_directories ($directory_name);

	foreach ($dirs as $dir)
	{
		$files = get_all_files ($dir);
		foreach ($files as $file)
		{
			$stats = get_file_stats ($file);

			add_stat ($dir, $file, $stats);
			echo "done: $file\n";
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


		$result = split (":", `src/phc $file --run plugins/tools/dynamic_things.la 2>/dev/null`);
		$result = split (",", $result[1]);
		return $result;
	}

	function add_stat ($package, $file, $stats)
	{
		global $stats;
		print "Adding stats for $package, $file\n";
		var_dump ($stats);

		$stats[$package]["eval"] += $stats[0];
		$stats[$package]["include"] += $stats[1];
		$stats[$package]["dynamic_include"] += $stats[2];

		$stats["all"]["eval"] += $stats[0];
		$stats["all"]["include"] += $stats[1];
		$stats["all"]["dynamic_include"] += $stats[2];
	}

	function dump_stats ()
	{
		var_dump ($stats);
		global $stats;

		foreach ($stats as $package => $actual_stats)
		{
			var_dump ($package, $actual_stats);
			foreach ($actual_stats as $key => $val)
			{
				print "$package: $key = $val\n";
			}
		}
	}





?>
