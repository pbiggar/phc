<?php 
while ($i++ < 65536) {
    $fp = fopen(__FILE__, "r");
    if (!$fp) {
        die("oops");
    }
} 
?>