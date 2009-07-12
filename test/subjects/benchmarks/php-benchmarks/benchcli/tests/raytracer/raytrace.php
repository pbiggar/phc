<?php
    require_once 'Scene.php';
	require_once 'Shape/Sphere.php';
	require_once 'Material/Solid.php';
	require_once 'Shape/Plane.php';
	require_once 'Material/Chessboard.php';
    require_once 'Light.php';
    require_once 'Engine.php';

function renderScene(){
	$scene = new RayTracer_Scene();

    $scene->camera = new RayTracer_Camera(
                        new RayTracer_Vector(0, 0, -15),
                        new RayTracer_Vector(-0.2, 0, 5),
                        new RayTracer_Vector(0, 1, 0)
                    );
                    
    $scene->background = new RayTracer_Background(
                                new RayTracer_Color(0.5, 0.5, 0.5),
                                0.4
                            );
                            
    $sphere = new RayTracer_Shape_Sphere(
        new RayTracer_Vector(-1.5, 1.5, 2),
        1.5,
        new RayTracer_Material_Solid(
            new RayTracer_Color(0,0.5,0.5),
            0.3,
            0.0,
            0.0,
            2.0
        )
    );

    $sphere1 = new RayTracer_Shape_Sphere(
        new RayTracer_Vector(1, 0.25, 1),
        0.5,
        new RayTracer_Material_Solid(
            new RayTracer_Color(0.9,0.9,0.9),
            0.1,
            0.0,
            0.0,
            1.5
        )
    );

    $v = new RayTracer_Vector(0.1, 0.9, -0.5);
	$plane = new RayTracer_Shape_Plane(
                                $v->normalize(),
                                1.2,
                                new RayTracer_Material_Chessboard(
                                    new RayTracer_Color(1.0, 1.0, 1.0),
                                    new RayTracer_Color(0.0, 0.0, 0.0),
                                    0.2,
                                    0.0,
                                    1.0,
                                    0.7
                                )
                            );
                            
    $scene->shapes[] = $plane;
    $scene->shapes[] = $sphere;
    $scene->shapes[] = $sphere1;
        
    $light = new RayTracer_Light(
        new RayTracer_Vector(5, 10, -1),
        new RayTracer_Color(0.8, 0.8, 0.8)
    );

    $light1 = new RayTracer_Light(
        new RayTracer_Vector(-3, 5, -15),
        new RayTracer_Color(0.8, 0.8, 0.8),
        100
    );

    $scene->lights[] = $light;
    $scene->lights[] = $light1;

    $imageWidth = 100; // $F('imageWidth');
    $imageHeight = 100; // $F('imageHeight');
    $pixelSize = split(',', "5,5"); //  $F('pixelSize').split(',');
    $renderDiffuse = true; // $F('renderDiffuse');
    $renderShadows = true; // $F('renderShadows');
    $renderHighlights = true; // $F('renderHighlights');
    $renderReflections = true; // $F('renderReflections');
    $rayDepth = 2;//$F('rayDepth');

    $raytracer = new RayTracer_Engine(
        array(
            "canvasWidth" => $imageWidth,
            "canvasHeight" => $imageHeight,
            "pixelWidth" => $pixelSize[0],
            "pixelHeight" => $pixelSize[1],
            "renderDiffuse" => $renderDiffuse,
            "renderHighlights" => $renderHighlights,
            "renderShadows" => $renderShadows,
            "renderReflections" => $renderReflections,
            "rayDepth" => $rayDepth
        )
    );

    // Create a 55x30 image
	//$im = imagecreatetruecolor(500, 500);
	$im = null;
    $raytracer->renderScene($scene, $im, 0);
	/*
    // Save the image
	imagepng($im, './imagefilledrectangle.png');
	imagedestroy($im);
*/
}

$elapsed = 0;
$start = microtime(true);

for ($i = 0;$i<6; $i++){
	renderScene();
}
$usec = microtime(true) - $start;
echo ($usec * 1000).'ms'. PHP_EOL;

/*
var RayTrace = new BenchmarkSuite('RayTrace', 932666, [
  new Benchmark('RayTrace', renderScene)
]);

var checkNumber;
*/
/*Execute at minimum 1 second the benchmark*/
/*
$elapsed = 0;
$start = microtime(true) * 1000;
for ($n = 0;$elapsed < 1000; $n++) {
	renderScene();
	$elapsed = (microtime(true) * 1000) - $start;
}
$usec = ($elapsed * 1000) / $n;
echo ($usec). PHP_EOL;

// Computes the geometric mean of a set of numbers.
function GeometricMean($numbers) 
{
	$log = 0;
	foreach ($numbers as $number) {
	  $log += log($number);
	}
	return pow(M_E, $log / count($numbers));
}
$reference = 932666;
$mean = GeometricMean(array($usec));
echo "score : ". (100 *($reference / $mean));*/
