<?php
	
	class Foo
	{
		
		var $x;
		
		function Foo()
		{
			$this->x = array('bar');
		}
		
		function bar()
		{
			echo "foo::bar\n";
		}
		
		function y()
		{
			echo "y\n";
		}
		
	}

	function bar()
	{
		echo "bar\n";
	}
	
	$a = new Foo();
	
	$a->x[0]();	// bar
	$a->y();		// foo:y
	
	$a->{$a->x[0]}();	// foo:bar
?>
