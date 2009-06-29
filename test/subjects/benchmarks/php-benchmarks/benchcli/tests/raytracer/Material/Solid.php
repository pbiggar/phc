<?php 
require_once 'tests/raytracer/Material/BaseMaterial.php';

class RayTracer_Material_Solid extends RayTracer_Material_BaseMaterial {

	public function __construct($color, $reflection, $refraction, $transparency, $gloss)
	{
        $this->color = $color;
        $this->reflection = $reflection;
        $this->transparency = $transparency;
        $this->gloss = $gloss;
        $this->hasTexture = false;
    }

    public function getColor($u, $v){
        return $this->color;
    }

    public function __toString()
    {
        return 'SolidMaterial [gloss=' . $this->gloss . ', transparency=' . $this->transparency . ', hasTexture=' . $this->hasTexture .']';
    }
}
