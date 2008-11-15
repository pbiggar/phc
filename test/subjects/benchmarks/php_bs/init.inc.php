<?php
/*
   (c) 2003-2004 John Lim
*/


if (isset($_GET['view'])) {
	$file = basename($_SERVER['PHP_SELF']);
	$f = fopen($file,'r');
	if ($f) {
		$txt = fread($f,filesize($file));
		highlight_string($txt);
		fclose($f);
	}
	die();
}

if (!function_exists('file_get_contents')) {
function file_get_contents($fn)
{
	$f = fopen($fn,'r');
	if (!$f) return false;
	$d = fread($f,filesize($fn));
	fclose($f);
	return $d;
}
}
?>