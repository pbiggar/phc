<?
/* The Great Computer Language Shootout
      http://shootout.alioth.debian.org/
      contributed by Isaac Gouy 

 	  --range 25,75,125,200 \
	  --inputfile ../../website/desc/moments-input.txt --geninput
     php -q moments.php < in.txt > out.txt
*/ 


$numbers = file("php://stdin");

$n = sizeof($numbers);
$sum = 0.0;
for ($i=0; $i<$n; $i++){
   $numbers[$i] = doubleval($numbers[$i]);
   $sum += $numbers[$i];
}

$dev = $adev = $variance = $skew = $kurtosis = 0.0; 
$mean = $sum / $n;

for ($i=0; $i<$n; $i++){
   $dev = $numbers[$i] - $mean;   
   $adev += abs($dev);   
   $variance += ($dev2 = $dev * $dev); 
   $skew += $dev2 * $dev;
   $kurtosis += $dev2 * $dev2;
}

$adev /= $n;   
$variance /= $n-1;     
$sdev = sqrt($variance);

if ($variance != 0.0){
   $skew /= $n * $variance * $sdev;
   $kurtosis = $kurtosis/($n * $variance * $variance) - 3.0;
}

sort($numbers);
$mid = $n / 2;
$median = ($n % 2 != 0) ?
   $numbers[$mid] : ($numbers[$mid] + $numbers[$mid-1]) / 2.0;

printf("n:                  %d\n", $n);
printf("median:             %0.6f\n", $median);
printf("mean:               %0.6f\n", $mean);
printf("average_deviation:  %0.6f\n", $adev);
printf("standard_deviation: %0.6f\n", $sdev);
printf("variance:           %0.6f\n", $variance);
printf("skew:               %0.6f\n", $skew);
printf("kurtosis:           %0.6f\n", $kurtosis);

?>
