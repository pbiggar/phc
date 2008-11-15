<?php
/*
 $Id: hash2.php,v 1.1 2004/02/16 14:35:19 tim Exp $
 http://www.bagley.org/~doug/shootout/
*/
$n = ($argc == 2) ? $argv[1] : 1000;

hash2($n);

function hash2($n) {

for ($i = 0; $i < 1000; $i++) {
    $hash1["foo_$i"] = $i;
}
for ($i = $n; $i > 0; $i--) {
    foreach($hash1 as $key => $value) $hash2[$key] += $value;
}
print "$hash1[foo_1] $hash1[foo_9999] $hash2[foo_1] $hash2[foo_9999]\n";
}
?>
