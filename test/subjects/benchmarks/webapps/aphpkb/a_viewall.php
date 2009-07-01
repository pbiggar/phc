<?php // view_all.php View all Articles
 
//Set Authentication for the Admin Area 
 
$adfl = TRUE; 
$acq='a';
$title = 'View All Articles';


include('./functions.php');
include"./config/config.php";
require_once ('./config/auth.php');
  include "./classes/mysql.class.php";
if($_REQUEST['type']){
// this uses the delete function.

$type = $_REQUEST['type'];
$id = $_REQUEST['id'];

$pagetitle = delete($type, $id);
}




head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);
$first = TRUE; 
   
$query = "SELECT FileID, Title, AuthorID, Approved, DATE_FORMAT(Submitdate, '%e %M, %Y') AS date FROM articles WHERE ParentID='0'  ORDER by FileID"; 
$result = mysql_query($query); 
 
// Display all the URLs 
while ($row = mysql_fetch_array ($result, MYSQL_ASSOC)) {	 
// If this is the first record, create the table header.	 

$approved = $row['Approved'];
$fileid = $row['FileID'];
$title = $row['Title'];
$authorid = $row['AuthorID'];
$date = $row['date'];

if ($first) { 

echo '<table border="0" width="98%" cellspacing="3" cellpadding="3" align="center"><tr> 
<td align="left" width="30%"><small>Title</small></td> 
<td align="left" width="20%"><small>Author</small></td> 
<td align="right" width="20%"><small>Last Updated</small></td> 
<td align="right" width="30%"><small>Approve-Edit-Delete</small></td>	 
</tr>';	}  
 
// End of first IF 
// Display each record.	 
echo " <tr><td align=\"left\"><a href=\"v.php?a=$fileid\">$title</a>"; 

if(!$authorid) { $authorid = 'Guest'; 
echo "<td align=\"left\">$authorid</td>"; 
} else {

  $authorsql = "SELECT FirstName, LastName FROM authors WHERE AuthorID='$authorid'";
  $authorresult = mysql_query($authorsql); 
  $arow = mysql_fetch_array($authorresult, MYSQL_ASSOC);
  $authorname = $arow['FirstName']  . ' ' . $arow['LastName'];

echo "<td align=\"left\"> 
<a href=\"a_authord.php?aid=$authorid\">$authorname</a></td>"; 
}


echo "<td align=\"center\">$date</td>"; 


switch($approved){

case('Y'):
$approval = 'Approved';
break;

case('N'):
$approval = '<a href="a_approve.php?fileid=' . $fileid . '">Approve</a>&nbsp;';
break;

case('S'):
$approval = 'Saved Only';
break;
}

echo "<td align=\"right\">$approval
<a href=\"a_edita.php?num=$fileid\">Edit</a>&nbsp;&nbsp;<a href=\"a_viewall.php?acq=$acq&type=a&id=$fileid\">Delete</a>

</td> 

</tr>\n";	 
 
$first = FALSE;  
 
// One record has been returned 
 
}  
// End of While loop 
// If no records were displayed... 
if ($first) {	 
 
     echo '<div align="center"><br /><br />There are currently no articles to view.<br /></div>'; 
 
} else {	 
 
echo '</table>';  
// Close the table. 
} 
foot_page();
?>