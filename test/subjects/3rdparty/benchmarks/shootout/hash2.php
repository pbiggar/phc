<?php
/* The Great Computer Language Shootout
   contributed by Isaac Gouy 

   php -q hash2.php 200
*/ 

//	  --range 50,100,150,200 

$n = ($argc == 2) ? $argv[1] : 1;

for ($i = 0; $i < 10000; $i++) 
   $hash1['foo_'.$i] = $i;

for ($i = $n; $i > 0; $i--) 
   foreach($hash1 as $key => $value) 
      if (isset($hash2[$key])){ 
         $hash2[$key] += $value; 
      } else { 
         $hash2[$key] = $value; 
      }
         
print "$hash1[foo_1] $hash1[foo_9999] $hash2[foo_1] $hash2[foo_9999]\n";

?>
