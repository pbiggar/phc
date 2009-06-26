<?php
class RayTracer_Light {
    public $position = null;
    public $color = null;
    public $intensity = 10.0;
	
    /**
     * 
     *
     * @param RayTracer_Vector $pos
     * @param RayTracer_Color $color
     * @param float $intensity
     */
    public function __construct(RayTracer_Vector $pos, RayTracer_Color $color, $intensity = 10.0) {
        $this->position = $pos;
        $this->color = $color;
        $this->intensity = $intensity;
    }
	
    //TODO Review
    public function getIntensity($distance){
        if($distance >= $this->intensity) return 0;

        return pow(($this->intensity - $distance) / $strength, 0.2);
    }

    public function __toString()
    {
        return 'Light [' . $this->position.x + ',' . $this->position->y + ',' . $this->position->z . ']';
    }
}