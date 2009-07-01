<?php // aal.php Author's Article List
  include_once"./config/dbsettings.php";
  
// luckily we already know the the $authorid - if we don't then we should shunt the visitor to index.php
if (!isset($_SESSION['first_name'])) {

	header ("Location:  http://" . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']) . "/index.php");
	ob_end_clean();
	exit();
	
} else {

if(isset($_SESSION['user_id'])) { $authorid = $_SESSION['user_id']; }
$first = TRUE; 
   
$query = "SELECT FileID, Title, Articledata, Approved FROM articles WHERE AuthorID='$authorid' ORDER by FileID"; 
$result = mysql_query($query); 
 
// Display all the URLs 
while ($row = mysql_fetch_array ($result, MYSQL_ASSOC)) {	 
// If this is the first record, create the table header.	 


$a = $row['FileID'];
$approved = $row['Approved'];

$articledata = $row['Articledata'];
$title = $row['Title'];

if ($first) 	{ 
echo '<p>Here is a list of your articles and their status:</p>';
		} // end of if($first)  
 switch($approved) {

	case('Y'):
		$status='Approved';
		$aviewlink = "<a href=\"v.php?a=$a\">$title</a>"; 
	break;
	
	case('N'):
		$status='Pending';
		$aviewlink = "<a href=\"aea.php?fileid=$a&enum=TRUE\">$title</a>";
	break;
	
	case('S'):
		$status='<a href="ssa.php?fileid=' . $a . '">Submit</a>';
		$aviewlink = "<a href=\"aea.php?fileid=$a&enum=TRUE\">$title</a>";
	break;
} //end of switch($approved)

echo $aviewlink . '<br />';;
echo strip_tags(substr($articledata,0,52) . '...');
echo "<font color=\"red\">[</font> $status - <a href=\"aea.php?fileid=$a&enum=TRUE\">Edit</a> - <a href=\"ada.php?num=$a\">Del</a><font color=\"red\">]</font>";

$upfirst = TRUE; 
$upquery = "SELECT UploadID, AuthorID, FileID, FileName, FileDescription FROM uploads WHERE FileID='$a' ORDER by FileID"; 
$upresult = mysql_query($upquery); 
 
// Display all the URLs 
while ($row = mysql_fetch_array ($upresult, MYSQL_ASSOC)) {	 
// If this is the first record, create the table header.	 


$uid = $row[UploadID];
$aid = $row[AuthorID];
$num = $row[FileID];
$filename = $row[FileName];
$description = $row[FileDescription];
$attachedurl = "<a href=\"" . KBURL . "attach/$uid-$aid-$num-$filename\">$description</a><font color=\"red\">[</font><a href=\"adu.php?uid=$uid\">Del</a><font color=\"red\">]</font>";
if ($upfirst && $uid) { 
	echo '&nbsp; <i>Attached: </i>';
				}

if($upfirst ==FALSE) { echo ', ';}
echo $attachedurl;
$upfirst = FALSE;

// One record has been returned 
 
} //end of while ($upresultresult)  
$first= FALSE;
echo '<br /><br />';
}// end of while ($result)
if ($first)   {	 
     echo '<div align="center"><br /><br />You have no articles yet, you can <a href="saa.php?aid=' . $authorid .'">create</a> an article.<br /></div>'; 
		} // end of if($first) 


} // end of if($_SESSION['first_name'])
?>