<?php
/*
 $Id: strcat.php,v 1.2 2004-10-11 04:48:01 bfulgham Exp $
 http://shootout.alioth.debian.org/
	  --range 10000,20000,30000,40000 \
	  --sampledelay 0.1 
*/
$n = ($argc == 2) ? $argv[1] : 1;
$str = "";
while ($n-- > 0) {
    $str .= "hello\n";
}
$len = strlen($str);
print "$len\n";
?>
