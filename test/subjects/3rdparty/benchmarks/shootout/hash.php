<?php
/* The Great Computer Language Shootout
   http://shootout.alioth.debian.org/
   contributed by Isaac Gouy 

   php -q hash.php 100000
*/ 

//	  --range 40000,60000,80000,100000

$n = ($argc == 2) ? $argv[1] : 1;

$i = 0; while ($i++ < $n) $x[dechex($i)] = $i; 

$count = 0;
while ($n--) 
    if (isset($x[$n])) $count++; 

print "$count\n";

?>
