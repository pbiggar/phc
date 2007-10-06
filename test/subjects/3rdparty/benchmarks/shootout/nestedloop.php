<?php
/* The Great Computer Language Shootout
   http://shootout.alioth.debian.org/
   contributed by Isaac Gouy 

   php -q nestedloop.php 18
	  --range 8,12,16,18
*/ 


$n = ($argc == 2) ? $argv[1] : 1;

$x = 0;
$a = $n; while ($a--){
   $b = $n; while ($b--){
      $c = $n; while ($c--){
         $d = $n; while ($d--){
            $e = $n; while ($e--){
               $f = $n; while ($f--) 
                  $x++; }}}}}
 
print "$x\n";

?>
