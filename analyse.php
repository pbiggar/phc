#!/usr/bin/env php
<?php

	require_once ("test/framework/lib/header.php");
	require_once ("test/framework/external/Console/Getopt.php");


	$cg = new Console_Getopt();
	$getopt = $cg->getOpt($cg->readPHPArgv(), "v", array ("verbose"));
	if ($getopt instanceof PEAR_Error)
		die ("Command line error: {$getopt->message}\n");

	list ($opts, $arguments) = $getopt;
	$options = array ();
	foreach ($opts as $opt) 
	{
		if ($opt[1] == NULL) 
		{
			@$options{$opt[0]} += 1;
		}
		else 
			$options{$opt[0]} = $opt[1];
	}
	$opt_verbose = @$options{"v"};



	if (count ($arguments) != 1)
		die ("usage: ./analyse.php FILENAME\n");

	$filename = $arguments[0];
	$base = basename ($filename, ".php");

	$clpa = "3rdparty/clpa/bin/clpa";
	if ($opt_verbose) $clpa .= " --debug add_rule";
	if ($opt_verbose == 2) $clpa .= " --debug eval_rule";

	$commands = array (
		// create .db files in the current directory
		"rm -f *.db",
		"src/phc --sdump=clar $filename > $base.clp",
		"src/phc --xdump=clar $filename | sed 's/^\s\+//' > $base.orig.xml", # indent them the same
		"$clpa --debug parse_warnings $base.clp",
#		"rm $base.clp",

		// Turn into CFG
		"$clpa src/analyse/do_cfg.clp",

 		# Run Optimizations
		"$clpa src/analyse/do_optimize.clp",

		# create CFG graphs (run after optimization so we can see the graphs)
		"rm -f *.ps",
		"for i in `ls *.dot`; do dot -Tps \$i -o`basename \$i .dot`.ps ; done",
		"rm -f *.dot",

		# Read back the optimized code
		"$clpa --quiet src/analyse/xml_unparser.clp > $base.xml",
		"callback: convert_to_xml",

		# Check it
#		"diff -u $base.orig.xml $base.new.xml",

		# Print the PHP code
		"src/phc --read-xml=mir --dump=mir $base.new.xml",
		"src/phc --read-xml=pst --generate-c $base.new.xml > $base.c",
		"src/phc --read-xml=pst --compile -o $base.out $base.new.xml",

		"./$base.out",


	);

	foreach ($commands as $command)
	{
		// callback
		if (preg_match ("/^callback: (.*)$/", $command, $match))
		{
			$match[1]();
		}
		else 
		{
			print "Command: $command\n";
			list ($out, $err, $exit) = complete_exec ($command);
			if ($out or $err or $exit)
				print "out: '$out', err: '$err', exit: '$exit'\n";
			if ($exit !== 0)
				die ("Bad exit code\n");
		}
	}

	function convert_to_xml ()
	{
		global $base, $filename;

		$input = file_get_contents ("$base.xml");

		// each Method starts with \"<MIR:Method>\n and ends with </MIR:Method>\n\"
		preg_match_all ("!\"(<MIR:Method>\n.*?</MIR:Method>)\n\"!sm", $input, $matches);


		// combine them with header and footer
		$header = 
			  "<?xml version=\"1.0\"?>\n"
			. "<MIR:PHP_script xmlns:MIR=\"http://www.phpcompiler.org/phc-1.1\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
			. "<attrs>\n"
			. "<attr key=\"phc.filename\"><string>".$filename."</string></attr>\n"
			. "</attrs>\n"
			. "<MIR:Statement_list>";
		$footer = "</MIR:Statement_list>\n</MIR:PHP_script>\n";

		$combined_xml = "$header\n" . join("\n", array_reverse ($matches[1])) . "\n$footer";
		file_put_contents ("$base.new.xml", $combined_xml);
	}


?>
