<? /* The Great Computer Language Shootout 
   http://shootout.alioth.debian.org/
   
   contributed by Isaac Gouy (PHP novice)
   
   php -q dispatch.php 10
	  --range 200000,600000,1000000
*/


class BottleState {
   function Next($b){}
   function Tag(){}
   
   function InitialState(){ global $Empty; return $Empty; }   
}

class EmptyState extends BottleState {
   function Next($b){ global $Full; $b->State($Full); }
   function Tag(){ return 1; }
}

class FullState extends BottleState  {
   function Next($b){ global $Sealed; $b->State($Sealed); }
   function Tag(){ return 2; }
}

class SealedState extends BottleState  {
   function Next($b){ global $Empty; $b->State($Empty); }
   function Tag(){ return 3; }
}

$Empty = new EmptyState;
$Full = new FullState;
$Sealed = new SealedState;


class PressurizedBottleState extends BottleState {
   function InitialState(){  global $UnpressurizedEmpty; return $UnpressurizedEmpty; }  
}

class UnpressurizedEmptyState extends PressurizedBottleState {
   function Next($b){ global $UnpressurizedFull; $b->State($UnpressurizedFull); }
   function Tag(){ return 4; }
}

class UnpressurizedFullState extends PressurizedBottleState {
   function Next($b){ global $PressurizedUnsealed; $b->State($PressurizedUnsealed); }
   function Tag(){ return 5; }
}

class PressurizedUnsealedState extends PressurizedBottleState {
   function Next($b){ global $PressurizedSealed; $b->State($PressurizedSealed); }
   function Tag(){ return 6; }
}

class PressurizedSealedState extends PressurizedBottleState {
   function Next($b){ global $UnpressurizedEmpty; $b->State($UnpressurizedEmpty); }
   function Tag(){ return 7; }
}

$UnpressurizedEmpty = new UnpressurizedEmptyState;
$UnpressurizedFull = new UnpressurizedFullState;
$PressurizedUnsealed = new PressurizedUnsealedState;
$PressurizedSealed = new PressurizedSealedState;


class Bottle {
   var $bottleState, $id;
      
   function Bottle($id){
      $this->id = $id;
      $this->bottleState = $this->InitialState();   
   } 
   
   function State($s){
      $this->bottleState = $s;
   }     

   function Cycle(){
      $this->Fill(); $this->Seal(); $this->Empty_();
   }   
   
   function InitialState(){
      return BottleState::InitialState();
   }      

   function Fill(){
      $this->bottleState ->Next($this);
   } 
         
   function Seal(){
      $this->bottleState ->Next($this);
   }
      
   function Empty_(){
      $this->bottleState ->Next($this);
   }    
   
   function Check($c){
      return $this->bottleState->Tag() + $this->id + $c;
   }          
}


class PressurizedBottle extends Bottle {

   function PressurizedBottle($id){
      Bottle::Bottle($id);    
   }
      
   function InitialState(){
      return PressurizedBottleState::InitialState();
   }  

   function Cycle(){
      $this->Fill(); $this->Pressurize(); $this->Seal(); $this->Empty_();
   } 
   
   function Pressurize(){
      $this->bottleState ->Next($this);
   }    
}


function BottleCheck($a1, $a2, $a3, $a4, $a5, $i){
   $a1->Cycle(); $a2->Cycle(); $a3->Cycle(); $a4->Cycle(); $a5->Cycle();
   $c = $i % 2;
   return $a1->Check($c) + $a2->Check($c) + $a3->Check($c) 
      + $a4->Check($c) + $a5->Check($c);
}


$n = ($argc == 2) ? $argv[1] : 1;

$b1 = new Bottle(1); $b2 = new Bottle(2);
$b3 = new Bottle(3); $b4 = new Bottle(4);
$b5 = new Bottle(5); $b6 = new Bottle(6);
$b7 = new Bottle(7); $b8 = new Bottle(8);
$b9 = new Bottle(9); $b0 = new Bottle(0);

$p1 = new PressurizedBottle(1); $p2 = new PressurizedBottle(2);
$p3 = new PressurizedBottle(3); $p4 = new PressurizedBottle(4);
$p5 = new PressurizedBottle(5); $p6 = new PressurizedBottle(6);
$p7 = new PressurizedBottle(7); $p8 = new PressurizedBottle(8);
$p9 = new PressurizedBottle(9); $p0 = new PressurizedBottle(0);

$check = 0;
for ($i=1; $i<=$n; $i++){
   $check += BottleCheck($b1,$b2,$b3,$b4,$b5,$i);
   $check += BottleCheck($b6,$b7,$b8,$b9,$b0,$i);

   $check += BottleCheck($p1,$p2,$p3,$p4,$p5,$i);
   $check -= BottleCheck($p6,$p7,$p8,$p9,$p0,$i);
}
print "$check";
?>
