<?php // view_authors.php
// This page allows the administrator to view all of the current authors.

// Require authentication.
$adfl = TRUE;
$title = 'View Authors';


include('./functions.php');
include"./config/config.php";
require_once ('./config/auth.php');
include"./config/dbsettings.php";
head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);
	// Number of records to show per page:
	$display = 10;
	
	// Determine how many pages there are. 
	if (isset($_GET['np'])) { // Already been determined.
		$num_pages = $_GET['np'];
	} else { // Need to determine.
		$query = "SELECT CONCAT(LastName, ', ', FirstName) AS name, AuthorID, DATE_FORMAT(RegistrationDate, '%M %d, %Y') AS dr FROM authors ORDER BY RegistrationDate ASC"; 
		$query_result = mysql_query ($query);
		$num_records = @mysql_num_rows ($query_result);
		
		if ($num_records > $display) { // More than 1 page.
			$num_pages = ceil ($num_records/$display);
		} else {
			$num_pages = 1;
		}
	}
	
	// Determine where in the database to start returning results.
	if (isset($_GET['s'])) { // Already been determined.
		$start = $_GET['s'];
	} else {
		$start = 0;
	}
			
	// Make the query.
	$query = "SELECT CONCAT(LastName, ', ', FirstName) AS name, AuthorID, DATE_FORMAT(RegistrationDate, '%M %d, %Y') AS dr FROM authors ORDER BY RegistrationDate ASC LIMIT $start, $display";		
	$result = @mysql_query ($query); // Run the query.
	$num = mysql_num_rows ($result); // How many users are there?
	
	if ($num > 0) { // If it ran OK, display the records.
	
		
	
		// Make the links to other pages, if necessary.
		if ($num_pages > 1) {
			
			echo '<p>';
			// Determine what page the script is on.	
			$current_page = ($start/$display) + 1;
			
			// If it's not the first page, make a Previous button.
			if ($current_page != 1) {
				echo '<a href="a_viewauthors.php?s=' . ($start - $display) . '&np=' . $num_pages . '">Previous</a> ';
			}
			
			// Make all the numbered pages.
			for ($i = 1; $i <= $num_pages; $i++) {
				if ($i != $current_page) {
					echo '<a href="a_viewauthors.php?s=' . (($display * ($i - 1))) . '&np=' . $num_pages . '">' . $i . '</a> ';
				} else {
					echo $i . ' ';
				}
			}
			
			// If it's not the last page, make a Next button.
			if ($current_page != $num_pages) {
				echo '<a href="a_viewauthors.php?s=' . ($start + $display) . '&np=' . $num_pages . '">Next</a>';
			}
			
			echo '</p><br />';
			
		} // End of links section.
		
		// Table header.
		echo '<table>
		<tr><td align="left"><font size="1">Name</font></td><td align="right"><font size="1">Date Registered</font></td></tr>';
		
		// Fetch and print all the records.
		$bg = '#eeeeee'; // Set the background color.
		while ($row = mysql_fetch_array($result, MYSQL_NUM)) {
   			$bg = ($bg=='#eeeeee' ? '#ffffff' : '#eeeeee'); // Switch the background color.
			echo '<tr bgcolor="', $bg, '"><td align="left"><a href="a_authord.php?aid=' . stripslashes($row[1]) . '">', stripslashes($row[0]), '</a></td><td align="right">', $row[2], '</td></tr>
';
		}
	
		echo '</table>'; // Close the table.
	
	} else { // If there are no registered users.
		echo '<div id="smallandcenter">There are currently no registered authors.</div>'; 
	}
foot_page();
?>