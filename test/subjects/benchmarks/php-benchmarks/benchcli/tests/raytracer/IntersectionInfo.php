<?php
class RayTracer_IntersectionInfo {
	public $isHit = false;
	public $hitCount = 0;
	public $shape = null;
	public $position = null;
	public $normal = null;
	public $color = null;
	public $distance = null;

	public function __construct()
	{
		$this->color = new RayTracer_Color(0,0,0);
	}


	public function __toString()
	{
		return 'Intersection [' . $this->position . ']';
	}
}