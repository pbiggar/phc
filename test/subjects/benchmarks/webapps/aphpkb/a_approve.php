<?php // a_aprove.php Admin Article Approval

include('./functions.php');
require_once ('./config/auth.php'); 
include_once('./config/config.php');
include"./config/dbsettings.php";

$fileid = mifi($_REQUEST['fileid']); 
$first = TRUE; 
$query = "UPDATE articles SET Approved='Y' where FileID='{$fileid}' LIMIT 1"; 
$result = mysql_query($query); 
$title = 'Approved';


//updaterss();

$query = "SELECT AuthorID, Title, Articledata, Keywords  FROM articles where FileID = '$fileid'";

    $result = mysql_query($query);
	while ($row = mysql_fetch_array ($result, MYSQL_ASSOC)) {
	
    $authorid = "{$row['AuthorID']}";
    $atitle = "{$row['Title']}";
    $articledata = "{$row['Articledata']}";
    $kpa = $row['Keywords'];
  }
$title = $atitle . ' article ' . $page_title;
head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);
echo '<div id="articlespace">';
//--article space begins -----

$articledata = ereg_replace("[[:alpha:]]+://[^<>[:space:]]+[[:alnum:]/]", "<a target=\"_blank\" href=\"\\0\">\\0</a>", $articledata);
$articledata = ereg_replace("\n", "<br />", $articledata);

$authorquery = "SELECT FirstName, LastName FROM authors WHERE AuthorID='$authorid'";

$result = mysql_query($authorquery); 
	while ($row = mysql_fetch_array ($result, MYSQL_ASSOC)) { 
	$authorname = $row['FirstName'] . ' ' . $row['LastName']; 
}
if(strlen($authorname)<1){$authorname = 'Guest';}


// place keywords into tags table.
	$arrkeywords = explode(' ', $kpa);
	$firsttime = "TRUE";
foreach ($arrkeywords as $keyword) {
	if(strlen($keyword)>4){
		$k2tquery = "INSERT INTO tags (fileid, tag) VALUES ('$fileid', '$keyword')";
		$k2tresult = mysql_query($k2tquery); 
	}
}
if(PLUGINRSS==1){
	updaterss();
}

echo<<<_ARTICLEDETAILS
<br />
Title : $atitle<br />
Author : $authorname<br />
Keywords : $kpa
<br />
_ARTICLEDETAILS;

echo stripslashes($articledata);
 
foot_page(); 
?>