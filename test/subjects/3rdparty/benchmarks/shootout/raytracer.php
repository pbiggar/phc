<? /* The Great Computer Language Shootout 
   http://shootout.alioth.debian.org/
   
   contributed by Isaac Gouy (PHP novice)
   
   php -q raytracer.php 32
	  --range 20,40,80,160
*/


define("INFINITY", log(0) * -1.0);
define("EPSILON", 1.49012e-08);

define("LEVELS", 6);
define("SS", 4);

class Vector {
   var $x, $y, $z; 
   
   function Vector($x,$y,$z){
      $this->x = $x; $this->y = $y; $this->z = $z;            
   }
   
   function plus(&$b){
      return new Vector(
         $this->x + $b->x, $this->y + $b->y, $this->z + $b->z );      
   }   
   
   function minus(&$b){
      return new Vector(
         $this->x - $b->x, $this->y - $b->y, $this->z - $b->z );        
   }   
   
   function dot(&$b){
      return ($this->x * $b->x) + 
         ($this->y * $b->y) + ($this->z * $b->z);      
   }   
   
   function scaledBy($s){
      return new Vector($this->x * $s, $this->y * $s, $this->z * $s);           
   }        
   
   function normalized(){
      return $this->scaledBy(1.0/sqrt( $this->dot($this) ));          
   }      
                        
}


class Ray {
   var $origin, $direction; 
   
   function Ray(&$origin,&$direction){
      $this->origin = $origin;
      $this->direction = $direction;                 
   }                           
}


class IntersectionPoint {
   var $distance, $normal; 
   
   function IntersectionPoint($distance,&$normal){
      $this->distance = $distance;
      $this->normal = $normal;         
   }                            
}


class Scene {

   function sphereScene($level,&$center,$radius){
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
            
               $c2 = new Vector(
                    $center->x - $dx*$rn
                  , $center->y + $rn
                  , $center->z - $dz*$rn
                  );    
                  
               $scene->add( Scene::sphereScene($level-1, $c2, $radius/2.0) );                          
            }            
         }   
         return $scene;
      }     
   } 
         
   function traceRay(&$ray,&$light){   
      $p = $this->intersect($ray,
         new IntersectionPoint(INFINITY, new Vector(0.0, 0.0, 0.0)) );                            
      if (is_infinite($p->distance)){ return 0.0; }
                             
      $greyscale = -1.0 * ($p->normal->dot($light));
      if ($greyscale <= 0.0){ return 0.0; }   
      
      $rayOrigin = $ray->origin;
      $scaledDirection = $ray->direction->scaledBy($p->distance);
      $scaledNormal = $p->normal->scaledBy(EPSILON);
      $o = $rayOrigin->plus($scaledDirection);
      $o = $o->plus($scaledNormal);          
              
      $v = new Vector(0.0, 0.0, 0.0);      
      $shadowRay = new Ray($o, $v->minus($light));      
      $shadowp = $this->intersect(
         $shadowRay, new IntersectionPoint(INFINITY, $p->normal) );      
          
      if (is_infinite($shadowp->distance)){ return $greyscale; }  
      else { return 0.0; }         
   }                                                           
}


// a leaf node in the scene tree
class Sphere extends Scene {
   var $center, $radius; 
   
   function Sphere(&$center,$radius){   
      $this->center = $center;
      $this->radius = $radius;               
   }     
   
   function distance(&$ray){
      $v = $this->center -> minus($ray->origin);                      
      $b = $v->dot($ray->direction);                      
      $disc = $b*$b - $v->dot($v) + $this->radius*$this->radius;       
      if ($disc < 0.0){ return INFINITY; } // No intersection
        
      $d = sqrt($disc);   
      $t1 = $b + $d;  
      if ($t1 < 0.0){ return INFINITY; }             
              
      $t2 = $b - $d;     
      if ($t2 > 0.0){ return $t2; } else { return $t1; }                     
   }   
      
   function intersect(&$ray,&$p){      
      $d = $this->distance($ray);              
      if ($d < $p->distance){                                     
         $rayOrigin = $ray->origin;
         $rayDirection = $ray->direction;
         $scaledDirection = $rayDirection->scaledBy($d);  
                
         $v = $rayOrigin->plus($scaledDirection->minus( $this->center ));                           
         $p = new IntersectionPoint($d, $v->normalized());         
      }             
      return $p; 
   }                           
}


// non-leaf node in the scene tree
class Group extends Scene {
   var $bound, $scenes;        
       
   function Group(&$bound){
      $this->bound = $bound;  
      $this->scenes = array();      
   }           
   
   function intersect(&$ray,&$p){     
      if (($this->bound -> distance($ray)) < $p->distance){                         
         foreach ($this->scenes as $each){
            $p = $each->intersect($ray,$p);                  
         }      
      }           
      return $p; 
   }    
      
   function add(&$s){  
      array_unshift($this->scenes, $s);   
   }                      
}

////////////////////////////////////////////////////////////////////

$n = ($argc == 2) ? $argv[1] : 1;

$scene = Scene::sphereScene(LEVELS, new Vector(0.0, -1.0, 0.0), 1.0);

printf("P5\n%d %d\n255\n", $n,$n);

for ($y=$n-1; $y>=0; --$y){
   for ($x=0; $x<$n; ++$x){
   
      $greyscale = 0.0;
      for ($dx=0; $dx<SS; ++$dx){
         for ($dy=0; $dy<SS; ++$dy){   
         
            $v = new Vector(
                 $x + ($dx/(double)SS) - ($n/2.0)
               , $y + ($dy/(double)SS) - ($n/2.0)
               , $n );                                                       
                             
            $ray = new Ray(new Vector(0.0, 0.0, -4.0), $v->normalized());  
                                           
            $u = new Vector(-1.0, -3.0, 2.0);                          
            $greyscale += $scene->traceRay($ray, $u->normalized());                                    
         }
      }                     
      echo chr( 0.5 + 255.0*$greyscale/(double)(SS*SS) );                                          
   }
}           
?>
