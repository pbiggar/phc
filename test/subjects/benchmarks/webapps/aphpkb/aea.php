<?php // Author Edit Article

include_once ('functions.php');
include_once ('config/config.php');
include_once('config/dbsettings.php');
$title = "Edit Article";
$fileid = mifi(escdata(xss_clean($_REQUEST['fileid']) ));
$aid = mifi(escdata(xss_clean($_REQUEST['aid']) ));
$authorid = $aid;

if (isset($_SESSION['first_name'])) { $enum=TRUE; }

if(isset($_REQUEST['submit'])) {  

 	$message = NULL;  
 
// sanitise user input
	
	$titlee = escdata(xss_clean($_POST['title']) ); 
	$keywordse = escdata(xss_clean($_POST['keywords']) ); 
	$articledatae = escdata(xss_clean($_POST['article']) );	
	$descriptione = escdata(xss_clean($_POST['description']) );
 
// Form Validation
 
	// Check for Title. 
	if (strlen($titlee) > 0) { $title = TRUE; 
	} else { 
	$title = FALSE; 
	$message .= 'You need to include a title for the article.  '; 
	} 
 
	// Check for Article. 
	if (strlen($articledatae) > 0) { $article = TRUE; 
	} else { 
	$article = FALSE; 
	$message .= 'You need to include the article.  '; 
	} 
 
	// Check for Keywords. 
	if (strlen($keywordse) > 0) { $keywords = TRUE; 
	} else { 
	$keywords = FALSE; 
	$message .= 'You need to include keywords for the article  '; 
	} 
 
	if ($title && $article && $keywords) { 
	
// If everythings okay.
	
$query="UPDATE articles SET Title='$titlee', Articledata='$articledatae', Keywords='$keywordse' WHERE FileID='$fileid'";

		$title = 'Your article has been saved.';
		
	$result = mysql_query($query); 
	
	if (mysql_errno())	{
			   echo "MySQL error ".mysql_errno().": ".mysql_error()."\n<br />When executing:<br />\n$query\n<br>";
				} 
	} else { 
	
// if not okay	
 
	$title = 'Submission Failed - Please try again<br /><br />'; 
}
	if(proscribedfiletypes($_FILES['upload']['type'])=='FALSE'){
	// Add the upload record to the database.
	$uquery = "INSERT INTO uploads (AuthorID, FileID, FileName, FileType, FileDescription, UploadDate) VALUES ('$aid' , '$fileid',  '{$_FILES['upload']['name']}' , '{$_FILES['upload']['type']}', '$descriptione', NOW())";
	$uresult = @mysql_query ($uquery);

	if ($uresult) {
		
		// Create the file name.
		$uid = mysql_insert_id(); // UploadID
		$filename = $uid . '-' . $aid . '-' . $fileid . '-' . $_FILES['upload']['name'];
		
		// Move the file over.
		if (move_uploaded_file($_FILES['upload']['tmp_name'], "./attach/$filename")) {
			$attachmessage = '<p>Attachment file has been processed!</p>';
		} else {
			//$attachmessage = '<p><font color="red">The file could not be moved.</font></p>';

			// Remove the record from the database.
			$query = "DELETE FROM uploads WHERE UploadID = $uid";
			$result = @mysql_query ($query);
		}
		
	} else { // If the query did not run OK.
		$attachmessage .= ''; 
	}
	}
	
$dbkeywords = $keywordse;	 
head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

$articledata = stripslashes($articledatae);

echo <<<_EOF
<p>Article Details</p>
<p>Title:  $titlee</p>
<p>Article:<br />$articledata</p>
<p>Keywords:  $keywordse</p>
$attachmessage
_EOF;

foot_page();
exit();
} // end of if submit
   
// Set the page title and include the HTML header. 
$title = 'Edit Article';

head_page($title); 
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);
// Print the error message if there is one. 
 
    if (isset($message)) { 
    	echo '<font color="red">', $message, '</font>'; 
    } 

$query2 = "SELECT Title, AuthorID, Approved, Keywords, Articledata from articles WHERE FileID='$fileid' LIMIT 1";

	$result2 = mysql_query($query2); 
	while ($row = mysql_fetch_array ($result2, MYSQL_ASSOC)) { 
	$title = $row['Title']; 
	$aid = $row['AuthorID'];	
	$keywords = $row['Keywords'];
	$pending = $row['Approved'];
	$articledatae = xss_clean($row['Articledata']);
    
    } 
?>

<form form enctype="multipart/form-data" action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post" name="articleform"> 

<p>Title:<br /> 
<input type="text" name="title" size="60" maxlength="60" value="<?php echo $title; ?>" /></p> 

<?php
if (isset($articledatae)) {

	$textareacontent = stripslashes($articledatae);
	
	} else { $textareacontent=$articledata; }
$textareaname='article';
if(PLUGINWHIZZYWIG=='1') { 

	include('./plugins/whizzywig/plugin-textarea.php'); 

	} else { 

	include('./textarea.php'); 

	}
?>

 
 <p>Article Keywords:<br /> 
<input type="text" name="keywords" size="60" maxlength="120" value="<?php echo $keywords ?>" /></p> 


<?php  
echo "
<input type=\"hidden\" name=\"aid\" value=\"$aid\">
<input type=\"hidden\" name=\"fileid\" value=\"$fileid\">
<input type=\"hidden\" name=\"vnum\" value=\"$enum\">

<p>File:  <font color=\"green\"><i>(Optional)</i></font><br /><input type=\"file\" size=\"35\" name=\"upload\" /></p>
<p>Description: <font color=\"green\"><i>(Optional, but required if uploading file above)</i></font> <br /> <textarea name=\"description\" cols=\"40\" rows=\"5\"></textarea></p>
";
$submitvalue='Submit';
?> 
 
 <input type="hidden" name="aid" value="<?php echo $aid; ?>" />
 
 
<p> 
<input type="submit" name="submit" value="<?php echo $submitvalue; ?>" /><input type="reset" Value="Reset" /></p> 
</form> 

</td>

<?php // Include the HTML footer file. 
foot_page(); 
?> 
