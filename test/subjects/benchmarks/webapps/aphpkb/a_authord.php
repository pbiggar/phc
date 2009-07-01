<?php // a_authord.php -- Admin view Author Details

include('./functions.php');
require_once ('./config/auth.php'); 
require ('./config/config.php');
include"./config/dbsettings.php";


$num = $_GET[aid];  
$query = "SELECT CONCAT(FirstName, ' ', LastName) AS name, UserName, Email, DATE_FORMAT(RegistrationDate, '%M %d, %Y') AS dr FROM authors WHERE AuthorID='{$num}'";

    $result = mysql_query($query); 
	while ($row = mysql_fetch_array ($result, MYSQL_ASSOC)) { 

$username = $row['UserName'];
$name = $row['name'];
$email = $row['Email'];
$authorid = $num;
$regdate = $row['dr'];
}

// pending articles count
$query = "SELECT count(*) from articles WHERE Approved = 'N' AND AuthorID='$authorid'";
$result = mysql_query($query);
$row = mysql_fetch_row ($result);
$pendingarticles = $row[0];

// approved articles count
$query = "SELECT count(*) from articles WHERE Approved = 'Y' AND AuthorID='$authorid'";
$result = mysql_query($query);
$row = mysql_fetch_row ($result);
$approvedarticles = $row[0];

// saved articles count
$query = "SELECT count(*) from articles WHERE Approved = 'S' AND AuthorID='$authorid'";
$result = mysql_query($query);
$row = mysql_fetch_row ($result);
$savedarticles = $row[0];
$totalarticles = $approvedarticles + $pendingarticles + $savedarticles;
$title = 'Viewing Author Details : ' . $name;

head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);
echo <<<_AUTHORDETAILS
AuthorID : $authorid<br />
UserName : $username<br />
Full Name : $name<br />
Email Address : $email<br />
RegistrationDate : $regdate<br />
<br />
Approved Articles : $approvedarticles<br />
Pending Articles : $pendingarticles<br />
Saved Articles : $savedarticles<br />
<br />
Total Articles : $totalarticles<br />
</td>
_AUTHORDETAILS;
foot_page();
?>