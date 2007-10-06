<? /* The Computer Language Shootout 
   http://shootout.alioth.debian.org/  
   contributed by Isaac Gouy 
	  --range 3,7,11
*/

function ack($m, $n){
   if($m == 0) return $n+1;
   if($n == 0) return ack($m-1, 1);
   return ack($m - 1, ack($m, ($n - 1)));
}

function fib($n){ 
   if($n < 2) { return 1; }
   else { return fib($n - 2) + fib($n - 1); }
}

function tak($x,$y,$z){
   if($y < $x){ return tak( tak($x-1,$y,$z), tak($y-1,$z,$x), tak($z-1,$x,$y)); }
   else { return $z; }
}

$n = $argv[1]; 
echo "Ack(3,$n): ", ack(3,$n),"\n";
printf("Fib(%.1f): %.1f\n", 27.0+$n, fib(27.0+$n));
$n--; printf("Tak(%d,%d,%d): %d\n", 3*$n,2*$n,$n, tak(3*$n,2*$n,$n));

printf("Fib(3): %d\n", fib(3));
printf("Tak(3.0,2.0,1.0): %.1f\n", tak(3.0,2.0,1.0));
?>
