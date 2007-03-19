<?php
	list($x, $y, $z) = $arr;
	list($x, , $z) = $arr;
	list(list($x, $y), list($z, $w), $a) = $arr;
	list(list($x, , $z), list($z, ,$v), $a) = $arr;
?>
