<?php
class RayTracer_Shape_Sphere {

	/**
	 * 
	 *
	 * @param RayTracer_Vector $pos
	 * @param float $radius
	 * @param RayTracer_Material_BaseMaterial $material
	 */
	public function __construct(RayTracer_Vector $pos, $radius, RayTracer_Material_BaseMaterial $material)
    {
        $this->radius = $radius;
        $this->position = $pos;
        $this->material = $material;
    }

    public function intersect($ray)
    {
        $info = new RayTracer_IntersectionInfo();
        $info->shape = $this;

        $dst = RayTracer_Vector::subtract($ray->position, $this->position);

        $B = $dst->dot($ray->direction);
        $C = $dst->dot($dst) - ($this->radius * $this->radius);
        $D = ($B * $B) - $C;

        if($D > 0){ // intersection!
            $info->isHit = true;
            $info->distance = (-$B) - sqrt($D);
            $info->position = RayTracer_Vector::add(
                                                $ray->position,
                                                RayTracer_Vector::multiplyScalar(
                                                    $ray->direction,
                                                    $info->distance
                                                )
                                            );
            $info->normal = RayTracer_Vector::subtract(
                                            $info->position,
                                            $this->position
                                        )->normalize();

            $info->color = $this->material->getColor(0,0);
        } else {
            $info->isHit = false;
        }
        return $info;
    }

    public function __toString()
    {
        return 'Sphere [position=' . $this->position . ', radius=' . $this->radius . ']';
    }
}