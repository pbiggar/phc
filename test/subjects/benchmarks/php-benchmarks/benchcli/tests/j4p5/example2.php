<?php

/* Example2
**
** Here we extend the JavaScript runtime environment with additional objects and methods.
** Since the speed of execution is slower than php speed, you can use this to expose 
** resource-intensive functions for JavaScript to call directly.
** 
*/

#-- Include the js library.
include "js.php";

#-- Define our js code
$code = <<<EOD

print("SHA-1('abc') = "+external.sha1("abc")+"<br>");
print("37 + PI = "+external.add(37,external.PI)+"<br>");

EOD;

#-- Define two functions meant to be called from javascript
#-- note the use of php_int() and php_str() to convert a js value to a php value, and the
#-- use of js_int() and js_str() to convert a php value to a js value.
function js_sha1($str) {
  return js_str(sha1(php_str($str)));
}
function js_add($a, $b) {
  return js_int(php_int($a) + php_int($b));
}

#-- Define a javascript object named "external" with member functions "sha1" and 
#-- "add", and a property "PI"
js::define("external", array("sha1" => "js_sha1", "add" => "js_add"), array("PI"=> 3.1416));

#-- Run the js code.
js::run($code);

?>