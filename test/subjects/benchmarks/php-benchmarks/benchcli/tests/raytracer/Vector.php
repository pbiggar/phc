<?php
class RayTracer_Vector {
    public $x = 0.0;
    public $y = 0.0;
    public $z = 0.0;
	
    /**
     * 
     *
     * @param float $x
     * @param float $y
     * @param float $z
     */
    public function __construct($x = 0.0, $y = 0.0, $z = 0.0) {
        $this->x = $x;
        $this->y = $y;
        $this->z = $z;
    }

    public function copy(RayTracer_Vector $vector){
        $this->x = $vector->x;
        $this->y = $vector->y;
        $this->z = $vector->z;
    }

    public function normalize()
    {
        $m = $this->magnitude();
        return new RayTracer_Vector($this->x / $m, $this->y / $m, $this->z / $m);
    }

    public function magnitude()
    {
            return sqrt(($this->x * $this->x) + ($this->y * $this->y) + ($this->z * $this->z));
    }

    public function cross(RayTracer_Vector $w)
    {
        return new RayTracer_Vector(
                                    -$this->z * $w->y + $this->y * $w->z,
                                    $this->z * $w->x - $this->x * $w->z,
                                    -$this->y * $w->x + $this->x * $w->y
                                    );
    }

    public function dot(RayTracer_Vector $w)
    {
        return $this->x * $w->x + $this->y * $w->y + $this->z * $w->z;
    }

    public static function add(RayTracer_Vector $v, RayTracer_Vector $w)
    {
        return new RayTracer_Vector($w->x + $v->x, $w->y + $v->y, $w->z + $v->z);
    }

    public static function subtract(RayTracer_Vector $v, RayTracer_Vector $w)
    {
        return new RayTracer_Vector($v->x - $w->x, $v->y - $w->y, $v->z - $w->z);
    }

    public static function multiplyVector(RayTracer_Vector $v, RayTracer_Vector $w)
    {
        return new RayTracer_Vector($v->x * $w->x, $v->y * $w->y, $v->z * $w->z);
    }

    /**
     * 
     *
     * @param RayTracer_Vector $v
     * @param float $w
     * @return RayTracer_Vector
     */
    public static function multiplyScalar(RayTracer_Vector $v, $w)
    {
        return new RayTracer_Vector($v->x * $w, $v->y * $w, $v->z * $w);
    }
	
    public function __toString()
    {
        return 'Vector [' . $this->x . ',' . $this->y . ',' . $this->z . ']';
    }
}