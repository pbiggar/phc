<?php // register.php
$adfl = FALSE; 
include('./config/config.php');
include"./config/dbsettings.php";
include('functions.php');
$title = 'Register';

head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

if (isset($_POST['submit'])) { // Handle the form.
	
	// Check for a first name.
	if (eregi ("^[[:alpha:].' -]{2,15}$", stripslashes(trim($_POST['first_name'])))) {
		$fn = escdata($_POST['first_name']);
	} else {
		$fn = FALSE;
		echo '<p>Please enter your first name!</p>';
	}
	
	// Check for a last name.
	if (eregi ("^[[:alpha:].' -]{2,30}$", stripslashes(trim($_POST['last_name'])))) {
		$ln = escdata($_POST['last_name']);
	} else {
		$ln = FALSE;
		echo '<p>Please enter your last name!</p>';
	}
	
	// Check for an email address.
	if (eregi ("^[[:alnum:]][a-z0-9_.-]*@[a-z0-9.-]+\.[a-z]{2,4}$", stripslashes(trim($_POST['email'])))) {
		$e = escdata($_POST['email']);
	} else {
		$e = FALSE;
		echo '<p>Please enter a valid email address!</p>';
	}

	// Check for a username.
	if (eregi ("^[[:alnum:]_]{4,20}$", stripslashes(trim($_POST['username'])))) {
		$u = escdata($_POST['username']);
	} else {
		$u = FALSE;
		echo '<p>Please enter a valid username!</p>';
	}
	
	// Check for a password and match against the confirmed password.
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
	
	if ($fn && $ln && $e && $u && $p) { // If everything's OK.

		// Make sure the username is available.
		$query = "SELECT AuthorID FROM authors WHERE UserName='$u'";		
		$result = @mysql_query ($query);
		
		if (mysql_num_rows($result) == 0) { // Available.
		
			// Add the user.
			$query = "INSERT INTO authors (UserName, FirstName, LastName, Email, Passwd, RegistrationDate) VALUES ('$u', '$fn', '$ln', '$e', PASSWORD('$p'), NOW() )";		
			$result = @mysql_query ($query); // Run the query.

			if ($result) { // If it ran OK.
			
				// Send an email, if desired.
				echo 'Thank you for registering!';
				foot_page();
				exit();				
				
			} else { // If it did not run OK.
				// Send a message to the error log, if desired.
				echo '<p>You could not be registered due to a system error. We apologize for any inconvenience.</p>'; 
			}		
			
		} else { // The username is not available.
			echo '<p>That username is already taken.</p>'; 
		}
		
		

	} else { // If one of the data tests failed.
		echo '<p>Please try again.</p>';		
	}

} ?>
	
	<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post">
	 
	
	<p>First Name:<br /> <input type="text" name="first_name" size="15" maxlength="15" value="<?php if (isset($_POST['first_name'])) echo $_POST['first_name']; ?>" /></p>
	
	<p>Last Name:<br /> <input type="text" name="last_name" size="30" maxlength="30" value="<?php if (isset($_POST['last_name'])) echo $_POST['last_name']; ?>" /></p>
	
	<p>Email Address:<br /> <input type="text" name="email" size="40" maxlength="40" value="<?php if (isset($_POST['email'])) echo $_POST['email']; ?>" /> </p>
	
	<p>User Name:<br /> <input type="text" name="username" size="10" maxlength="20" value="<?php if (isset($_POST['username'])) echo $_POST['username']; ?>" /> <small>Use only letters, numbers, and the underscore. Must be between 4 and 20 characters long.</small></p>
	
	<p>Password:<br /><input type="password" name="password1" size="20" maxlength="20" /> <small>Use only letters and numbers. Must be between 4 and 20 characters long.</small></p>
	
	<p>Confirm Password:<br /><input type="password" name="password2" size="20" maxlength="20" /></p>
	 
	
	 <input type="submit" name="submit" value="Register" /> 
	
	</form><!-- End of Form -->

<?php // Include the HTML footer.
foot_page();
?>