<?php

for ($i=0; $i<1000; $i++) {
  $f = file("/etc/passwd");
}

var_dump($f);

?>



