<? /* The Great Computer Language Shootout 
   http://shootout.alioth.debian.org/
   
   contributed by Isaac Gouy 
   
   php -q takfp.php 10

	  --range 8,9,10
*/

function Takfp($x, $y, $z){
   if ($y>=$x){ 
      return $z; 
   }
   else {
      return Takfp( Takfp($x-1.0,$y,$z), Takfp($y-1.0,$z,$x),  Takfp($z-1.0,$x,$y));
   }   
}

$n = ($argc == 2) ? $argv[1] : 1;
printf("%.1f\n", Takfp($n*3.0,$n*2.0,$n*1.0));

?>
