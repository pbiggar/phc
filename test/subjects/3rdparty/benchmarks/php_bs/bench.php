<?php

/*
   (c) 2003-2004 John Lim
   
   METADATA FORMAT
   
   //~~ Title to display, description of bench1(), description of bench2(), # iterations

   Optional is # iterations, which defaults to 1000
*/

include_once('config.inc.php');

function DoScanDir($dir)
{
	$bencharr = array();
	$subdir = dir($dir);
	while ($fname = $subdir->read()) {
		if (strpos($fname,'---') !== false) $bencharr[$dir.'/'.$fname] = '<br>';
		if (strpos($fname,'.php') === false) continue;
		if (strpos($fname,'~')) continue; // homesite tmp file
		if (strncmp($fname,'_',1) == 0) continue;
		$fname = $dir.'/'.$fname;
		$f = fopen($fname,'r');
		if ($f) {
			$txt = fread($f,filesize($fname));
			fclose($f);
			if (preg_match("!//~~(.*)!",$txt,$txtarr)) {
				$bencharr[$fname] = explode(',', $fname.','.$txtarr[1]);
			}
		}
	}
	ksort($bencharr);
	return $bencharr;
}

function TestDir($bencharr,$dest,$swap)
{
global $CACHE;

	if (PHP_VERSION < 4.1) {
	global $HTTP_SERVER_VARS;
		$_SERVER = $HTTP_SERVER_VARS;
	}
	$host = $_SERVER['HTTP_HOST'];
	$PHP_SELF = $_SERVER['PHP_SELF'];
	$dir = dirname($PHP_SELF);

	echo "<a href=index.php>Back</a>";
	
	$noswap = 1 - $swap;
	$bfirst = ($noswap) ? '2' : '1';
	if (empty($CACHE)) {
		echo " &nbsp; <a href=bench.php?d=$dest&swap=$noswap>Run bench$bfirst() first.</a>";
	}
	flush();
	foreach($bencharr as $arr) {
		if (!is_array($arr)) {
			echo $arr;
			continue;
		}
		
		$file = $arr[0];
		$desc = $arr[1];
		$descleft = $arr[2];
		$descright = $arr[3];
		
		$iter = (!empty($arr[4])) ? $iter = (integer) trim($arr[4]) : 1000;
		$findhash = (!empty($arr[5]));
		
		$urlbase = "http://$host$dir/$file";
		$url = "$urlbase?iter=$iter";
		$url .= '&swap='.$swap;
	
		$f = fopen($url,'r');
		$data = '';
		if ($f) {
			while ($data1 = fread($f,100000)) $data .= $data1;
			fclose($f);
		}
		
		if ($findhash) {
			$pos = strpos($data,'##');
			$data = substr($data,$pos);
		}
		//echo "A=",$data,"A",substr($data,0,2);
		if (substr($data,0,2) == '##') {
			$r = explode('##',$data);
			$results[] = array($r[1],$r[2]);
			if (is_numeric($r[2])) {
				if ($r[1] < $r[2]) {
					$descleft = "<b>$descleft</b>";
					if ($r[1]>0) $descleft .= ' <font size=1>x'.sprintf("%2.2f",(float)$r[2]/$r[1]).' faster</font>';
				} else if ($r[1] > $r[2]) {
					$descright = "<b>$descright</b>";
					if ($r[2]>0) $descright .= ' <font size=1>x'.sprintf("%2.2f",(float)$r[1]/$r[2]).' faster</font>';
				}
			}
		} else
			$results[] = array(false,false,$data);
			
		$ss = empty($CACHE) ? 
			" <a href=\"$url&view=1\">Source</a> &nbsp; <a href=\"$urlbase?iter=1\">Test Once</a>  &nbsp; $desc"
		:
			' &nbsp; '.$desc;
			
		echo "<table border=1 width=90%><tr><td colspan=4 bgcolor=#EEEEEE>", $ss;
		// <font size=1>($iter iterations)</font>";
		foreach($results as $arr) {
			if (sizeof($arr) == 3){
				echo "<tr><td>",$descleft.'-',$descright,"<td colspan=3>",$arr[2];
			} else {
				echo "<tr><td width=35%>",$descleft,"<td width=15%>",$arr[0],"<td width=35%>",$descright,"<td width=15%>",$arr[1];
			}
		}
		echo "</table>\n\n";
		flush();
		$results = array();
	}
	
	echo "<p><font size=2>Testing PHP ".PHP_VERSION." Completed on ".PHP_OS.". Benchmark done on: ".date("d-M-Y H:i:s")."</font></p></html>";
	echo "<hr>".Copyright();
}


function DoTestDir($dir,$bencharr)
{
global $CACHE,$PHP_SELF;

	$ok = @mkdir('_cache');
	if (!file_exists('_cache')) die("Cannot create _cache directory");
	$savef = "_cache/$dir.html";
	if (file_exists($savef) && ! empty($CACHE) && ($CACHE < 0 || abs(time() - filemtime($savef)) < $CACHE)) {
		readfile($savef);
		echo "<hr><font size=1>This is a cached result. Results cached for $CACHE seconds. To disable caching, set \$CACHE=0 in $PHP_SELF</font>";
	} else {
		ob_start();
			TestDir($bencharr,$dir,	empty($_GET['swap']) ? '0' : '1');
		$t = ob_get_contents();
		ob_end_flush();
		$f = fopen($savef,'w');
		fwrite($f,$t);
		fclose($f);
	}
	
}

//==============================================================

if (PHP_VERSION < 4.1) $_GET = $HTTP_GET_VARS;

$dir = isset($_GET['d']) ? $_GET['d'] : '';
if (empty($dir)) die("No dir defined");

// SAFETY CHECK
if (strpos($dir,'..') !== false || strpos($dir,'/') !== false || strpos($dir,'\\') !== false) die("Safety check violation 1");
$dirpath = basename($dir);

$bencharr = DoScanDir($dirpath);

DoTestDir($dir,$bencharr);
	
die();


?>