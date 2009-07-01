<?php

// Start output buffering and initialise a session.
ob_start();
session_start();

function xss_clean ($var) {
       $allowedTags =
'<font><p><strong><em><u><h1><h2><h3><h4><h5><h6><li><ol><ul><span><div><br><ins><del><b><pre><div><p><table><tbody><tr><td><th><li><hr><ul><ol>';

$var = strip_tags($var, $allowedTags);
      return $var;
}

function mifi($incoming) {
	if (is_numeric($incoming)) {
		return mysql_escape_string(intval($incoming));
	} 
	return '';
}

// Function for escaping and trimming form data.
function escdata ($data) { 
	global $dbc;
	if (ini_get('magic_quotes_gpc')) {
		$data = stripslashes($data);
	}
	return mysql_real_escape_string (trim ($data), $dbc);
} // End of escape_data() function.

function head_page($title) {
include('./html/header.html');
}

function menu_options($title, $a, $viewop, $pid, $keys, $adfl) {


echo '
<div id="navAlpha">
<div class="title">
<img src="./imgs/logo.png" width="45" alt="Andy Grayndler">
<br /><br />
</div>';

if($_SESSION['adfl']==TRUE) {
include"./html/adminmenu.html";
}
$searchwidth='100%';
include"search.php";

include"./inc/tags.php";

include"./html/articlemenu.html";


//include"./html/authormenu.html";

echo '</div>';
} //end of menu_options

function contentinit($title) {

echo '<div class ="navstrip">';
echo '&nbsp;&nbsp;<a href="' . KBHOMEURL . '" title="' . KBHOMEURL . '">'. stripslashes(KBNAME) . '</a>';
echo '&raquo; <a href="index.php" title="Knowledge Base">Knowledgebase</a> &raquo; <font color="red">';
echo stripslashes($title) . '</font><div align="right">';?>

<? if(isset($_SESSION['user_id']) AND (substr($_SERVER['PHP_SELF'], -10) != 'logout.php')):?>

<a href="logout.php">Logout</a> :: <a href="change_password.php">Change Password</a> :: <a href="authors.php">List Articles</a>

<?else:?>

<a href="login.php">Login</a> :: <a href="register.php">Register</a> :: <a href="forgot_password.php">Forgot Password</a>

  <?endif;?>

<?

echo 


'</div></div><div class ="content">';


}

function install_foot_page () {
echo '<br /></div></div><div class="footer">';
echo "<a href=\"http://www.aphpkb.org\">Andy's PHP Knowledgebase ";

$file='../docs/VERSION';
$fhr = fopen("$file", "r");
$data = fread($fhr,filesize($file)+1);
fclose ($fhr);
$version = substr($data,0,6); 
echo $version . '</a> &copy; Andy Grayndler 2008</div></body></html>';
}



function foot_page () {

echo '<br /></div><div class="footer">';
echo "<a href=\"http://www.aphpkb.org\">Andy's PHP Knowledgebase ";

$file='./docs/VERSION';
$fhr = fopen("$file", "r");
$data = fread($fhr,filesize($file)+1);
fclose ($fhr);
$version = substr($data,0,6); 
echo $version . '</a> &copy; Andy Grayndler 2008</div></body></html>';
}

function updaterss () {
$first = TRUE;
$maxrec = DB_MAX_REC;
$query = "SELECT FileID, Title, Articledata FROM articles WHERE Approved='Y' AND ParentID=0 ORDER by FileID DESC LIMIT $maxrec";

$result = mysql_query($query);
$num_records = @mysql_num_rows($result);

// Display all the URLs
while ($row = mysql_fetch_array ($result, MYSQL_ASSOC)) {	
// If this is the first record, create the table header.	
$linktitle = stripslashes($row['Title']);
$link = KBURL . '/v.php?a=' . $row['FileID'];
$description = strip_tags(substr(stripslashes($row['Articledata']),0,52) . '...');

$sitetitle = KBNAME;
$sitelink = KBURL;
$sitedescription = KBNAME . ' Knowledgebase';

if($first==TRUE) {
$output =
'<?xml version="1.0" encoding="utf-8"?>
<rss version="2.0">
<channel>
<title>' . $sitetitle . '</title>
<link>' . $sitelink . '</link>
<description>' . $sitedescription . '</description>

';
}

$output .= '
<item>
<title>' . $linktitle . '</title>
<link>' . $link . '</link>
<guid>' . $link . '</guid>
<description>' . $description . '</description>
</item>';
$first = FALSE; 
}

$output .= '
</channel>
</rss>';

// write the file
	$file = '../rss.xml';
	$fh = fopen($file, "w+");
	$status = fwrite($fh, $output);
	fclose($fh);
}

function delete($type, $id){
switch ($type){
case 'a':
$query = "DELETE from articles WHERE FileID='$id'"; 
$tagquery = "DELETE from tags WHERE fileid='$id'"; 
$del = 'Article Deleted';
break;

case 'c':
$query = "DELETE from articles WHERE FileID='$id'"; 
$del = 'Comment Deleted';
break;

case 'q':
$query = "DELETE from articles WHERE FileID='$id' AND Approved='Q'"; 
$del = 'Question Deleted';
break;
}
// run delete query
$mysqldb = new mysql();
$mysqldb->connect();
$mysqldb->select();
$mysqldb->query($query);

if($tagquery){
$mysqldb->query($tagquery);
}

if(PLUGINRSS){
updaterss();
}

return $del;
}







function proscribedfiletypes($type) {
switch ($type){
case 'application/x-httpd-php':
$type = 'TRUE';
break;

default:
$type = 'FALSE';
break;
}
return $type;
}

function errhandler($e_number, $e_message, $e_file, $e_line) {
	   if(PRODLEV==1){ error_reporting (0); } else { error_reporting (7); }
        $message = 'An error occurred in script ' . $e_file . ' on line ' . $e_line . ": $e_message";
        if(PRODLEV=='1'){        
	      /*uncomment out for email notification of errors and warnings */
	     // error_log ($message, 1, KBADMINEMAIL);
        	} else { 
		/* uncomment out for display errors and warning on page */
        	// echo '<font color="red" size="1">', $message, '</font>';
        }
}
set_error_handler('errhandler');
?>
