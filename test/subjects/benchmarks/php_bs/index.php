<?php
/*
   (c) 2003-2004 John Lim
*/
set_time_limit(1200);

include_once('config.inc.php');

$s = "<html><title>PHP Benchmarking Suite</title><body>";
$s .= "<h3>Benchmarking PHP ".PHP_VERSION."</h3>";
$s .= "Any pair of results that are within 10% of each other are probably not statistically significant, 
and the results can be considered approximately equal. All results are in seconds, mostly based on running the code 1000 times.
Faster is better.</font></p>";
echo $s;

$s .= "<?php if (file_exists('../index.php')) echo '<h3><a href=../index.php>&lt;&lt; Back</a></h3>\n';?>\n";

$rootdir = dir('.');
$dirlist = array();
while ($subdirname = $rootdir->read()) {
	if (strncmp(strtolower($subdirname),'_php',4) == 0) {
		$dirlist[] = $subdirname;
		continue;
	}
	if (strpos($subdirname,'.') !== false) continue;
	if (strncmp($subdirname,'_',1) == 0) continue;
	$dirlist[] = $subdirname;
}
asort($dirlist);

foreach($dirlist as $d) {
	if (strncmp(strtolower($d),'_php',4) == 0) {
		echo "<h3><a href=".rawurlencode($d)."/index.php>Cached ".trim(str_replace('_',' ',$d))." Results</a></h3>";
	} else {
		echo "<h3><a href=bench.php?d=".rawurlencode($d).">".htmlspecialchars($d)."</a></h3>\n";
		$s .= "<h3><a href=".rawurlencode($d).".html>".htmlspecialchars($d)."</a></h3>\n";
	}
}

echo Copyright();

$s .= Copyright();
$s .= "<hr>$copyr <font size=1><b>Cached version</b>.</font>";

$f = fopen('_cache/index.php','w');
fwrite($f,$s);
fclose($f);
?>

