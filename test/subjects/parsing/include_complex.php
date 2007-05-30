<?php

	# note that this test will not work on cygwin, because of incorrect PHP
	# behaviour, specifically that PHP includes using \\ on cygwin (even though
	# it opens files using /

// the following not being included
//- files that arent found
//- files that dont parse
//- files with return statements arent
//- files with return statements in their classes are ok                       
//- include_once the second time.

// the following issuing errors
//- the parse failing                                                          
//- class redefinition being spotted
//- method redefinition being spotted
//- the file not being found for require

// warnings on
//- files which arent included
//- the file not being found


	# there should be no require, include, include_once or require_once
	# statements in this file once its passed through phc with
	# --compile-time-includes

	function fail($file, $line, $reason)
	{
		print "Failure: '$reason' on $file:$line\n";
	}


	# checks variables are overwritten

	$a1 = "old value";
	$a2 = "my old value";

	echo "about to include included_var_overwrite.php\n";
	include "included_var_overwrite.php";

	var_dump($a1);
	var_dump($a2);

	if ($a1 == "old value" or $a2 == "my old value")
	{
		fail(__FILE__, __LINE__, "var overwrite");
	}




	# checks classes are added

	echo "about to include included_classes_and_functions.php\n";
	include "included_classes_and_functions.php";

	$b = new B();
	var_dump($b);
	$b = $b->b();
	var_dump($b);
	if(!$b)
	{
		fail(__FILE__, __LINE__, "included class");
	}
	$b = b();
	var_dump($b);
	if(!$b)
	{
		fail(__FILE__, __LINE__, "included function");
	}
		



	# include a file with return statements in the classes
	# if this fails, the grep will remove it

	echo "about to include included_classes_with_return_values.php\n";
	include "included_classes_with_return_values.php";

	$c = new C();
	var_dump($c);
	$c = $c->cc();
	var_dump($c);
	if ($c != 7)
	{
		fail(__FILE__, __LINE__, "class with return value");
	}



	# files with directory levels

	echo "about to include include_dir/../../bugs/././../horrible/invocation_priorities.php\n";
	include "include_dir/../../bugs/./../horrible/invocation_priorities.php";

	var_dump($f);
	var_dump($a);
	var_dump($x);
	if(!$x)
	{
		fail(__FILE__, __LINE__, "directory levels");
	}


	# files from the current working directory, with ./

	$x = "zzz";
	$y = "zzz";
	$xx = "zzz";
	echo "about to include ./test/subjects/horrible/obfuscated_foreach.php\n";
	include "./test/subjects/horrible/obfuscated_foreach.php";

	var_dump($x);
	var_dump($y);
	var_dump($xx);
	if(!$xx)
	{
		fail(__FILE__, __LINE__, "current working directory");
	}



	# files from the current working directory
	
	echo "about to include test/subjects/horrible/obfuscated_foreach.php\n";
	include "test/subjects/horrible/obfuscated_foreach.php";

	var_dump($x);
	var_dump($y);
	var_dump($xx);
	if(!$xx)
	{
		fail(__FILE__, __LINE__, "current working directory");
	}


	# including files with correct __FILE__
	# Note: this test taken out. We dont want to process file, merely include it
	# in the tree	


	# calling files with include
	
	echo "about to include included_recursive1.php\n";
	require "included_recursive1.php";
	
	var_dump($f);
	if($f !== 26)
	{
		fail(__FILE__, __LINE__, "recursive include");
	}


	# including within a function

	function g()
	{
		$a1 = "old string";
		$a2 = "old string";
	
		echo "about to include included_var_overwrite.php\n";	
		require "included_var_overwrite.php";

		var_dump($a1);
		var_dump($a2);

		if ($a1 == "old value" or $a2 == "my old value")
		{
			fail(__FILE__, __LINE__, "var overwrite within function");
		}
	}
	g();

	# including within a class

	class H
	{
		function H()
		{
			echo "H\n";
		}

		function g()
		{
			$a1 = "old string";
			$a2 = "old string";

			echo "about to include included_var_overwrite.php\n";
			include "included_var_overwrite.php";

			if ($a1 == "old value" or $a2 == "my old value")
			{
				fail(__FILE__, __LINE__, "var overwrite within class");
			}
		}
	}
	$h = new H();
	var_dump($h);
	$h = $h->g();
	var_dump($h);


	# the included file using varaibles from this file
	$i1 = "some value";
	$i2 = "another value";

	echo "about to include included_use_existing_vars.php\n";
	include "included_use_existing_vars.php";
	
	# the included file using functions from this file

	echo "about to include included_use_vars_in_function.php\n";
	include "included_use_vars_in_function.php";

	$j = j(1,2);
	var_dump($j);

	# the included file using classes from this file
	
	echo "about to include included_use_vars_in_classes.php\n";
	include "included_use_vars_in_classes.php";

	$k = new K();
	var_dump($k);
	$k = $k->kk();
	var_dump($k);


?>
