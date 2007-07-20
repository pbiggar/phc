<?php


	function c1(C $x, D $y) {}
	function c2(array $x, array $y) {}
	function g(C $x = NULL, D $y = NULL) {}
	function g(array $x = NULL, array $y = NULL) {}
	class D
	{
		function dc(C $x, D $y) {}
		function dc(array $x, array $y) {}
		function dg(C $x = NULL, D $y = NULL) {}
		function dg(array $x = NULL, array $y = NULL) {}
	}
?>
