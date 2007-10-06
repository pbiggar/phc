<?
/* The Great Computer Language Shootout
   http://shootout.alioth.debian.org/
   contributed by Isaac Gouy 

          --range 100,6000,9000,12000 \
	  --inputfile ../../website/desc/regexmatch-input.txt

   php -q regexmatch.php 12000 < input.txt
*/ 


$regex = "/" 
         ."(?:^|[^\d\(])" 
         ."(?:\((\d\d\d)\)|(\d\d\d))"    
         ."[ ]" 
         ."(\d\d\d)"
         ."[ -]"
         ."(\d\d\d\d)"
         ."\D" 
         ."/";


$n = ($argc == 2) ? $argv[1] : 1;

$phoneNumbers = file("php://stdin");
$last = sizeof($phoneNumbers)-1;
$count = 0;

while ($n--)
   for ($i=0; $i<$last; $i++){
      preg_match($regex, $phoneNumbers[$i], $match);
      if (($n == 0) && $match){ 
         $m = $match[1] ? $match[1] : $match[2];
         printf("%d: (%s) %s-%s\n", ++$count, $m, $match[3], $match[4]);
         }
   }

?>
