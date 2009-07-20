<?php 
abstract class RayTracer_Material_BaseMaterial {

    public $gloss = 2.0;             // [0...infinity] 0 = matt
    public $transparency = 0.0;      // 0=opaque
    public $reflection = 0.0;        // [0...infinity] 0 = no reflection
    public $refraction = 0.50;
    public $hasTexture = false;

    public function __construct()
    {
    }
	
    /**
     * 
     *
     * @param float $u
     * @param float $v
     * return RayTracer_Color
     */
    abstract public function getColor($u, $v);

    public function wrapUp($t)
    {
        $t = fmod($t, 2.0);
        if($t < -1) $t += 2.0;
        if($t >= 1) $t -= 2.0;
        return $t;
    }
    
    public function __toString()
    {
        return 'Material [gloss=' . $this->gloss . ', transparency=' . $this->transparency . ', hasTexture=' . $this->hasTexture .']';
    }
}