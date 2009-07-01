<?php // auth.php 
if($_SESSION['adfl']!=TRUE) {
	header ("Location:  http://" . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']) . "/index.php");
	ob_end_clean();
	exit();
	}
?>