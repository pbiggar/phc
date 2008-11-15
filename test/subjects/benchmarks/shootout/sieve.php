<?php
/* The Great Computer Language Shootout
   http://shootout.alioth.debian.org/
   contributed by Isaac Gouy 

   php -q sieve.php 9000
--range 300,600,900,1200 
*/ 


$n = ($argc == 2) ? $argv[1] : 1;

$stop = 8192;
$count = 0;

while ($n-- > 0) {
   $count = 0;
   $i = $stop; while ($i--) $isPrime[$i] = 1;

   $i = 2; while ($i++ < $stop){
      if ($isPrime[$i]){
         for ($k=$i+$i; $k<=$stop; $k+=$i) $isPrime[$k] = 0;
         $count++;
      }
   }
} 
print "Count: $count\n";

?>
