<? /* The Great Computer Language Shootout 
   http://shootout.alioth.debian.org/
   
   contributed by Isaac Gouy 
   
   php -q harmonic.php 1000
	  --range 6000000,8000000,10000000
*/


$n = ($argc == 2) ? $argv[1] : 600000;

$partialSum = 0.0;
for ($i=1; $i<=$n; $i++) $partialSum += 1.0 / $i;

printf("%.9f\n", $partialSum);
?>
