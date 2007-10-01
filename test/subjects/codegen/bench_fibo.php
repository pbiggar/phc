<?php

function fibo_r($n){
    return(($n < 2) ? 1 : fibo_r($n - 2) + fibo_r($n - 1));
}

function fibo($n) {
  $r = fibo_r($n);
  print "$r\n";
}

// PHP takes ages to run this. Original was 30.
fibo (4);

?>
