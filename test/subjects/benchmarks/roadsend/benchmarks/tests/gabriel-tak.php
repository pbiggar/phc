From "Performance and Evaluation of Lisp Systems" by Richard Gabriel 
pg. 82


"The Tak benchmark is a variant of the Takeuchi function that Ikuo
Takeuchi of Japan used as a simple benchmark.  Because Tak is
function-call-heavy, it is representative of many Lisp programs.  On
the other hand, because it does little else but function calls (fixnum
arithmetic is performed as well), it is not representative of the
majority of Lisp programs.  It is only a good test of function call
and recursion, in particular."


<?php

function tak($x, $y, $z) {
  if ( !($y < $x)) {
    return $z;
  } else {
    return tak( tak($x - 1, $y, $z),
		tak($y - 1, $z, $x),
		tak($z - 1, $x, $y));
  }
}

print "result: " . tak(18, 12, 6) . "\n";

?>
