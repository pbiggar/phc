<?php

/* The Computer Language Shootout
 * http://shootout.alioth.debian.org/
 *
 * contributed by Charles G.
 * modified by Isaac Gouy
 */

function nsieve($m)
{
    $flags = ' ';
    $flags[$m] = ' ';
    
    $count = 0;
    for ($i = 2; $i < $m; ++$i)
        if ($flags[$i] == ' ') {
            ++$count;
            for ($j = $i << 1; $j < $m; $j += $i)
                $flags[$j] = 'x';
        }

    printf("Primes up to %8d %8d\n", $m, $count);

}

$m = $argv[1];
for ($i = 0; $i < 3; $i++)
    nsieve(10000 << ($m-$i));
?>
