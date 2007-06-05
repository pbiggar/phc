This benchmark was contributed by "BDKR"
<?php

$globules['x']['k']['y']['alpha']=0;

while($globules['x']['k']['y']['alpha']<1000000) { 
  ++$globules['x']['k']['y']['alpha']; 
}

test_global_x();
$globules['x']['k']['y']['alpha']='For a later function';
test_global_x();


function test_global_x() { 
  echo $GLOBALS['globules']['x']['k']['y']['alpha']."\n\n"; 
}

?>
