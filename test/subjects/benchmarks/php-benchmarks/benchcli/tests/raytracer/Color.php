<?php
class RayTracer_Color {
	public $red = 0.0;
	public $green = 0.0;
	public $blue = 0.0;

	public function __construct($r = 0.0, $g = 0.0, $b = 0.0) 
	{
		$this->red = $r;
		$this->green = $g;
		$this->blue = $b;
	}

	public static function add(RayTracer_Color $c1, RayTracer_Color $c2)
	{
		$result = new RayTracer_Color(0,0,0);

		$result->red = $c1->red + $c2->red;
		$result->green = $c1->green + $c2->green;
		$result->blue = $c1->blue + $c2->blue;
		
		return $result;
	}

	/**
	 * 
	 *
	 * @param RayTracer_Color $c1
	 * @param float $s
	 * @return RayTracer_Color
	 */
	public static function addScalar(RayTracer_Color $c1, $s)
	{
		$result = new RayTracer_Color(0,0,0);
		
		$result->red = $c1->red + $s;
		$result->green = $c1->green + $s;
		$result->blue = $c1->blue + $s;
		
		$result->limit();
	
		return $result;
	}

	public static function subtract(RayTracer_Color $c1, RayTracer_Color $c2)
	{
		$result = new RayTracer_Color(0,0,0);
		
		$result->red = $c1->red - $c2->red;
		$result->green = $c1->green - $c2->green;
		$result->blue = $c1->blue - $c2->blue;
		
		return $result;
	}

	public static function multiply(RayTracer_Color $c1, RayTracer_Color $c2)
	{
		$result = new RayTracer_Color(0,0,0);
		
		$result->red = $c1->red * $c2->red;
		$result->green = $c1->green * $c2->green;
		$result->blue = $c1->blue * $c2->blue;
		
		return $result;
	}
	
	/**
	 * 
	 *
	 * @param RayTracer_Color $c1
	 * @param float $f
	 * @return RayTracer_Color
	 */
	public static function multiplyScalar(RayTracer_Color $c1, $f)
	{
		$result = new RayTracer_Color(0,0,0);
	
		$result->red = $c1->red * $f;
		$result->green = $c1->green * $f;
		$result->blue = $c1->blue * $f;
			
		return $result;
	}
	/**
	 * 
	 *
	 * @param RayTracer_Color $c1
	 * @param float $f
	 * @return Raytracer_Color
	 */
	public static function divideFactor(RayTracer_Color $c1, $f)
	{
		$result = new RayTracer_Color(0,0,0);

		$result->red = $c1->red / $f;
		$result->green = $c1->green / $f;
		$result->blue = $c1->blue / $f;
		
		return $result;
	}

	public function limit()
	{
		$this->red = ($this->red > 0.0) ? ( ($this->red > 1.0) ? 1.0 : $this->red ) : 0.0;
		$this->green = ($this->green > 0.0) ? ( ($this->green > 1.0) ? 1.0 : $this->green ) : 0.0;
		$this->blue = ($this->blue > 0.0) ? ( ($this->blue > 1.0) ? 1.0 : $this->blue ) : 0.0;
	}

	public function distance(RayTracer_Color $color)
	{
		$d = abs($this->red - $color->red) + abs($this->green - $color->green) + abs($this->blue - $color->blue);
		return $d;
	}

	/**
	 * 
	 *
	 * @param RayTracer_Color $c1
	 * @param RayTracer_Color $c2
	 * @param float $w
	 * @return unknown
	 */
	public static function blend(RayTracer_Color $c1, RayTracer_Color $c2, $w)
	{
		$result = RayTracer_Color::add(
		RayTracer_Color::multiplyScalar($c1, 1 - $w),
		RayTracer_Color::multiplyScalar($c2, $w)
		);
		return $result;
	}
	
	public function brightness()
	{
		$r = floor($this->red*255);
		$g = floor($this->green*255);
		$b = floor($this->blue*255);
		return ($r * 77 + $g * 150 + $b * 29) >> 8;
	}

	public function __toString()
	{
		$r = floor($this->red*255);
		$g = floor($this->green*255);
		$b = floor($this->blue*255);
		
		return "rgb("+ $r +","+ $g +","+ $b +")";
	}
}
