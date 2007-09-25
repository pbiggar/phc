<?php

function simpleudcall() {
  for ($i = 0; $i < 1000000; $i++) 
    hallo2("hallo");
}

function hallo2($a) {
}

simpleudcall ();


?>
