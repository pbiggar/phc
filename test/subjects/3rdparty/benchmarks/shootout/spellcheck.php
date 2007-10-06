<?php
/* The Great Computer Language Shootout
   http://shootout.alioth.debian.org/
   contributed by Isaac Gouy 

   php -q spellcheck.php < input.txt
	  --range 4,7,10,15 \
	  --inputfile ../../website/desc/spellcheck-input.txt --geninput
*/ 


$fp = fopen("Usr.Dict.Words", "r");
while ($line = fgets($fp, 128)) { $dict[chop($line)] = 1; }
fclose($fp);


$fp = fopen("php://stdin", "r");
while ($line = fgets($fp, 128)) {
    $line = chop($line);

    if (!isset($dict[$line])) print "$line\n";
}
fclose($fp);

?>
