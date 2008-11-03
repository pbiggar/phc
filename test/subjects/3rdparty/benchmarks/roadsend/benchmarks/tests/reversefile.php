<?php
/*
 $Id: reversefile.php,v 1.2 2004/02/20 18:03:41 tim Exp $
 http://www.bagley.org/~doug/shootout/
*/
$datafile = "test/subjects/3rdparty/benchmarks/roadsend/benchmarks/data/spellcheck";

if(!file_exists($datafile)) {
  trigger_error("Couldn't find datafile $datafile.", E_USER_ERROR);
}
$fd = fopen($datafile, "r");
$lines = array();
while (!feof ($fd)) { array_push($lines, fgets($fd, 4096)); }
fclose($fd);
foreach (array_reverse($lines) as $line) print $line;
?>
