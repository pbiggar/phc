<?php // Submit Authored Article
$adfl = FALSE; 
include_once ('config/config.php');
include_once ('functions.php');
include_once ('config/dbsettings.php');

$title = "Submit Article";
$aid = mifi($_REQUEST['aid']);
$ans = mifi($_REQUEST['a']);

if (isset($_SESSION['first_name'])) { $enum=TRUE;   }



 	$message = NULL;  
 
// sanitise user input
	
	$titlee = escdata(xss_clean($_POST['title']) ); 
	$keywordse = escdata(xss_clean($_POST['keywords']) ); 
	$productide = escdata(xss_clean($_POST['productid']) ); 
	$articledatae = escdata(xss_clean($_POST['article']) );	
	$savestatus = xss_clean($_POST['savestatus']);
	$descriptione = escdata(xss_clean($_POST['description']) );
if(isset($_POST['submit'])) {  
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
	
        if($savestatus=='save') 
		{ 
		$aquery = "INSERT into articles 
		(Title, AuthorID, Articledata, Keywords, Approved) 
		VALUES 
		('$titlee','$aid', '$articledatae' , '$keywordse', 'S')"; 
		
		$title = "Your article has been saved for future editing and submission";
		
		} else {
		
		$aquery = "INSERT into articles 
		(Title, AuthorID, Articledata, Keywords) 
		VALUES 
		('$titlee','$aid', '$articledatae' , '$keywordse')"; 
	
		$title = "Your article has been submitted for approval";
		
		}

	$result = mysql_query($aquery); 
	$fileid = mysql_insert_id(); // FileID

	if (mysql_errno())	{
			   echo "MySQL error ".mysql_errno().": ".mysql_error()."\n<br />When executing:<br />\n$query\n<br>";
				} 
	} else { 
	
// if not okay	
 
	$title = 'Submission Failed - Please try again<br /><br />'; 
	}
	
	if(proscribedfiletypes($_FILES['upload']['type'])=='FALSE'){
	
	
	

	
	// Add the attachment record to the database.
	$uquery = "INSERT INTO uploads (AuthorID, FileID, FileName, FileType, FileDescription, UploadDate) VALUES ('$aid' , '$fileid',  '{$_FILES['upload']['name']}' , '{$_FILES['upload']['type']}', '$descriptione', NOW())";
	$result = @mysql_query ($uquery);

	if ($result) {
		
		// Create the file name.
		$uid = mysql_insert_id(); // UploadID
		$filename = $uid . '-' . $aid . '-' . $fileid . '-' . $_FILES['upload']['name'];
		
		// Move the file over.
		if (move_uploaded_file($_FILES['upload']['tmp_name'], "./attach/$filename")) {
			$attachmessage = '<p>Attachment file has been processed!</p>';
		} else {
			//$attachmessage = '<p><font color="red">The file could not be moved.</font></p>';

			// Remove the record from the database.
			$dquery = "DELETE FROM uploads WHERE UploadID = $uid";
			$result = @mysql_query ($dquery);
		}
		
	} else { // If the query did not run OK.
		$attachmessage .= '<p><font color="red">Attachment could not be processed due to a system error.  We apologize for any inconvenience.</font></p>'; 
	}
	}

head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

$articledata = stripslashes($articledatae);

echo '<p>Article Details</p>';
if($titlee) { echo "<p>Title:  $titlee</p>"; }
echo "<p>Article:<br />$articledata</p>";
if($keywordse) { echo "<p>Keywords:  $keywordse</p>"; }
echo "$attachmessage
<br />";

if($ans){

$ansquery = "UPDATE articles SET ParentID='$fileid', Approved='A' WHERE FileID='$ans'";
echo "Q & A Updated.";
		
		

	$result = mysql_query($ansquery); 


	if (mysql_errno())	{
			   echo "MySQL error ".mysql_errno().": ".mysql_error()."\n<br />When executing:<br />\n$query\n<br>";
				} 

}
exit();
	
} // end of if submit

if($ans){
$qquery = "SELECT ArticleData FROM articles WHERE FileID='$ans' LIMIT 1";
	$qresult = mysql_query($qquery); 
while ($row = mysql_fetch_array ($qresult, MYSQL_ASSOC)) {	 
$question = $row['ArticleData'];
}
$questionbox = 'Question : <font color="red">' . $question . '</font><br /><br />';
}
// Set the page title and include the HTML header. 
$title = 'Submit Article';

head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

// Print the error message if there is one. 
 
    if (isset($message)) { 
    	echo '<font color="red">', $message, '</font>'; 
    } 
    echo $questionbox;
?>

<form form enctype="multipart/form-data" action="<?php echo $_SERVER['PHP_SELF']; ?>" method="POST" name="articleform"> 

<p>Title:<br /> 
<input type="text" name="title" size="60" maxlength="60" value="<?php if (isset($_POST['title'])) echo $_POST['title']; ?>" /></p> 

<p>Article:<br /> <?php
$textareaname = 'article';

if (isset($articledatae)) {
	$textareacontent = $articledatae;
	} else { $textareacontent=''; }

if(PLUGINHTML=='1') { 
	include('./plugins/whizzywig/plugin-textarea.php'); 
	} else { 
	include('./textarea.php'); 
	}
	?>
</p> 
 <p>Article Keywords:<br /> 
<input type="text" name="keywords" size="60" maxlength="120" value="<?php if (isset($_POST['keywords'])) echo $_POST['keywords']; ?>" /></p> 

<?php  
if($aid!=0){ // if this is a guest submission, we will not include attachments.  Fairly sure it wouldn't work.

echo "
<input type=\"hidden\" name=\"aid\" value=\"$aid\">
<p>File:  <font color=\"green\"><i>(Optional)</i></font><br /><input type=\"file\" size=\"35\" name=\"upload\" /></p>
<p>Description: <font color=\"green\"><i>(Only required if uploading a file above)</i></font> <br /> <textarea name=\"description\" cols=\"40\" rows=\"5\"></textarea></p>
";

echo '<p>
 <input type="checkbox" name="savestatus" value="save" />Save Only (do not submit for approval)
 </p>'; 

$submitvalue='Submit/Save';
} else {
$submitvalue='Submit';
}
 ?> 
 
 <input type="hidden" name="aid" value="<?php echo $aid; ?>" />
 <input type="hidden" name="a" value="<?php echo $ans; ?>" />
 
<p> 
<input type="submit" name="submit" value="<?php echo $submitvalue; ?>" /><input type="reset" Value="Clear All" /></p> 
</form> 
</td>
<?php foot_page();?> 