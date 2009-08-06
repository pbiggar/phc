<?php
	/*
	* Runs the list of files (stripped of ".php") in test/framework/bench/list.txt
	*/

	$php = "/usr/local/php-opt/bin/php";

	function run_phc ($filename, $name, $input)
	{
		global $date;
		// Compile it. The tests are run after this, but they
		// all have a very short run if no command line
		// parameters are given.
		$compile_cmd = "misc/comp -O -i $filename";
		print $compile_cmd."\n";
		system ($compile_cmd, $exit_code);
		print ($exit_code);
		if($exit_code)
		{
			$error_file = fopen ("results/".$date."_errors", "a");
			fwrite ($error_file, "$filename did not compile\n");
			fclose ($error_file);
		}
		else
		{
			// run it.
			$run_cmd = "./".`basename "$name.out"`;
			$start = microtime (1);
			print "$run_cmd\n";
			system($run_cmd, $exit_code);
			$stop = microtime (1);
			print ($exit_code);
			if ($exit_code)
			{
				$error_file = fopen ("results/".$date."_errors", "a");
				fwrite ($error_file, "$run_cmd failed\n");
				fclose ($error_file);
				return 0;
			}
			return $stop - $start;
		}
		return 0;
	}

	function run_php ($filename, $input)
	{
		global $php;

		// start the timer
		$start = microtime (1);

		$command = "$php $filename $input";
		print "$command\n";
		print `$command`;

		// stop the timer
		$stop = microtime (1);

		return $stop - $start;
	}

	function run ($name, $cmdline_input)
	{
		global $date;
		$filename = "$name.php";


		// run it in php first
		$time = run_php ($filename, $cmdline_input);
		print "PHP: ".basename ($name).": $time";
		print "\n";		

		$php_res = fopen ("results/php_$date.txt","a");
		fwrite ($php_res, basename ($name)."     ".$time."\n");
		fclose ($php_res);
		
		// run it with phc
		$time = run_phc ($filename, $name, $cmdline_input);
		print "phc: ".basename ($name).": $time\n";
			
		$phc_res = fopen ("results/phc_$date.txt", "a");
		fwrite ($phc_res, basename ($name)."     ".$time."\n");
		fclose ($phc_res);
	}

	$date = date ("c");
	
	$bench_list = fopen ("test/framework/bench/list.txt", "r");
	while ($bench = fgets ($bench_list))
	{
		run (chop ($bench), "");
	}

	fclose ($bench_list);

	// special input // TODO

//	run_unique_input ("knucleotide", 2500, "kneucleotide-input.txt");
//	run_input ("moments", 25, "moments-input.txt");
//	run_unique_input ("regexdna.php-2", 10000, "regex-dna-input.txt");
//	run_input ("regexmatch", 12000, "regexmatch-input.txt");
//	run_unique_input ("revcomp", 25000, "revcomp-input.txt");
//	run_generated_input ("reversefile", 10, "reversefile-input.txt");
//	run_generated_input ("spellcheck", 7, "spellcheck-input.txt");
//	run_sampled ("strcat", 10000, 0.1);
//	run_generated_input ("sumcol", 400, "sumcol-input.txt");
//	run_input ("wc", x, "wc-input.txt");
//	run_generated_input ("wordfreq", 25, "wordfreq-input.txt");

?>
