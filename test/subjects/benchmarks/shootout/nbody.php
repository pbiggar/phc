<? /* The Great Computer Language Shootout 
   http://shootout.alioth.debian.org/
   
   contributed by Isaac Gouy 
   
   php -q nbody.php 1000
	  --range 200000,2000000,20000000
*/


function Advance(&$bodies, $dt) {
   $m = sizeof($bodies);
   for ($i=0; $i<$m; $i++) {
      for ($j=$i+1; $j<$m; $j++) {
         $dx = $bodies[$i]->x - $bodies[$j]->x;
         $dy = $bodies[$i]->y - $bodies[$j]->y;
         $dz = $bodies[$i]->z - $bodies[$j]->z;

         $distance = sqrt($dx*$dx + $dy*$dy + $dz*$dz);
         $mag = $dt / ($distance * $distance * $distance);

         $bodies[$i]->vx -= $dx * $bodies[$j]->mass * $mag;
         $bodies[$i]->vy -= $dy * $bodies[$j]->mass * $mag;
         $bodies[$i]->vz -= $dz * $bodies[$j]->mass * $mag;

         $bodies[$j]->vx += $dx * $bodies[$i]->mass * $mag;
         $bodies[$j]->vy += $dy * $bodies[$i]->mass * $mag;
         $bodies[$j]->vz += $dz * $bodies[$i]->mass * $mag;
      }
   }
   
   for ($i=0; $i<$m; $i++) {      
      $bodies[$i]->x += $dt * $bodies[$i]->vx;
      $bodies[$i]->y += $dt * $bodies[$i]->vy;
      $bodies[$i]->z += $dt * $bodies[$i]->vz;
   }
}


function Energy(&$bodies) {
   $m = sizeof($bodies);
   $e = 0.0;
   for ($i=0; $i<$m; $i++) {
      $e += 0.5 * $bodies[$i]->mass *
         ( $bodies[$i]->vx * $bodies[$i]->vx
         + $bodies[$i]->vy * $bodies[$i]->vy
         + $bodies[$i]->vz * $bodies[$i]->vz );

      for ($j=$i+1; $j<$m; $j++) {
         $dx = $bodies[$i]->x - $bodies[$j]->x;
         $dy = $bodies[$i]->y - $bodies[$j]->y;
         $dz = $bodies[$i]->z - $bodies[$j]->z;

         $distance = sqrt($dx*$dx + $dy*$dy + $dz*$dz);
         $e -= ($bodies[$i]->mass * $bodies[$j]->mass) / $distance;
      }
   }
   return $e;
}


define("PI", 3.141592653589793);
define("SOLAR_MASS", 4 * PI * PI);
define("DAYS_PER_YEAR", 365.24);

class Body {
   var $x, $y, $z, $vx, $vy, $vz, $mass;
 
   function NewBody($x, $y, $z, $vx, $vy, $vz, $mass){
      $b = new Body;
      $b->x = $x;
      $b->y = $y;
      $b->z = $z;
      $b->vx = $vx;
      $b->vy = $vy;
      $b->vz = $vz;
      $b->mass = $mass;        
      return $b;                               
   } 
      
   function Jupiter(){ 
      return Body::NewBody(  
           4.84143144246472090E+00
         , -1.16032004402742839E+00
         , -1.03622044471123109E-01
         , 1.66007664274403694E-03 * DAYS_PER_YEAR
         , 7.69901118419740425E-03 * DAYS_PER_YEAR
         , -6.90460016972063023E-05 * DAYS_PER_YEAR
         , 9.54791938424326609E-04 * SOLAR_MASS 
      );   
   }
   
   function Saturn(){ 
      return Body::NewBody(  
           8.34336671824457987E+00
         , 4.12479856412430479E+00
         , -4.03523417114321381E-01
         , -2.76742510726862411E-03 * DAYS_PER_YEAR
         , 4.99852801234917238E-03 * DAYS_PER_YEAR
         , 2.30417297573763929E-05 * DAYS_PER_YEAR
         , 2.85885980666130812E-04 * SOLAR_MASS
      );   
   }   
   
   function Uranus(){ 
      return Body::NewBody(  
           1.28943695621391310E+01
         , -1.51111514016986312E+01
         , -2.23307578892655734E-01
         , 2.96460137564761618E-03 * DAYS_PER_YEAR
         , 2.37847173959480950E-03 * DAYS_PER_YEAR
         , -2.96589568540237556E-05 * DAYS_PER_YEAR
         , 4.36624404335156298E-05 * SOLAR_MASS
      );   
   }    
   
   function Neptune(){ 
      return Body::NewBody(  
           1.53796971148509165E+01
         , -2.59193146099879641E+01
         , 1.79258772950371181E-01
         , 2.68067772490389322E-03 * DAYS_PER_YEAR
         , 1.62824170038242295E-03 * DAYS_PER_YEAR
         , -9.51592254519715870E-05 * DAYS_PER_YEAR
         , 5.15138902046611451E-05 * SOLAR_MASS
      );   
   }   
   
   function Sun(){ 
      return Body::NewBody(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, SOLAR_MASS);   
   }   
   
   function OffsetMomentum(&$bodies){ 
      $px = 0.0;
      $py = 0.0;
      $pz = 0.0;
      foreach ($bodies as $each) {
         $px += $each->vx * $each->mass;
         $py += $each->vy * $each->mass;
         $pz += $each->vz * $each->mass;
      }      
      $bodies[0]->vx = -$px / SOLAR_MASS;
      $bodies[0]->vy = -$py / SOLAR_MASS;
      $bodies[0]->vz = -$pz / SOLAR_MASS;                                       
   }      
}


$bodies = array( Body::Sun(), Body::Jupiter(), 
                 Body::Saturn(), Body::Uranus(), Body::Neptune() );                 
Body::OffsetMomentum($bodies);

$n = ($argc == 2) ? $argv[1] : 1;
printf("%0.9f\n", Energy($bodies));
for ($i=0; $i<$n; $i++){ Advance($bodies,0.01); }
printf("%0.9f\n", Energy($bodies));
?>
