<?php

  //Bug report on phc-general
  //Basic class properties cause segfault (phc_declare_property asserts compiled out)

class DataSet 
{
  public $Type;
} 
$x = new DataSet();
var_dump($x); 

?>
