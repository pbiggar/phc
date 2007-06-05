<?php

class SM_smTag {
}

class SM_module {
}

class SM_codePlate {
}

$includedir = $_ENV["PCC_HOME"] . "/benchmarks/data/include/";

include_once($includedir . "/inc.php");
include_once($includedir . "/finc.php");

do {
  include_once($includedir . "/inc$i.php");
  echo "\n";
  include_once($includedir . "/finc$i.php");
  echo "\n";
  $i++;
} while ($i <= 20);

unset($i);
do {
  if (isset($j)) $j=0;
  do {
    include_once($includedir . "/main$i$j.cpt");
    echo "$i, $j\n";
    $j++;
    if (!isset($i)) { echo "isset";  $i=0; }
  } while ($j<10);
  $i++;
} while ($i<10);
?>