<?php
$usr_langs = array('de', 'fr', 'it');

function f() {
  global $usr_langs;
  
  foreach($usr_langs as $lang) {
    # do something 
  } 
}

function g() {
  global $usr_langs;
  
  foreach ($usr_langs as $lang) {
    f();
    echo "$lang "; 
  }
}

echo "Test1:<br>";
g();
echo "<br>----------<br>";

echo "Test2:<br>";
foreach ($usr_langs as $lang) {
  f();
  echo "$lang "; 
}


function f2() {

  foreach($GLOBALS['usr_langs'] as $lang) {
  }
}

function g2() {

  foreach($GLOBALS['usr_langs'] as $lang) {
    f2();
    echo $lang.' ';
  }
}

echo 'Test1:<br>';
g2();
echo '<br>----------<br>';

echo 'Test2:<br>';
foreach($usr_langs as $lang) {
  f2();
  echo $lang.' ';
}

?>
