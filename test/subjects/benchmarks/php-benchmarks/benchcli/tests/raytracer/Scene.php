<?php 
    	require_once 'Camera.php';
    	require_once 'Vector.php';
        require_once 'Background.php';
        require_once 'Color.php';

class RayTracer_Scene {
    public $camera = null;
    /**
     * 
     * @var array
     */
    public $shapes;
    /**
     * 
     * @var array
     */
    public $lights;
    public $background = null;

    public function __construct()
    {
    	$this->camera = new RayTracer_Camera(
            new RayTracer_Vector(0,0,-5),
            new RayTracer_Vector(0,0,1),
            new RayTracer_Vector(0,1,0)
        );
        $this->shapes = array();
        $this->lights = array();
        $this->background = new RayTracer_Background(new RayTracer_Color(0,0,0.5), 0.2);
    }
}
