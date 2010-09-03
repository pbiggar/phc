<?php

require_once('include.php');

if (isset($_POST['sessionname'])) {
	$_SESSION['phpSQLiteAdmin_currentdb'] = $_POST['sessionvalue'];
} else {
	$_SESSION['phpSQLiteAdmin_currentdb'] = "phpsla.slqite";
}

header("Location: index.php");
exit;

?>