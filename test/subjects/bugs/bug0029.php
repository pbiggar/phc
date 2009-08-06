<?php

// Reported by Alberto Bachelli
// This segfaulted since there was no parent.
// { phc-warning: Attempt to use 'parent::' in a class with no parent class }
class Stack
{
	private function __construct( $input )
	{
		parent::__construct( $input );
	}
}
?>
