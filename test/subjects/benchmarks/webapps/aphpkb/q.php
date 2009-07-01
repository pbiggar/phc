<?php // Submit Authored Article
$adfl = FALSE; 
include_once ('config/config.php');
include_once ('functions.php');
include_once ('config/dbsettings.php');

$title = "Question";
$aid = mifi($_REQUEST['aid']);

if(isset($_POST['submit'])) {  

 	$message = NULL;  
 
// sanitise user input

	$articledatae = escdata(xss_clean($_POST['article']) );	

// Form Validation
 
	// Check for Article. 
	if (strlen($articledatae) > 0) { 
	
	$article = TRUE; 
	
	// create keywords from question words greater than 4 letters.
	$arrkeywords = explode(' ', $articledatae);

foreach ($arrkeywords as $keyword) {
	if(strlen($keyword)>4){
		$keywords .= ' ' .  $keyword;
	}
	}
	
	
	
	} else { 
	$article = FALSE; 
	$message .= 'You need to include the question.  '; 
	} 
 
	
 
	if ($article) { 
	
// If everythings okay.
	
	$aquery = "INSERT into articles (Title, AuthorID, Articledata, Keywords, Approved) VALUES ('$title','$aid', '$articledatae' , '$keywords', 'Q')"; 
	$title = "Your question has been submitted.";
	$result = mysql_query($aquery); 
	$fileid = mysql_insert_id(); // FileID

	if (mysql_errno())	{
			   echo "MySQL error ".mysql_errno().": ".mysql_error()."\n<br />When executing:<br />\n$query\n<br>";
				} 
	} else { 	
// if not okay	
 
	$title = 'Submission Failed - Please try again<br /><br />'; 
	}


head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

$articledata = stripslashes($articledatae);

echo '<p>Article Details</p>';

echo "<p>Question:<br />$articledata</p>";
if($keywordse) { echo "<p>Keywords:  $keywordse</p>"; }
exit();
	
} // end of if submit
   
// Set the page title and include the HTML header. 
$title = 'Question';

head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

// Print the error message if there is one. 
 
    if (isset($message)) { 
    	echo '<font color="red">', $message, '</font>'; 
    } 
?>
<p>
Use the form below to submit a question for inclusion into the knowledgebase.<br />
End-users are welcome to submit questions relating to the Product or Service.
</p>

<form form enctype="multipart/form-data" action="<?php echo $_SERVER['PHP_SELF']; ?>" method="POST" name="articleform"> 


<p>Question:<br /> <?php
$textareaname = 'article';

if (isset($articledatae)) {

	$textareacontent = $articledatae;

	} else { $textareacontent=''; }
	include('./textarea.php'); 
	?>
</p> 
 <input type="hidden" name="aid" value="<?php echo $aid; ?>" />
<p><input type="submit" name="submit" value="Submit Question" /><input type="reset" Value="Clear All" /></p> 
</form> 
<?php foot_page();?> 