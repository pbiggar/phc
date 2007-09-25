<?php

function hallo($a) {
}

function simpleucall() {
  for ($i = 0; $i < 1000000; $i++) 
    hallo("hallo");
}

simpleucall ();

?>
