<?php

  // should be removed, def was not declared.
  if (defined("def"))
    echo "def defined?\n";

  // case insensitive (internally represented as "def" - lowercase)
  $x = define("Def", "something", true);

  // not defined, since "def" is already defined.
  $y = define("def", "something else");

  // defined, since "Def" (with the capital d) was not yet defined.
  $z = define("Def", "something else completely");

  // not defined, since "dEf" is internally represented as "def"
  // which has already been defined.
  $w = define("dEf", "something differently", true); 

  var_dump($x); // true
  var_dump($y); // false
  var_dump($z); // true
  var_dump($w); // false

  if (defined("def"))
    echo "def: " . def . "\n";

  if (defined("Def"))
    echo "Def: " . Def . "\n";

  if (defined("DEF"))
    echo "DEF: " . DEF . "\n";

  if (defined("dEf"))
    echo "dEf: " . dEf . "\n";

?>
