<?php

/**
 * This runs the first example from the j4p5 interpreter for JS.
 * The example is modified to not produce output.
 *
 * The j4p5 interpreter has been modified to never cache the compiled file. 
 * (Always override it)
 */


#-- Include the javascript library. This is a small file that may include other files as needed.
include_once "j4p5/js.php";

$code = file_get_contents("test/subjects/benchmarks/php-benchmarks/benchcli/tests/j4p5/data1.js");
#-- Execute the code. This automatically performs several speed optimizations whenever possible.
js::run($code);
?>
