<?php
	/**
	 * Date: 2005/11/02
	 * Reported by: Paul Biggar
	 * Reported for: 0.1
	 * Fixed in: 0.1.1
	 *
	 * Unparsing this script gives
	 *
	 * 	"$a = "[\x00\x00\x00\x00\x00\x00\x00\n\x00\x00" . $b . "]"
	 *
	 * for the first line.
	 */
	
	$a = "[$b]";

	/*
	 * Extra test cases
	 */

	$a = "[]";
	$a = "$b";
	$a = " $b";
	$a = "e$b";
	$a = "ee$b";
	$a = "ee $b";
	$a = "ee   $b";
	$a = "a $b c";
	$a = "\001\002 $b \003\004";
	$a = "\000\001\002 $b \003\004\005";
?>
