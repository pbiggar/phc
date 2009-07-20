<?php
		require_once 'IntersectionInfo.php';
class RayTracer_Engine {
	public $canvas = null; /* 2d context we can render to */

	public function __construct($options = array())
	{
		$this->options = array_merge(array(
		'canvasHeight' => 100,
		'canvasWidth'=> 100,
		'pixelWidth'=> 2,
		'pixelHeight'=> 2,
		'renderDiffuse'=> false,
		'renderShadows'=> false,
		'renderHighlights'=> false,
		'renderReflections'=> false,
		'rayDepth'=> 2
		), $options);

		$this->options['canvasHeight'] /= $this->options['pixelHeight'];
		$this->options['canvasWidth'] /= $this->options['pixelWidth'];
		
		/* TODO: dynamically include other scripts */
	}
	
	public function setPixel($x, $y, RayTracer_Color $color){
		$pxW = $this->options['pixelWidth'];
		$pxH = $this->options['pixelHeight'];

		if ($this->canvas) {
			$colorId = imagecolorallocate($this->canvas, $color->red*255, $color->green*255, $color->blue*255);
			$x1 = $x * $pxW;
			$y1 = $y * $pxH;
			imagefilledrectangle($this->canvas, $x1, $y1, $x1 + $pxW, $y1 + $pxH, $colorId);
			/*
			$this->canvas->fillStyle = $color->__toString();
			$this->canvas->fillRect ($x * $pxW, $y * $pxH, $pxW, $pxH);
			*/
		} else {
			if ($x === $y) {
				$this->checkNumber += $color->brightness();
			}
		 	//echo $x * $pxW, $y * $pxH, $pxW, $pxH, PHP_EOL;
		}
	}

	public function renderScene(RayTracer_Scene $scene, $canvas)
	{
		$this->checkNumber = 0;
		/* Get canvas */
		if ($canvas) {
//			$this->canvas = $canvas->getContext("2d");
			$this->canvas = $canvas;
		} else {
			$this->canvas = null;
		}

		$canvasHeight = $this->options['canvasHeight'];
		$canvasWidth = $this->options['canvasWidth'];

		for($y=0; $y < $canvasHeight; $y++) {
			for($x=0; $x < $canvasWidth; $x++) {
				$yp = $y * 1.0 / $canvasHeight * 2 - 1;
				$xp = $x * 1.0 / $canvasWidth * 2 - 1;
				
				$ray = $scene->camera->getRay($xp, $yp);
				
				$color = $this->getPixelColor($ray, $scene);
				
				$this->setPixel($x, $y, $color);
			}
		}
		/*
		if ($this->checkNumber !== 2321) {
			var_dump($this->checkNumber);
			throw new Exception("Scene rendered incorrectly");
		}*/
	}
	
	public function getPixelColor($ray, $scene)
	{
		$info = $this->testIntersection($ray, $scene, null);
		if ($info->isHit) {
			$color = $this->rayTrace($info, $ray, $scene, 0);
			return $color;
		}
		return $scene->background->color;
	}
	
	public function testIntersection($ray, $scene, $exclude)
	{
		$hits = 0;
		$best = new RayTracer_IntersectionInfo();
		$best->distance = PHP_INT_MAX * 1.0;

		foreach ($scene->shapes as $shape) {
			//@var $shape Raytracer_BaseShape
			if ($shape != $exclude) {
				$info = $shape->intersect($ray);
				if ($info->isHit && $info->distance >= 0 && $info->distance < $best->distance) {
					$best = $info;
					$hits++;
				}
			}
		}
		$best->hitCount = $hits;
		return $best;
	}

	public function getReflectionRay($P, $N, $V)
	{
		$c1 = -$N->dot($V);
		$R1 = RayTracer_Vector::add(
		RayTracer_Vector::multiplyScalar($N, 2*$c1),
		$V
		);
		return new Raytracer_Ray($P, $R1);
	}

	public function rayTrace(RayTracer_IntersectionInfo $info, RayTracer_Ray $ray, RayTracer_Scene $scene, $depth)
	{
		// Calc ambient
		$color = RayTracer_Color::multiplyScalar($info->color, $scene->background->ambience);
		$shininess = pow(10, $info->shape->material->gloss + 1);

		foreach ($scene->lights as $light) {
			
			// Calc diffuse lighting
			$v = RayTracer_Vector::subtract(
			$light->position,
			$info->position
			)->normalize();
	
			if ($this->options['renderDiffuse']) {
				$L = $v->dot($info->normal);
				if ($L > 0.0) {
					$color = RayTracer_Color::add(
						$color,
						RayTracer_Color::multiply(
							$info->color,
							RayTracer_Color::multiplyScalar(
								$light->color,
								$L
							)
						)
					);
				}
			}
	
	
			// The greater the depth the more accurate the colours, but
			// this is exponentially (!) expensive
			if ($depth <= $this->options['rayDepth']) {
				// calculate reflection ray
				if($this->options['renderReflections'] && $info->shape->material->reflection > 0)
				{
					$reflectionRay = $this->getReflectionRay($info->position, $info->normal, $ray->direction);
					$refl = $this->testIntersection($reflectionRay, $scene, $info->shape);
			
					if ($refl->isHit && $refl->distance > 0){
						$refl->color = $this->rayTrace($refl, $reflectionRay, $scene, $depth + 1);
					} else {
						$refl->color = $scene->background->color;
					}
	
					$color = RayTracer_Color::blend(
						$color,
						$refl->color,
						$info->shape->material->reflection
					);
				}
	
				// Refraction
				/* TODO */
			}
	
			/* Render shadows and highlights */
			
			$shadowInfo = new RayTracer_IntersectionInfo();
	
			if($this->options['renderShadows']){
				$shadowRay = new RayTracer_Ray($info->position, $v);
				
				$shadowInfo = $this->testIntersection($shadowRay, $scene, $info->shape);
				if($shadowInfo->isHit && $shadowInfo->shape != $info->shape /*&& shadowInfo.shape.type != 'PLANE'*/){
					$vA = RayTracer_Color::multiplyScalar($color, 0.5);
					$dB = (0.5 * pow($shadowInfo->shape->material->transparency, 0.5));
					$color = RayTracer_Color::addScalar($vA, $dB);
				}
			}
	
			// Phong specular highlights
			if($this->options['renderHighlights'] && !$shadowInfo->isHit && $info->shape->material->gloss > 0){
				$Lv = RayTracer_Vector::subtract(
					$info->shape->position,
					$light->position
				)->normalize();
	
				$E = RayTracer_Vector::subtract(
					$scene->camera->position,
					$info->shape->position
				)->normalize();
	
				$H = RayTracer_Vector::subtract(
					$E,
					$Lv
				)->normalize();
	
				$glossWeight = pow(max($info->normal->dot($H), 0), $shininess);
				$color = RayTracer_Color::add(
					RayTracer_Color::multiplyScalar($light->color, $glossWeight),
					$color
				);
			}
		}
		$color->limit();
		return $color;
	}
}
