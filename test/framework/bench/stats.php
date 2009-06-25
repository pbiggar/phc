<?php
	/*
	*	Run from the phc root directory
	*	Use the -d flag to run tests on a whole directory
	*/

	include 'lib/header.php';
	
	$name = "types";
	$DB = new PDO ("sqlite:results/statdb/$name.db");

	$DB->exec ("
		CREATE table results 
		(date date,
		file varchar(200),
		flags varchar(200),
		test varchar(200),
		types varchar(200),
		num_types int)
		");
 
	$dir_mode = false;
	$count = 0;
	$flags = "";
	
	// Extract flags
	foreach ($argv as $arg)
	{
		if($count > 1)
		{
			if ($arg != "-O2" || $arg != "--stats")
			{
				$flags = $flags.$arg;
				$flags = $flags." ";
			}
		}
		if ($argv[$count] == "-d")
		{
			$dir_mode = true;
			$path = $argv[$count+1];
		}
		else
		{
			$count++;
		}
	}
	
	$filename = $argv[1];

	// Single file or whole directory?
	if ($dir_mode)
	{
		$dir = opendir ($path);
		while (($filename = readdir ($dir)) !== false) 
		{
			$phpext = '/.+\.php$/';
			if (preg_match($phpext, $filename))
			{ 
				$filename = $path.$filename;
				insert_results($DB, $filename, $flags);
			}
		}

	}
	else
	{
		insert_results ($DB, $filename, $flags);
	}

	
	function insert_results (PDO $DB, $filename, $flags)
	{
		print ("$filename\n");	
	
		$arr = complete_exec ("src/phc --stats -O2 $filename $flags 2>&1");

		$output = split ("\n", $arr[0]);

		$date = date ("c");		

		print_r ($output);

		foreach ($output as $o)
		{
			$DB->exec ("
				INSERT INTO results
				VALUES ('$date',
					'$filename',
					'$flags',
					$o)
				");
		}


	}

?>
