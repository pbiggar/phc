<?php  //forgot_password.php
// This page allows a user to reset their password, if forgotten.

include('./config/config.php'); 
include"./config/dbsettings.php";
include('functions.php');

// Set the page title and include the HTML header.
$title = 'Password Reset';
head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

if (isset($_POST['submit'])) { // Handle the form.

	if (empty($_POST['username']) || $_POST['username'] == 'Admin' ) { // Validate the username.
		$u = FALSE;
		echo '<p>Invalid or missing User Name!</p>';
	} else {
		$u = escdata($_POST['username']);
		
		// Check for the existence of that username.
		$query = "SELECT AuthorID, Email FROM authors WHERE UserName='$u'";		
		$result = @mysql_query ($query);
		$row = mysql_fetch_array ($result, MYSQL_NUM); 
		if ($row) {
			$uid = $row[0];
			$email = $row[1];
		} else {
			echo '<p>The submitted username does not match those on file!</p>';
			$u = FALSE;
		}
		
	}
	
	if ($u) { // If everything's OK.

		// Create a new, random password.
		$p = substr ( md5(uniqid(rand(),1)), 3, 10);

		// Make the query.
		$query = "UPDATE authors SET Passwd=PASSWORD('$p') WHERE AuthorID='$uid' AND UserName!='Admin' ";	
		
		$result = @mysql_query ($query); // Run the query.
		if (mysql_affected_rows() == 1) { // If it ran OK.
		
			// Send an email.
			$body = "Your password to log into KBNAME has been temporarily changed to '$p'. Please log-in using this password and your username. At that time you may change your password to something more familiar.";
			echo 'Your New Password is : ' . $p;
			
			foot_page();  
			exit();				
			
		} else { // If it did not run OK.
		
			// Send a message to the error log, if desired.
			$message = '<p>Your password could not be changed due to a system error. We apologize for any inconvenience.</p>'; 

		}		
		

	} else { // Failed the validation test.
		echo '<p>Please try again.</p>';		
	}

} // End of the main Submit conditional.

?>


<p>Enter your username below and your password will be reset.</p> 
<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post">

	<p>User Name:<br /> <input type="text" name="username" size="10" maxlength="20" value="<?php if (isset($_POST['username'])) echo $_POST['username']; ?>" /></p>

<input type="submit" name="submit" value="Reset My Password" />
</form>

<?php foot_page(); ?>