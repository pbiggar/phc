<? /* The Great Computer Language Shootout 
   http://shootout.alioth.debian.org/
   
   contributed by Isaac Gouy 
   
   php -q spectralnorm.php 10
	  --range 500,1500,2500
*/


function A($i, $j){
   return 1.0/(($i+$j)*($i+$j+1)/2+$i+1);  
}

function Av($n,$v){
   $Av = array();
   for ($i=0; $i<$n; $i++){
      $Av[$i] = 0;
      for ($j=0; $j<$n; $j++) $Av[$i] += A($i,$j)*$v[$j]; 
   }         
   return $Av;  
}

function Atv($n,$v){
   $Atv = array();
   for ($i=0; $i<$n; $i++){
      $Atv[$i] = 0;
      for ($j=0; $j<$n; $j++) $Atv[$i] += A($j,$i)*$v[$j];
   }         
   return $Atv;  
}

function AtAv($n,$v){        
   return Atv($n, Av($n,$v));  
}


$n = ($argc == 2) ? $argv[1] : 1;
$u = array_pad(array(), $n, 1);

for ($i=0; $i<10; $i++){
   $v = AtAv($n,$u);
   $u = AtAv($n,$v);
}

$vBv = 0;
$vv = 0;
for ($i=0; $i<$n; $i++){
   $vBv += $u[$i]*$v[$i]; 
   $vv += $v[$i]*$v[$i];
}
printf("%0.9f\n", sqrt($vBv/$vv));

?>
