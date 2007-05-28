<?php


	function c1(C $x, D $y) {}
	function c2(array $x, array $y) {}
	function g(C $x = 0, D $y = 0) {}
	function g(array $x = 0, array $y = 0) {}
	class D
	{
		function dc(C $x, D $y) {}
		function dc(array $x, array $y) {}
		function dg(C $x = 0, D $y = 0) {}
		function dg(array $x = 0, array $y = 0) {}
	}
?>
