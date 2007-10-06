<?php

/* The Computer Language Shootout
   http://shootout.alioth.debian.org/
   contributed by Michael Hansen
*/

define(BPC, 32);
define(FLAG_MAX, 0xFFFFFFFF);

function primes($n) {
    $size = 10000 * pow(2, $n);
    $flags = array();
    $count = 0;
    for ($i=0; $i<($size/BPC + 1); $i++)
        $flags[$i] = FLAG_MAX;

    for($prime=2; $prime<$size; $prime++) {
        $offset = $prime / BPC;
        $mask = pow(2, $prime % BPC);
        if (($flags[$offset] & $mask) != 0) {
            $count++;
            for ($i=($prime*2); $i<=$size; $i += $prime) {
                $offset = $i / BPC;
                $mask = pow(2, $i % BPC);
                if (($flags[$offset] & $mask) != 0)
                    $flags[$offset] ^= $mask;
            }
        }
    }

    printf("Primes up to %8d %8d\n", $size, $count);
}

$n = ($argv[1] != '') ? $argv[1] : 1;
for ($i=0; $i<3; $i++) primes($n-$i);

?>
