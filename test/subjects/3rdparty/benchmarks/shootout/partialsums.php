<? /* The Computer Language Shootout 
   http://shootout.alioth.debian.org/  
	  --range 25000,250000,2500000
   contributed by Isaac Gouy */

$n = $argv[1];

$a1 = 0.0; $a2 = 0.0; $a3 = 0.0; $a4 = 0.0; $a5 = 0.0; 
$a6 = 0.0; $a7 = 0.0; $a8 = 0.0; $a9 = 0.0;

$twothirds = 2.0/3.0;
$alt = -1.0;

for ($k=1; $k<=$n; $k++){
   $k2 = $k*$k;
   $k3 = $k2*$k;
   $sk = sin($k);
   $ck = cos($k);
   $alt = -$alt;

   $a1 += pow($twothirds,$k-1);
   $a2 += pow($k,-0.5);
   $a3 += 1.0/($k*($k+1.0));
   $a4 += 1.0/($k3 * $sk*$sk);
   $a5 += 1.0/($k3 * $ck*$ck);
   $a6 += 1.0/$k;
   $a7 += 1.0/$k2;
   $a8 += $alt/$k;
   $a9 += $alt/(2*$k -1);
}

printf("%.9f\t(2/3)^k\n", $a1);
printf("%.9f\tk^-0.5\n", $a2);
printf("%.9f\t1/k(k+1)\n", $a3);
printf("%.9f\tFlint Hills\n", $a4);
printf("%.9f\tCookson Hills\n", $a5);
printf("%.9f\tHarmonic\n", $a6);
printf("%.9f\tRiemann Zeta\n", $a7);
printf("%.9f\tAlternating Harmonic\n", $a8);
printf("%.9f\tGregory\n", $a9);

?>
