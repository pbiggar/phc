<?php


function hash2($n) {
  for ($i = 0; $i < $n; $i++) {
    $hash1["foo_$i"] = $i;
    $hash2["foo_$i"] = 0;
  }
  for ($i = $n; $i > 0; $i--) {
    foreach($hash1 as $key => $value) $hash2[$key] += $value;
  }
  $first = "foo_0";
  $last  = "foo_".($n-1);
  print "$hash1[$first] $hash1[$last] $hash2[$first] $hash2[$last]\n";

}


hash2 (5);

?>
