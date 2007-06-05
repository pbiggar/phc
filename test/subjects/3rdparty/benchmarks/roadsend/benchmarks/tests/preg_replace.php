<?php

$target = "foobarfoobarfoo";
$target .= $target;
$target .= $target;
$target .= $target;



for ($i=0; $i<1000; $i++) {
    preg_replace("/foo/", "baz", $target);
}

print preg_replace("/foo/", "baz", $target);

?>