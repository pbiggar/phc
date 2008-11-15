<?
/* The Great Computer Language Shootout
   http://shootout.alioth.debian.org/
   contributed by Isaac Gouy 

   php -q ary.php 3000-9000
*/ 


$n = ($argc == 2) ? $argv[1] : 1;

for ($i=0; $i<$n; $i++) $x[$i] = $i + 1;
    
$y = array_pad(array(),$n,0);
for ($k=0; $k<1000; $k++){
   $j = $n;
   while ($j--) $y[$j] += $x[$j];
}

printf("%d %d\n", $y[0], $y[$n-1]);

?>
