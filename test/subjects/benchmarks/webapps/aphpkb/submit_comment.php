<?php // Submission page. 
$adfl = FALSE; 
include_once ('config/config.php');
include_once ('functions.php');
  include "./classes/mysql.class.php";
 $mysqldb = new mysql();
 $mysqldb->connect();
 $mysqldb->select(); 

$parentid = mifi($_REQUEST['parentid']) ; 

$mysqldb->query("SELECT Title from articles where FileID ='$parentid'");
    $result = mysql_query($query); 
 $row = $mysqldb->fetchObject();
	$title = "Re: $row->Title"; 


if(isset($_POST['submit'])) {
	// Handle the Form
	
	$message = NULL;
	// Create an empty new variable.
	
	
	// sanitise user input

	//$titlee = escdata( xss_clean($_POST['commenttitle']) );
	//$articledatae = escdata( xss_clean($_POST['article']) );
	
	$titlee = xss_clean($_POST['commenttitle']) ;
	$articledatae = xss_clean($_POST['article']) ;
	
	
	// Validate user input
	
		// Check for Title. 
	if (strlen($titlee) > 0) { $title = TRUE; 
	} else { 
	$title = FALSE; 
	$message .= 'You need to include a title for your comment.  '; 
	} 
 
	// Check for Article. 
	if (strlen($articledatae) > 0) { $article = TRUE; 
	} else { 
	$article = FALSE; 
	$message .= 'You need to include the comment.  '; 
	} 
 
	
	
	if ( $title && $article) { 
	
	// If everythings okay.
	
	$insquery = "INSERT into articles (ParentID, Title, Articledata) VALUES ('$parentid', '$titlee', '$articledatae')";
 
	$insresult = mysql_query($insquery); 

	if (mysql_errno())	{
			   echo "MySQL error ".mysql_errno().": ".mysql_error()."\n<br>When executing:<br>\n$query\n<br>";
	   } 

	$title = "Your comment has been submitted for inclusion in the Knowledge base"; 
 
	} else { 
 
	$title = 'Submission Failed - Please try again' . $insquery; 
 
	} 


  
// Set the page title and include the HTML header.
head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

// Print the error message if there is one. 
 
if (isset($message)) { 
 
	echo '<font color="red">', $message, '</font>'; 
} 

$newcommenttitle=stripslashes($titlee);
$newcomment=stripslashes($articledatae);


echo<<<_NEWCOMMENT
<p>
Comment Title:  $newcommenttitle<br />
<br />
Comment:<br />
<br />
$newcomment
<br />
</p>
_NEWCOMMENT;
} else {  
 
head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);
// Print the error message if there is one. 
 
if (isset($message)) { 
 
	echo '<font color="red">', $message, '</font>'; 
} 

?> 

<?
if(isset($_POST['submit']))	{

foot_page(); 
exit;
}
?>

<p>
Use the form below to submit a comment on this article for inclusion into the knowledgebase.
End-users are welcome to submit comments on any articles.
</p>
<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="POST"> 
Submit a comment in response to the knowledgebase article. The comments  may be modified by the Knowledgebase Administrator. Before
posting the comment will be reviewed and may be edited for brevity, structure and content.

<input type="hidden" name="parentid" value="<?php echo $parentid ?>">

<p>Title:<br /> 
<input type="text" name="commenttitle" size="40" maxlength="60" value="<?php echo $title ?>" /></p> 
 
<p>Comment Text:<br /> 
<textarea name="article" cols="60" rows="5"><?php if (isset($_POST['article'])) echo $_POST['article']; ?></textarea> 
</p> 
<p> 
<input type="submit" name="submit" value="Submit" /><input type="reset" Value="Clear All" /></p> 
</form> 

</td>

<?php // Include the HTML footer file. 
}
foot_page();
?> 