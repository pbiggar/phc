<?php // adminea.php Admin Edit Article
include('./functions.php');
require_once ('./config/auth.php');
include('./config/config.php');

$enum = mifi($_REQUEST['num']);
 
if(isset($_POST['submit'])) {  
        // Handle the Form 
 
	$message = NULL;  
        // Create an empty new variable. 
 
	// Check for Title. 
	if (strlen($_POST['title']) > 0) { $title = TRUE; 
	} else { 
	$title = FALSE; 
	$message .= 'needs a title, '; 
	} 
 
	// Check for Article. 
	if (strlen($_POST['article']) > 0) { $article = TRUE; 
	} else { 
	$article = FALSE; 
	$message .= 'needs content, '; 
	} 
 
	// Check for Keywords. 
	if (strlen($_POST['keywords']) > 0) { $keywords = TRUE; 
	} else { 
	$keywords = FALSE; 
	$message .= 'needs keywords, '; 
	} 
 
	if ($title && $article && $keywords) { // If everythings okay. 
 
	$titlesql = escdata($_POST['title']); 
	$keywordssql = escdata($_POST['keywords']); 
	$catidsql = mifi($_POST['catid']); 
    $articledatasql = escdata($_POST['article']);
	 
	$query = "UPDATE articles SET Title = '{$titlesql}', Articledata = '{$articledatasql}', Keywords = '{$keywordssql}' WHERE FileID='$enum'"; 
 
	$result = mysql_query($query); 
	
    $message .= "has been updated successfully.  This article "; 
 
    // now that the database is updated, we'd like to put these values back
 
	$title = xss_clean($_POST['title']); 
	$productid = mifi($_POST['pid']);
	$keywords = xss_clean($_POST['keywords']); 
	$catid = mifi($_POST['catid']); 
    $articledata = xss_clean($_POST['article']);
    

    
    
    } else { 
 
	$message .= ' and has not been updated, please try again.  This article '; 
 
	} 
} 
 
 
// Set the page title and include the HTML header. 
 
$title = 'Edit Article'; 
head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

$query2 = "SELECT Title, Approved, Keywords, Articledata from articles WHERE FileID='$enum' LIMIT 1";
 
	$result2 = mysql_query($query2); 
	while ($row = mysql_fetch_array ($result2, MYSQL_ASSOC)) { 
	$title = $row['Title']; 
	$keywords = $row['Keywords'];
    $pending = $row['Approved'];
	$articledata = stripslashes($row['Articledata']);
    
    
}    
include('./getcatfromid.php');
//returns $articlecategory from $catid   
    
     
?> 
 
<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="POST"> 
<fieldset><legend>This article <?php 


// Print the error message if there is one. 
 
  if (isset($message)) { 
 	echo $message; 
} 




switch ($pending) {
case ('Y'):
$approvalstatus = 'is approved';
break;

case ('S'):
$approvalstatus = 'is saved but not yet submitted';
break;

case ('N'):
$approvalstatus = 'is pending approval';
break;
}

echo $approvalstatus; ?>

</legend> 
<?php
echo <<<_FORM

<p>Title:<br /> 
<input type="text" name="title" size="60" maxlength="60" value="$title" /></p> 

<p>Article:<br />
_FORM;
if (isset($articledata)) {
$textareacontent=$articledata; }
$textareaname='article';
include('./textarea.php'); 
?>
</p> 
 
<p>Keywords:<br /> 
<input type="text" name="keywords" size="60" maxlength="120" value="<?php echo $keywords; ?>" /></p> 

<input type="hidden" name="num" value="<?php echo $enum; ?>" />

</fieldset> 

<p> 
<input type="submit" name="submit" value="Save" /><input type="reset" Value="Revert" /></p> 
</form> 
<?php foot_page();?> 