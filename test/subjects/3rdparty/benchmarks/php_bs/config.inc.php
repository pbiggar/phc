<?php

/*
	1.01 
	functions: short vs long function name test
	algorithms: parse_ini_file vs assoc array test
	
	1.00 29 Feb 2003
	initial release after redesign
*/

$VERSION = '1.01';

//===================================
// NUMBER OF SECONDS TO CACHE RESULTS
// -1 = always use _cache copy
//  0 = never use _cache copy
// >0 = cache for $CACHE secs
$CACHE = 0;


function Copyright()
{
global $VERSION;

	return "<font size=1>(c) 2003-2004 John Lim 
	<a href=http://phplens.com/benchmark_suite/>PHP Benchmark Suite (PHP BS $VERSION)</a>. 
	Sponsored by <a href=http://natsoft.com/>Natsoft</a> and <a href=http://ormestech.com/>Ormes</a>.</font>";
}

?>