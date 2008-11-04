<?
/* The Great Computer Language Shootout
   http://shootout.alioth.debian.org/
   contributed by Isaac Gouy 

   php -q objinst.php 1500000
	  --range 400000,700000,1000000,1500000
*/ 


class Toggle {
   var $_state;
   function Toggle($startState){ $this->_state = $startState; }
   function value(){ return $this->_state; }
   function activate(){ $this->_state = ! $this->_state; }
}


class NthToggle extends Toggle {
   var $_countMax;
   var $_count;

   function NthToggle($startState,$max){
      Toggle::Toggle($startState);
      $this->_countMax = $max; 
      $this->_count = 0;      
   }

   function activate(){ 
      $this->_count++;
      if ($this->_count >= $this->_countMax){
         $this->_state = ! $this->_state;
         $this->_count = 0;       
      }
   }
}


$n = ($argc == 2) ? $argv[1] : 1;

$toggle = new Toggle(TRUE);
for ($i=0; $i<5; $i++){
   $toggle->activate();
   $toggle->value() ? print "true\n" : print "false\n";   
}

for ($i=0; $i<$n; $i++) new Toggle(TRUE);
print "\n";

$ntoggle = new NthToggle(TRUE,3);
for ($i=0; $i<8; $i++){
   $ntoggle->activate();
   $ntoggle->value() ? print "true\n" : print "false\n";   
}

for ($i=0; $i<$n; $i++) new NthToggle(TRUE,3);

?>
