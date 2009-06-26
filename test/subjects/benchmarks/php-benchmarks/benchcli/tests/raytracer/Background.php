<?php
class RayTracer_Background {
    public $color = null;
    public $ambience = 0.0;
	
    /**
     * 
     *
     * @param RayTracer_Color $color
     * @param float $ambience
     */
	public function __construct(RayTracer_Color $color, $ambience)
	{
        $this->color = $color;
        $this->ambience = $ambience;
    }
}