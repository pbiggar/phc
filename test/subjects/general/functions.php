<?php
	class C {}

	function a($x, $y) {}
	function b(&$x, &$y) {}
	function c(C $x, D $y) {}
	function c(array $x, array $y) {}
	function &d(C &$x, D &$y) {}
	
	function e($x = 0, $y = 0) {}
	function f(&$x = 0, &$y = 0) {}
	function g(C $x = 0, D $y = 0) {}
	function g(array $x = 0, array $y = 0) {}
	function &h(C &$x = 0, D &$y = 0) {}
	
	class D 
	{
		function da($x, $y) {}
		function db(&$x, &$y) {}
		function dc(C $x, D $y) {}
		function dc(array $x, array $y) {}
		function &dd(C &$x, D &$y) {}
		
		function de($x = 0, $y = 0) {}
		function df(&$x = 0, &$y = 0) {}
		function dg(C $x = 0, D $y = 0) {}
		function dg(array $x = 0, array $y = 0) {}
		function &dh(C &$x = 0, D &$y = 0) {}
	}
?>
