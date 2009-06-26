<?php

/*  Example1
**
**  This runs a small self-contained javascript file.
**  Nothing too exciting here, beyond the fact that it works.
*/

#-- Include the javascript library. This is a small file that may include other files as needed.
include "js.php";

#-- Define some javascript code in a string
$code = <<<EOD

/* define a few useful functions */
Math.rand = function(l) {
  return Math.floor(Math.random()*l);
};
String.prototype.randomChar = function() {
  var pos = Math.rand(this.length);
  return this.charAt(pos);
};
function printbr(str) {
  return print(str+"<br>");
}
/* contrived function to use closures. */
function oper(op, y) {
  switch (op) {
    case '+': return function(x) { return x+y; };
    case '-': return function(x) { return x-y; };
    case '/': return function(x) { return x/y; };
    case '*': return function(x) { return x*y; };
    case '%': return function(x) { return x%y; };
    case 'r': return function(x) { return oper("+-/*%".randomChar(), y)(x); };
    default:
      print("not idea what to do with ["+op+"]<br>");
      return function(x) { return x; };
  }
}
var mod256 = oper("%", 256);
var inc = oper("+", 1);
var half =oper("/", 2);
printbr("37812 mod256 = "+mod256(37812));
printbr("5 +1 = "+inc(5));
printbr("half of 894 is "+half(894));

//

var rand13=oper("r",13);
do {
  printbr("49 ? 13 = "+rand13(49));
} while (rand13(13)!=1);

EOD;

#-- Execute the code. This automatically performs several speed optimizations whenever possible.
js::run($code);

?>