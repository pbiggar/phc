<?php
require_once 'tests/raytracer/Shape/BaseShape.php';
class RayTracer_Shape_Plane extends RayTracer_Shape_BaseShape {
    private $d = 0.0;

    public function __construct(RayTracer_Vector $pos, $d, RayTracer_Material_BaseMaterial $material)
    {
        $this->position = $pos;
        $this->d = $d;
        $this->material = $material;
    }

    public function intersect($ray)
    {
        $info = new RayTracer_IntersectionInfo();

        $Vd = $this->position->dot($ray->direction);
        if($Vd == 0) return $info; // no intersection

        $t = -($this->position->dot($ray->position) + $this->d) / $Vd;
        if($t <= 0) return $info;

        $info->shape = $this;
        $info->isHit = true;
        $info->position = RayTracer_Vector::add(
                                            $ray->position,
                                            RayTracer_Vector::multiplyScalar(
                                                $ray->direction,
                                                $t
                                            )
                                        );
        $info->normal = $this->position;
        $info->distance = $t;

        if($this->material->hasTexture){
            $vU = new RayTracer_Vector($this->position->y, $this->position->z, -$this->position->x);
            $vV = $vU->cross($this->position);
            $u = $info->position->dot($vU);
            $v = $info->position->dot($vV);
            $info->color = $this->material->getColor($u, $v);            
        } else {
            $info->color = $this->material->getColor(0,0);
        }
        return $info;
    }
        
    public function __toString()
    {
        return 'Plane [' . $this->position . ', d=' . $this->d . ']';
    }
}
