<? /* The Great Computer Language Shootout 
   http://shootout.alioth.debian.org/
   
   contributed by Isaac Gouy 
   
   php -q pidigits.php 27
	  --range 600,800,1000
*/


class Transformation {
   var $q, $r, $s, $t, $k;

   function Transformation($q, $r, $s, $t){
      $this->q = $q;
      $this->r = $r;      
      $this->s = $s;
      $this->t = $t;               
   }
   
   function Unity(){
      return new Transformation("1", "0", "0", "1");              
   }   
   
   function Zero(){
      return new Transformation("0", "0", "0", "0");              
   }      
   
      
   function Compose($a){
      $qq = bcmul($this->q, $a->q);
      $qrrt = bcadd(bcmul($this->q, $a->r), bcmul($this->r, $a->t));
      $sqts = bcadd(bcmul($this->s, $a->q), bcmul($this->t, $a->s));
      $srtt = bcadd(bcmul($this->s, $a->r), bcmul($this->t, $a->t));   
      return new Transformation($qq, $qrrt, $sqts, $srtt);
   }
   
   function Extract($j){
      $bigj = strval($j);
      $qjr = bcadd(bcmul($this->q, $bigj), $this->r);
      $sjt = bcadd(bcmul($this->s, $bigj), $this->t);
      $d = bcdiv($qjr, $sjt);
      return floor($d);
   }
      
   function Next(){ 
      $this->k = $this->k + 1;
      $this->q = strval($this->k);
      $this->r = strval(4*$this->k + 2);
      $this->s = "0";
      $this->t = strval(2*$this->k + 1);
      return $this;      
   }                
}



class PiDigitStream {
   var $z, $x, $inverse;

   function PiDigitStream(){
      $this->z = Transformation::Unity();
      $this->x = Transformation::Zero();      
      $this->inverse = Transformation::Zero();   
   }
   
   function Produce($j){
      $i = $this->inverse;
      $i->q = "10";
      $i->r = strval(-10*$j);
      $i->s = "0";
      $i->t = "1";
      return $i->Compose($this->z);
   }   

   function Consume($a){
      return $this->z ->Compose($a);  
   }
   
   function Digit(){
      return $this->z ->Extract(3);  
   }  
   
   function IsSafe($j){
      return $j == ($this->z ->Extract(4));  
   }    

   function Next(){
      $y = $this->Digit();
      if ($this->IsSafe($y)){
         $this->z = $this->Produce($y);
         return $y;
      } else {
         $this->z = $this->Consume($this->x ->Next());
         return $this->Next();      
      }
   } 
}


$n = ($argc == 2) ? $argv[1] : 1;
$i = 0;
$length = 10;
$pidigit = new PiDigitStream;

while ($n > 0){
   if ($n < $length){
      for ($j=0; $j<$n; $j++) printf("%d",$pidigit->Next());
      for ($j=$n; $j<$length; $j++)  print " ";
      $i += $n;
   } else {
      for ($j=0; $j<$length; $j++) printf("%d",$pidigit->Next());
      $i += $length;   
   }
   print "\t:$i\n";
   $n -= $length;
}
?>
