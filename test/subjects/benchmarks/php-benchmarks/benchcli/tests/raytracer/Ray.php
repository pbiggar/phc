<?php
class RayTracer_Ray {
    public $position = null;
    public $direction = null;
    
    public function __construct(RayTracer_Vector $pos, RayTracer_Vector $dir)
    {
        $this->position = $pos;
        $this->direction = $dir;
    }
	
    public function __toString()
    {
        return 'Ray [' . $this->position + ',' . $this->direction + ']';
    }
}