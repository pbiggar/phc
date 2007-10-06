<?php /* The Computer Language Shootout
   http://shootout.alioth.debian.org/
   contributed by Peter Baltruschat
*/

function primes($size)
{
   $flags = array_fill(0, ($size>>5) + 1, ~0);
   $count = 0;
   for($i = 2; $i < $size; ++$i)
   {
      $offset = $i>>5;
      $mask = 1<<($i - ($offset<<5));
      if($flags[$offset] & $mask)
      {
         ++$count;
         for($j = $i<<1; $j <= $size; $j += $i)
         {
            $offset = $j>>5;
            $mask = 1<<($j - ($offset<<5));
            if($flags[$offset] & $mask)
            {
               $flags[$offset] ^= $mask;
            }
         }
      }
   }
   unset($flags);
   printf("Primes up to %8d %8d\n", $size, $count);
}

$n = ($argv[1] != '') ? $argv[1] : $_GET['n'];

$size = 10000 * (1<<$n);
primes($size);
primes($size>>1);
primes($size>>2);
?>
