<?php

	// hand reduced from zend bench.php. This found memory coruption.

function simple() { }

function getmicrotime() { $t = gettimeofday(); }

function start_test() { return getmicrotime(); }

start_test();
simple();
$x = $y + $z;
?>
