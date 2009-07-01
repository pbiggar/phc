<?php // confirm.php

include('./config/config.php');
include('functions.php');
$title = 'Confirmation';

head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

if (isset($_REQUEST['emd'])) { // Handle the form.
	
$emd = escdata(xss_clean($_REQUEST['emd']));


			$emailmd5 = md5($e);
			
			$query = "UPDATE authors SET Approved = 'Y' WHERE EmailMD5='$emd'";		
			$result = @mysql_query ($query); // Run the query.

			if ($result) { // If it ran OK.
			
				// Registration Message and Thanks.
				echo '
				
				<p>Thank you for your confirmation!</p>
				
				<p>Please feel free to <a href="./login.php">login</a>.</p>';


  				foot_page();
				exit();				
				
			} else { // If it did not run OK.
				// Send a message to the error log, if desired.
				echo '<p>You could not be registered due to a system error.  We apologize for any inconvenience.</p><p>';
			}		
			
		} 
foot_page();
?>