<?php // delete.php Delete Upload
// Set the page title and include the HTML header. 

include('./config/config.php');
include('functions.php');

$title = 'Delete Upload'; 

head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);
 
$uid = mifi($_GET['uid']); 
// must be the author of this article to be able to delete it.
if (!isset($_SESSION['first_name'])) {

	header ("Location:  http://" . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']) . "/index.php");
	ob_end_clean();
	exit();
	
} else {

$first = TRUE; 

$query = "DELETE from uploads WHERE UploadID='{$uid}' AND AuthorID='{$_SESSION['user_id']}'"; 

$result = mysql_query($query); 

echo "Upload Deleted!<br /> 
</td></tr>\n";	 
foot_page();} 
?>