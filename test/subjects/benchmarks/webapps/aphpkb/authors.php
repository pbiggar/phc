<?php //authors.php
$title = 'Author Page';

$vnum='';
$viewop='';
$pid='';
$keys='';
$adfl='';
include('config/config.php');
include('functions.php');
head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

echo 'Welcome';
if (isset($_SESSION['first_name'])) {
	echo ", {$_SESSION['first_name']}!";

if (isset($_SESSION['user_id'])) { $aid = $_SESSION['user_id']; }

	$authorsql = "SELECT AuthorID FROM authors WHERE AuthorID = '$aid'";
	    $result = mysql_query($authorsql); 
	while ($row = mysql_fetch_array ($result, MYSQL_ASSOC)) { 
	$authorid = "{$row['AuthorID']}"; 
}


include('aal.php');
} else {
echo <<<_EOF
 Guest<br />
<p>Feel free to create a guest <a href="./saa.php">article</a>, or <a href="login.php">Login<a/>.</p>
_EOF;
}
foot_page();
?>