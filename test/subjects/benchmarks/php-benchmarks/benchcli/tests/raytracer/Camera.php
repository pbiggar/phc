<?php
class RayTracer_Camera {
    public $position = null;
    public $lookAt = null;
    public $equator = null;
    public $up = null;
    public $screen = null;

    public function __construct(RayTracer_Vector $pos, RayTracer_Vector $lookAt, RayTracer_Vector $up)
    {
        $this->up = $up->normalize();
    	$this->position = $pos;
        $this->lookAt = $lookAt;
        $this->equator = $lookAt->normalize()->cross($this->up);
        $this->screen = RayTracer_Vector::add($this->position, $this->lookAt);
    }

    
    
    public function getRay($vx, $vy)
    {
        $pos = RayTracer_Vector::subtract(
            $this->screen,
            RayTracer_Vector::subtract(
            	RayTracer_Vector::multiplyScalar($this->equator, $vx),            
            	RayTracer_Vector::multiplyScalar($this->up, $vy)
            )
        );
        $pos->y = $pos->y * -1;
        $dir = RayTracer_Vector::subtract(
            $pos,
            $this->position
        );
		require_once 'Ray.php';
        $ray = new RayTracer_Ray($pos, $dir->normalize());

        return $ray;
    }

	public function __toString()
	{
	    return 'Ray []';
    }
}