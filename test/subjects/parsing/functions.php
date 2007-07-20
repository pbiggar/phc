<?php
	class C {}

	function a($x, $y) {}
	function b(&$x, &$y) {}
	function c1(C $x, D $y) {}
	function c2(array $x, array $y) {}
	function &d(C &$x, D &$y) {}
	
	function e($x = NULL, $y = NULL) {}
	function f(&$x = NULL, &$y = NULL) {}
	function g(C $x = NULL, D $y = NULL) {}
	function g(array $x = NULL, array $y = NULL) {}
	function &h(C &$x = NULL, D &$y = NULL) {}
	
	class D 
	{
		function da($x, $y) {}
		function db(&$x, &$y) {}
		function dc(C $x, D $y) {}
		function dc(array $x, array $y) {}
		function &dd(C &$x, D &$y) {}
		
		function de($x = NULL, $y = NULL) {}
		function df(&$x = NULL, &$y = NULL) {}
		function dg(C $x = NULL, D $y = NULL) {}
		function dg(array $x = NULL, array $y = NULL) {}
		function &dh(C &$x = NULL, D &$y = NULL) {}
	}
?>
