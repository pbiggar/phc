<?php // edit_comment.php 
include('./functions.php');
require_once ('./config/auth.php');
include('./config/config.php');
 
$num = mifi($_REQUEST['num']);
 
if(isset($_POST['submit'])) {  
        // Handle the Form 
 
	$message = NULL;  
        // Create an empty new variable. 
 
	// Check for Title. 
	if (strlen($_POST['title']) > 0) { $title = TRUE; 
	} else { 
	$title = FALSE; 
	$message .= '<p>You need to include a title for the comment</p>'; 
	} 
 
	// Check for Article. 
	if (strlen($_POST['article']) > 0) { $article = TRUE; 
	} else { 
	$article = FALSE; 
	$message .= '<p>You need to include the comment.</p>'; 
	} 
 
 
	if ($title && $article) { // If everythings okay. 
 
	$titlesql = $_POST['title']; 
	$authorsql = $_POST['author']; 
    $articledatasql = $_POST['article'];
	 
	$query = "UPDATE articles SET Title = '{$titlesql}', Author = '{$authorsql}', Articledata = '{$articledatasql}' WHERE FileID='$num'"; 
 
	$result = mysql_query($query); 
	
    $message .= "The comment data has been updated."; 
 
    // now that the database is updated, we'd like to put these values back
 
	$title = $_POST['title']; 
	$author = $_POST['author']; 
	$keywords = $_POST['keywords']; 
	$category = $_POST['category']; 
    $articledata = $_POST['article'];
    
    } else { 
 
	$message .= '<p>Please try again</p>'; 
 
	} 
} 
// Set the page title and include the HTML header. 
 

$query2 = "SELECT Title, AuthorID, Approved, Articledata FROM articles WHERE FileID='$num' AND ParentID>0";
 
	$result2 = mysql_query($query2); 
	while ($row = mysql_fetch_array ($result2, MYSQL_ASSOC)) { 
	$title = "{$row['Title']}"; 
	$authorid = "{$row['AuthorID']}"; 
	$pending = "{$row['Approved']}";
	$articledata = "{$row['Articledata']}";
    } 
    
head_page($title);    
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);
 // Print the error message if there is one. 
 
  if (isset($message)) { 
 
	echo '<font color="red">', $message, '</font>';
      
} 
     
    
    
?> 
 
<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="POST"> 
<fieldset><legend>This comment is <?php 
if ($pending == 'Y') { 
echo '<font color="green">Approved</font>';
} else { 
echo '<font color="red">Pending Approval</font>';
}
?></legend> 
<br /><br /> 
 
<p>Title:<br /> 
<input type="text" name="title" size="60" maxlength="60" value="
<?php echo $title;
?>" /></p> 
 
<p>Article:<br /> 	
<textarea name="article" cols="60" rows="15"><?php 
echo $articledata;
?></textarea> 

</p> 
 
<input type="hidden" name="num" value="<?php echo $num; ?>" />

</fieldset> 
<p> 
<input type="submit" name="submit" value="Submit" /><input type="reset" Value="Revert" /></p> 
</form> 
<?php  
foot_page(); 
?> 