<?php

function simple() {
  $a = 0;
  for ($i = 0; $i < 1000000; $i++) 
    $a++;

  $thisisanotherlongname = 0;
  for ($thisisalongname = 0; $thisisalongname < 1000000; $thisisalongname++) 
    $thisisanotherlongname++;
}

simple ();

?>
