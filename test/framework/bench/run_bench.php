<?php

	// TODO make sure they compute the same result.

	$prefix = "test/subjects/3rdparty/benchmarks/shootout";
	$php = "/usr/local/php-opt/bin/php";
	$memory_limit = 128;

	function run_phc ($filename, $name, $input)
	{
		// Compile it. The tests are run after this, but they
		// all have a very short run if no command line
		// parameters are given.
		$compile_cmd = "misc/comp -O $filename";
		print $compile_cmd."\n";
		`$compile_cmd`;


		// run it.
		$run_cmd = "./$name.out $input";
		$start = microtime (1);
		print "$run_cmd\n";;
		print `$run_cmd`;
		$stop = microtime (1);

		return $stop - $start;
	}

	function run_php ($filename, $input)
	{
		global $php;
		global $memory_limit;

		// start the timer
		$start = microtime (1);

		$command = "$php -d memory_limit={$memory_limit}M $filename $input";
		print "$command\n";
		print `$command`;

		// stop the timer
		$stop = microtime (1);

		// if it runs outside of the 20-30 second range, fail.
		return $stop - $start;
	}

	function run ($name, $cmdline_input)
	{
//		$cmdline_input = ""; // run the test very quickly
		global $prefix;
		$filename = "$prefix/$name.php";


		// run it in php first
		$time = run_php ($filename, $cmdline_input);
		print "PHP: $name: $time";

		if ($time > 30 or $time < 20)
			print " - Test outside time range\n";

		print "\n";


		// run it with phc
		$time = run_phc ($filename, $name, $cmdline_input);
		print "phc: $name: $time\n";
	}

	function inc_mem ($mem) { global $memory_limit; $memory_limit = $mem; }
	function dec_mem () { global $memory_limit; $memory_limit = 128; }


	// broken or worthless
//	run ("hello", x);
//	run ("meteor", 100); // test doesnt work


	// simple

	run ("ackermann", 9);
	run ("ary", 60000);
	run ("binarytrees", 13);
	run ("binarytrees.php-2", 14);
	run ("dispatch", 70000);
	run ("fannkuch", 9);
	run ("fasta.php-2", 450000);
	run ("fibo", 34);
	run ("harmonic", 40000000);
	run ("hash2", 3000);
	run ("heapsort", 800000);
	run ("lists", 16);
	run ("mandelbrot.php-2", 800);
	run ("matrix", 1200);
	run ("methcall", 5000000);
	run ("nbody", 250000);
	run ("nestedloop", 22);
	run ("nsievebits", 8);
	run ("nsievebits.php-2", 9);
	run ("objinst", 4000000);
	run ("partialsums", 4500000);
	run ("pidigits", 1600);
	run ("pidigits.php-2", 11000);
	run ("random", 9000000);
	run ("raytracer", 5);
	run ("raytracer.php-2", 5);
	run ("recursive.php-2", 7);
	run ("sieve", 1800);
	run ("spectralnorm", 550);
	run ("takfp", 9);

	// need extra memory
	inc_mem (512);

	run ("hash", 6000000);
	run ("nsieve", 9);
	run ("nsieve.php-2", 10);

	dec_mem ();


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
