<?php // logout.php
include('./config/config.php');
include('functions.php');

// If no first_name variable exists, redirect the user.
if (!isset($_SESSION['first_name'])) {

	header ("Location:  http://" . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']) . "/index.php");
	ob_end_clean(); // Delete the buffer.
	exit(); // Quit the script.
	
} else { // Logout the user.

	$_SESSION = array(); // Destroy the variables.
	session_destroy(); // Destroy the session itself.
	setcookie (session_name(), '', time()-300, '/', '', 0); // Destroy the cookie.
	header ("Location:  http://" . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']) . "/index.php");
}
?>