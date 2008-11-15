<?php
/* The Computer Language Shootout 
   http://shootout.alioth.debian.org/
	  --range 200,400,600
   contributed by Thomas GODART (based on Greg Buchholz's C program) */

$w = 0; $h = 0; $bit_num = 0;
$byte_acc = 0;
$i = 0; $iter = 50;
$x = 0; $y = 0; $limit2 = 4;
$Zr = 0; $Zi = 0; $Cr = 0; $Ci = 0; $Tr = 0; $Ti = 0;

@$h = ($argc == 2) ? $argv[1] : 600;
$w = $h;

printf ("P4\n%d %d\n", $w, $h);

for ($y = 0 ; $y < $h ; ++$y)
{
	for ($x = 0 ; $x < $w ; ++$x)
	{
		$Zr = 0; $Zi = 0; $Tr = 0; $Ti = 0.0;

		$Cr = (2.0 * $x / $w - 1.5); $Ci = (2.0 * $y / $h - 1.0);

		for ($i = 0 ; $i < $iter and ($Tr + $Ti <= $limit2) ; ++$i)
		{
			$Zi = 2.0 * $Zr * $Zi + $Ci;
			$Zr = $Tr - $Ti + $Cr;
			$Tr = $Zr * $Zr;
			$Ti = $Zi * $Zi;
		}

		$byte_acc = $byte_acc << 1;
		if ($Tr + $Ti <= $limit2) $byte_acc = $byte_acc | 1;

		++$bit_num;

		if ($bit_num == 8)
		{
			echo chr ($byte_acc);
			$byte_acc = 0;
			$bit_num = 0;
		}
		else if ($x == $w - 1)
		{
			$byte_acc = $byte_acc << (8 - $w % 8);
			echo chr ($byte_acc);
			$byte_acc = 0;
			$bit_num = 0;
		}
	}
}

?>
