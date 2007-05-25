<?
/*
 * When we write to $y in statement marked (*), we find that $y is a reference to
 * another variable (that is, $x, but the code generator does not necessarily know
 * that). Since it is a reference to another variable, we must overwrite the zval
 * pointed to by $y, rather than simply make $y point to a new zval. 
 *
 * The point of this test is that $y first points to a zval containing a string,
 * and therefore as some additional memory associated with it (the value of the 
 * string). We must therefore be careful to call the destructor on the old zval
 * before overwriting it.
 */

	$x = "a string";
	$y =& $x;

	$y = 5; 			// (*)
	var_export($y);
?>
