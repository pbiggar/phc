<?php // a_aprovec.php Admin Comment Approval

include('./functions.php');
require_once ('./config/auth.php');
include_once('./config/config.php');
include"./config/dbsettings.php";

$title = 'Comment Approval'; 
head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);
 
$num = mifi($_REQUEST['num']); 
 
// Connect to the database 
 
$first = TRUE; 
   
$query = "UPDATE articles SET Approved='Y' where FileID='{$num}' LIMIT 1"; 
$result = mysql_query($query); 
 
echo "Comment Approved!<br /> 
</td></tr>\n";	  
foot_page(); 
?> 