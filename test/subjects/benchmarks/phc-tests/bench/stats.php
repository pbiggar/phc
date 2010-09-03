<?php
	/*
	*	Run from the phc root directory
	*	Use the -d flag to run tests on a whole directory
	*  The PHP file must be the first argument otherwise, and --stats and -O2 are implicit (it will fail if you pass -O2 or --stats)
	*/

	include 'lib/header.php';
	
	$name = $argv[2];

	$DB = new PDO ("sqlite:results/statdb/$name");

	$DB->exec ("
		CREATE table results 
		(date date,
		file varchar(200),
		flags varchar(200),
		test varchar(200),
		strings varchar(200),
		num real)
		");
 
	$dir_mode = false;
	$count = 0;
	$flags = "";

	$flow_context = " ";	
	// Extract flags
	foreach ($argv as $arg)
	{
		if($count > 2)
		{
			if ($arg != "-O2" || $arg != "--stats")
			{
				$flags = $flags.$arg;
				$flags = $flags." ";
			}
			if ($arg == "--flow-insensitive")
			{
				$flow_context = $flow_context.$arg;
				$flow_context = $flow_context." ";
			}

			if ($arg == "--call-string-length=1")
				$flow_context = $flow_context.$arg;
		}
		if ($argv[$count] == "-D")
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
				insert_results($DB, $filename, $flags, $flow_context);
			}
		}

	}
	else
	{
		exit (insert_results ($DB, $filename, $flags, $flow_context));
	}

	
	function insert_results (PDO $DB, $filename, $flags, $flow_context)
	{
		print ("$filename\n");	
	
		list ($output, $err, $exit_code) = complete_exec ("ulimit -t 2400 && ulimit -v 8000000 && src/phc --stats -O2 $filename $flags", NULL, 0);


		if ($err or $exit_code)
		{
			print ("exit: $exit_code\n");
			print ($err);
		}
		
		$output = split ("\n", $output);

		$date = date ("c");		

		print_r ($output);

		foreach ($output as $o)
		{
			$fields = split ("\|", $o);
			if (count($fields) == 3)
			{	
				$DB->exec ("
					INSERT INTO results
					VALUES ('$date',
						'$filename',
						'$flow_context',
						'".$fields[0]."',
						'".$fields[2]."',
						'".$fields[1]."')
					");
			}
		}
		return $exit_code;
	}
?>
