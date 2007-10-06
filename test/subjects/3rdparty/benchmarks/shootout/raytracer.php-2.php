<? /* The Great Computer Language Shootout 
   http://shootout.alioth.debian.org/
  
   contributed by Isaac Gouy (PHP novice)
   
   php -q raytracer.php 32
*/


define("INFINITY", log(0) * -1.0);
define("EPSILON", 1.49012e-08);

define("LEVELS", 6);
define("SS", 4);


function &newVector($x,$y,$z){
   return array($x,$y,$z);          
}

function &add(&$a,&$b){
   return array($a[0]+$b[0], $a[1]+$b[1], $a[2]+$b[2]);      
}   

function &subtract(&$a,&$b){
   return array($a[0]-$b[0], $a[1]-$b[1], $a[2]-$b[2]);        
}   

function dot(&$a,&$b){
   return $a[0]*$b[0] + $a[1]*$b[1] + $a[2]*$b[2];      
}   

function &scaleBy(&$a,$s){
   return array($a[0]*$s, $a[1]*$s, $a[2]*$s);         
}        

function &normalize(&$a){
   return scaleBy($a,1.0/sqrt(dot($a,$a)));          
}


function &newRay($origin,$direction){
   return array("origin"=>$origin,"direction"=>$direction); 
}


function &newIntersectionPoint($distance,$normal){
   return array("distance"=>$distance,"normal"=>$normal); 
}



class Scene {

   function &sphereScene($level,&$center,$radius){
      $sphere = new Sphere($center,$radius);
      if ($level==1){
         return $sphere;
      }
      else {
         $scene = new Group( new Sphere($center,3.0*$radius) );
         $scene->add($sphere);
         $rn = 3.0*$radius / sqrt(12.0);
         
         for ($dz=-1; $dz<=1; $dz+=2){
            for ($dx=-1; $dx<=1; $dx+=2){   
            
               $c2 = newVector(
                    $center[0] - $dx*$rn
                  , $center[1] + $rn
                  , $center[2] - $dz*$rn
                  );    
                  
               $scene->add( Scene::sphereScene($level-1, $c2, $radius/2.0) );                          
            }            
         }   
         return $scene;
      }     
   } 
         
   function traceRay(&$ray,&$light){   
      $p = $this->intersect($ray,
         newIntersectionPoint(INFINITY, newVector(0.0, 0.0, 0.0)) );                                  
      if (is_infinite($p["distance"])){ return 0.0; }
                                                  
      $greyscale = -1.0 * dot($p["normal"],$light);
      if ($greyscale <= 0.0){ return 0.0; }   
      
      $rayOrigin = $ray["origin"];
      $scaledDirection = scaleBy($ray["direction"], $p["distance"]);
      $scaledNormal = scaleBy($p["normal"],EPSILON);
      $o = add($rayOrigin,$scaledDirection);
      $o = add($o,$scaledNormal);          
              
      $v = newVector(0.0, 0.0, 0.0);      
      $shadowRay = newRay($o, subtract($v,$light));      
      $shadowp = $this->intersect(
         $shadowRay, newIntersectionPoint(INFINITY, $p["normal"]) );      
          
      if (is_infinite($shadowp["distance"])){ return $greyscale; }  
      else { return 0.0; }         
   }                                                           
}


// a leaf node in the scene tree
class Sphere extends Scene {
   var $center, $radius; 
   
   function Sphere($center,$radius){   
      $this->center = $center;
      $this->radius = $radius;               
   }     
   
   function distance(&$ray){
      $v = subtract($this->center,$ray["origin"]);                      
      $b = dot($v,$ray["direction"]);                      
      $disc = $b*$b - dot($v,$v) + $this->radius*$this->radius;       
      if ($disc < 0.0){ return INFINITY; } // No intersection
        
      $d = sqrt($disc);   
      $t1 = $b + $d;  
      if ($t1 < 0.0){ return INFINITY; }             
              
      $t2 = $b - $d;     
      if ($t2 > 0.0){ return $t2; } else { return $t1; }                     
   }   
      
   function intersect(&$ray,&$p){      
      $d = $this->distance($ray);                    
      if ($d < $p["distance"]){                                
         $rayOrigin = $ray["origin"];
         $rayDirection = $ray["direction"];
         $scaledDirection = scaleBy($rayDirection,$d);  
                
         $v = add($rayOrigin,subtract($scaledDirection,$this->center ));                           
         $p = newIntersectionPoint($d, normalize($v));         
      }             
      return $p; 
   }                           
}


// non-leaf node in the scene tree
class Group extends Scene {
   var $bound, $scenes;        
       
   function Group($bound){
      $this->bound = $bound;  
      $this->scenes = array();      
   }           
   
   function intersect(&$ray,&$p){     
      if (($this->bound -> distance($ray)) < $p["distance"]){                         
         foreach ($this->scenes as $each){
            $p = $each->intersect($ray,$p);                  
         }      
      }           
      return $p; 
   }    
      
   function add($s){  
      array_unshift($this->scenes, $s);   
   }                      
}


////////////////////////////////////////////////////////////////////

$n = ($argc == 2) ? $argv[1] : 1;

$scene = Scene::sphereScene(LEVELS, newVector(0.0, -1.0, 0.0), 1.0);

printf("P5\n%d %d\n255\n", $n,$n);

for ($y=$n-1; $y>=0; --$y){
   for ($x=0; $x<$n; ++$x){
   
      $greyscale = 0.0;
      for ($dx=0; $dx<SS; ++$dx){
         for ($dy=0; $dy<SS; ++$dy){   
         
            $v = newVector(
                 $x + ($dx/(double)SS) - ($n/2.0)
               , $y + ($dy/(double)SS) - ($n/2.0)
               , $n );                                                       
                              
            $ray = newRay(newVector(0.0, 0.0, -4.0), normalize($v));  
                                                                  
            $u = newVector(-1.0, -3.0, 2.0);                          
            $greyscale += $scene->traceRay($ray, normalize($u));                                    
         }
      }          
      echo chr( 0.5 + 255.0*$greyscale/(double)(SS*SS) );                                          
   }
}           
?>