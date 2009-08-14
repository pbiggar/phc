#!/usr/bin/env php
<?php

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
		echo "Analysing $dir\n";
		$files = get_all_files ($dir);
		foreach ($files as $file)
		{
			$file_stats = get_file_stats ($file);
			if ($file_stats === NULL 
					|| ($file_stats[0] == (string)"0" && $file_stats[1] == (string)"0" && $file_stats[2] == (string)"0"))
			{
				continue;
			}
			else
				if ($argv[1] == "-delete")	
				{
					`rm -r -f $dir`;
					echo "Deleting $dir\n";
					continue 2;
				}

			add_stat ($dir, $file, $file_stats);
			echo "$file\n";
		}
	}

	aggregate_stats ();
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
		$results = split ("\n", _exec ("find $dir/ -type f -name \"*.php\""));
		array_pop ($results);
		return $results;
	}

	function get_file_stats ($file)
	{
		$result = _exec ("src/phc $file --run plugins/tools/dynamic_things.la 2>/dev/null");
		$result = rtrim ($result);

		if ($result == "")
			return NULL;


		$result = split (":", $result);
		$result = split (",", $result[1]);
		return $result;
	}

	function add_stat ($package, $file, $file_stats)
	{
		global $stats;
		$linecount = (int)(_exec ("cat $file | wc -l"));

		$stats[$package]["eval"] += $file_stats[0];
		$stats[$package]["include"] += $file_stats[1];
		$stats[$package]["dynamic_include"] += $file_stats[2];
		$stats[$package]["filecount"] += 1;
		$stats[$package]["linecount"] += $linecount;

		$stats["all"]["eval"] += $file_stats[0];
		$stats["all"]["include"] += $file_stats[1];
		$stats["all"]["dynamic_include"] += $file_stats[2];
		$stats["all"]["filecount"] += 1;
		$stats["all"]["linecount"] += $linecount;
	}

	function aggregate_stats ()
	{
		global $stats;

		# Calculate averages
		$package_count = count ($stats) - 1;
		foreach (array ("eval", "include", "dynamic_include", "filecount", "linecount") as $name)
		{
			$stats["average"][$name] = $stats["all"][$name] / $package_count;
		}

		# How many have at least 1?
		foreach ($stats as $package => $actual_stats)
		{
			if ($package == "all" || $package == "average" || $package == "aggregate")
				continue;

				
			foreach ($actual_stats as $key => $val)
			{
				if ($val >= 1)
					$stats["aggregate"][$key] += 1;
			}

			if ($actual_stats["eval"] >= 1 || $actual_stats["dynamic_include"] >= 1)
			{
				$stats["aggregate"]["either"] += 1;
			}
		}
	}

	function dump_stats ()
	{
		global $stats;

		foreach ($stats as $package => $actual_stats)
		{
			if ($package == "all" || $package == "average" || $package == "aggregate")
			{
				print "$package";
				foreach ($actual_stats as $key => $val)
				{
					print ", $key = $val";
				}
				print "\n";
			}
		}
	}

	function _exec ($command)
	{
		// 20 seconds, max
		list ($output) = complete_exec ($command, NULL, 20);
		return $output;
	}


?>
