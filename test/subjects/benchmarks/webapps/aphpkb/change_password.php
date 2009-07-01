<?php //change_password.php
require_once ('config/config.php');
include"./config/dbsettings.php";

$title = 'Change Your Password';

include('functions.php');
head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);
// If no first_name variable exists, redirect the user.
if (!isset($_SESSION['first_name'])) {

	header ("Location:  http://" . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']) . "/index.php");
	ob_end_clean();
	exit();
	
} else {

	if (isset($_POST['submit'])) { 			
		// Check for a new password and match against the confirmed password.
		if (eregi ("^[[:alnum:]]{4,20}$", stripslashes(trim($_POST['password1'])))) {
			
						
			if ($_POST['password1'] == $_POST['password2']) {
				$p = escdata($_POST['password1']);
			} else {
				$p = FALSE;
				echo '<p>Your password did not match the confirmed password!</p>';
			}
		} else {
			$p = FALSE;
			echo '<p>Please enter a valid password!</p>';
		}
		
		if ($p) { // If everything's OK.
	
			// Make the query.
			
			$query = "UPDATE authors SET Passwd=PASSWORD('$p') WHERE AuthorID={$_SESSION['user_id']}";		
			
			$result = @mysql_query ($query);
// Run the query.
			if (mysql_affected_rows() == 1) { // If it ran OK.
			
				// Send an email, if desired.
				echo '<p>Your password has been changed.</p>';
				foot_page(); // Include the HTML footer.
				exit();				
				
			} else { // If it did not run OK.
			
				// Send a message to the error log, if desired.
				$message = '<p>Your password could not be changed due to a system error. We apologize for any inconvenience.</p>'; 

			}		
		} else { 
// Failed the validation test.
			echo '<p>Please try again.</p>';		
		}
	
	} // End of the main Submit conditional.
	
	?>
	
	<p>Change Your Password</p>
	<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post">
	<fieldset>
	<p>New Password:<br /><input type="password" name="password1" size="20" maxlength="20" /> <small>Use only letters and numbers. Must be between 4 and 20 characters long.</small></p>
	<p>Confirm New Password:<br /><input type="password" name="password2" size="20" maxlength="20" /></p>
	
	<div align="center"><input type="submit" name="submit" value="Reset My Password" /></div>
	</fieldset>
	</form>

<?php
} // End of the !isset($_SESSION['first_name']) ELSE.
foot_page(); 
?>