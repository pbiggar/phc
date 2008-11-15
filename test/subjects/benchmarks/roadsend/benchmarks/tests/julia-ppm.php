<?php

function complex ($real_part, $imag_part) {
  return array($real_part, $imag_part);
}

function real_part ($complex_number) {
  return $complex_number[0];
}

function imag_part ($complex_number) {
  return $complex_number[1];
}

function complex_add ($complex1, $complex2) {
  return complex(real_part($complex1) + real_part($complex2),
                 imag_part($complex1) + imag_part($complex2));
}

function complex_multiply ($complex1, $complex2) {
  return complex((real_part($complex1) * real_part($complex2)) - (imag_part($complex1) * imag_part($complex2)),
                 (real_part($complex1) * imag_part($complex2)) + (imag_part($complex1) * real_part($complex2)));
}

function complex_abs ($complex ) {
  $r = real_part($complex);
  $i = imag_part($complex);
  return sqrt(($r * $r) + ($i * $i));
}

function ppm_write ($filehandle, $data) {
#  if (posix_isatty(STDOUT))
    fwrite($filehandle, $data);
#  else
#    print($data);
}

function julia_ppm ($filename, $size, $depth, $zreal, $zimag) {
  ## open the file
  if (file_exists($filename))
    unlink($filename);
  $ppm = fopen($filename, "w");

  ## write ppm header
  ppm_write($ppm, "P3\n");

  ## write width and height
  ppm_write($ppm, $size . " " . $size . "\n");

  ## write max value
  ppm_write($ppm, $depth . "\n");

  ## write pixel values
  $z        = complex($zreal, $zimag);
  $real_min = -1.2;
  $real_max =  1.2;
  $imag_min = -1.2;
  $delta    = ($real_max - $real_min) / $size;

  for ($i = 0, $xreal = $real_min;
       $i < $size;
       $i++, $xreal = ($xreal + $delta)) {
    for ($j = 0, $ximag = $imag_min;
         $j < $size;
         $j++, $ximag = ($ximag + $delta)) {
      $count = 0;
      $x = complex($xreal, $ximag) ;
      while ($count < $depth && complex_abs($x) < 2.0) {
        $count++;
        $x = complex_add(complex_multiply($x, $x), $z);
      }
      if (complex_abs($x) <= 2.0)
        ppm_write($ppm, "0 0 0\n");
      else {
        $intensity = $count / $depth;
        if ($intensity > .001)
          ppm_write($ppm, round($depth - ($depth * $intensity)) . " " .
                          round($depth - ($depth * $intensity)) . " " .
                          $depth . "\n");	
      }
    }
  }
  fclose($ppm);
}

$filename = "/tmp/julia.ppm";

## change the size (second arg) to make test run longer
julia_ppm("/tmp/julia.ppm", 100, 25, -0.74543, 0.11302);

print("image file size: " . filesize($filename) . "\n");

?>