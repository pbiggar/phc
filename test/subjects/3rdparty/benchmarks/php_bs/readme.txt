John's PHP Benchmarking Suite (PHP BS)
======================================

This is a set of benchmark programs for PHP4. All scripts perform 2 benchmarks. A reference
benchmark, and a 2nd benchmark. All benchmarks are compared with the reference benchmark,
so we can tell that benchmark X is perhaps 3.4 times faster than benchmark Y.


Installation
============
To run, just unpack in a web server directory, and open up index.php from your web browser.

To save a set of HTML results, turn caching on by going to config.inc.php and change 
$CACHE to 1. Then all results that you view are saved in _cache. An index.php is 
also generated. Just rename _cache as appropriate, eg. _PHP420_RH9_P4-2.0GHz.

Results
=======
All cached results for PHP 4.0.6 and 4.3.3 have Zend Optimizer installed.

Creating Benchmarks
===================

Benchmarks are sorted by directory. Each benchmark directory is automatically read by 
index.php, and all benchmarks in a directory are executed together.

Every benchmark script will perform 2 benchmarks and compare the results of the 2 benchmarks. 
This makes it easier to do relative comparisons. The 1st benchmark is defined in bench1() and 
the 2nd in bench2().

Benchmark functions are executed 1000 times by default, and the total time run is measured, 
less the time to execute an empty function 1000 times.

Special metadata is stored in the benchmark .php file which is used to annotate the benchmark. 
The metadata is of the form

//~~ TITLE OF BENCHMARK, TITLE OF BENCH1, TITLE OF BENCH2


Here is a simple benchmark script:

<?php

include_once("../init.inc.php");

// METADATA THAT IS READ BY ../bench.php:
//~~ Reading CONSTANTS versus Global Variables, Constants, Globals

//================================================ INIT

define('CONSTANT',1);
$CONSTANT = 1;

//================================================ TEST CODE

function bench1() 
{
	return CONSTANT+CONSTANT+CONSTANT;
}

function bench2() 
{
global $CONSTANT;

	return $CONSTANT+$CONSTANT+$CONSTANT;
}

//================================================ BENCHMARK!

include_once("../bench.inc.php");

?>



(c) 2003, 2004 John Lim jlim#natsoft.com.my
Licensed under BSD style license.