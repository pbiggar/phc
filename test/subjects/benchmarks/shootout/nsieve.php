<? /* The Computer Language Shootout 
   http://shootout.alioth.debian.org/   
   contributed by Isaac Gouy   
   php -q nsieve.php 2
	  --range 7,8,9
*/


function NSieve($m, &$isPrime){
   for ($i=2; $i<=$m; $i++) $isPrime[$i] = TRUE;
   $count = 0;

   for ($i=2; $i<=$m; $i++){
      if ($isPrime[$i]){
         for ($k=$i+$i; $k<=$m; $k+=$i) $isPrime[$k] = FALSE;
         $count++;
      }
   }
   return $count;
}


$n = ($argc == 2) ? $argv[1] : 1;
$flags = array();

$m = (1<<$n)*10000;
printf("Primes up to %8d %8d\n", $m, NSieve($m, $flags));

$m = (1<<$n-1)*10000;
printf("Primes up to %8d %8d\n", $m, NSieve($m, $flags));

$m = (1<<$n-2)*10000;
printf("Primes up to %8d %8d\n", $m, NSieve($m, $flags));
?>
