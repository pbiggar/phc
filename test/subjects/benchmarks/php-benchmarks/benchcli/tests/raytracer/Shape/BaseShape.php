<?php
class RayTracer_Shape_BaseShape {
	/**
	 * 
	 *
	 * @var RayTracer_Vector
	 */
    public $position = null;
    /**
     * 
     *
     * @var RayTracer_Material_BaseMaterial
     */
    public $material = null;

	public function __construct()
	{
    	$this->position = new RayTracer_Vector(0.0, 0.0, 0.0);
        $this->material = new RayTracer_Material_Solid(
            new RayTracer_Color(1.0, 0.0, 1.0),
            0.0,
            0.0,
            0.0
        );
    }

	public function __toString()
	{
    	return 'Material [gloss=' . $this->gloss . ', transparency=' . $this->transparency . ', hasTexture=' . $this->hasTexture .']';
    }
}