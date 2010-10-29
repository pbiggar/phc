<?php

/* 
 * Issue 130, reported by catapuit2000-php@yahoo.de.
 *
 * The return statement does not properly shred, and doesn't convert properly 
 * to HIR because of the field access.
 */

class X
{
	function __construct ()
	{
		$this->propertyName = "str";
	}

	function checkColor( &$color )
	{
		return $color;
	}

	function __get( $propertyName )
	{
		return ( $this->$propertyName = $this->checkColor( $this->$propertyName ) );
	}
}

$x = new X();

?>
