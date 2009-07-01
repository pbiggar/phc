<?php // abk.php Articles by Keywords.

$adfl = FALSE; 
include('./config/config.php');
include"./config/dbsettings.php";
include('functions.php');

$title = 'Search Results';
$keyword_list = $_REQUEST['keyword_list'];
if(strlen($keyword_list) == 0) { $keyword_list = 'nothing'; }
$pid = mifi($_REQUEST['productid']);

$title = "Search Results for \"$keyword_list\"";
head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);
// Number of Records to show per page:
$display = DB_MAX_REC;

// Determine where in the db to start returning results
if (isset($_GET['s'])) { // Already determined
$start = $_GET['s'];
} else {
$start = 0;
}
// We need to sort out the query first, because we are searching from
// any number of keywords, this is an involved process.
$firstquery = "SELECT FileID, Title, Articledata, AuthorID, DATE_FORMAT(SubmitDate, '%m/%e/%y') as date FROM articles WHERE $product Approved='Y' AND Keywords LIKE ";
	$endquery = " ORDER by FileID";
	$arrkeywords = explode(' ', $keyword_list);
	$firsttime = "TRUE";

foreach ($arrkeywords as $keyword) {

	if($keyword == " " || $keyword == "") continue;

		if ($firsttime == "FALSE") {
			$keywordquery = $keywordquery . " OR Keywords LIKE " ;
		}
			$keywordquery = $keywordquery . "'%{$keyword}%'";
		$firsttime = "FALSE";
	}

$query = $firstquery . $keywordquery . $endquery;
$viewquery = $query . " LIMIT $start, $display";
// That's the end of our query making.  

// Determine how many pages there are:
if (isset($_GET['np'])) { // all ready been determined
$num_pages = $_GET['np'];
} else { // need to determine
$query_result = mysql_query($query);
$num_records = @mysql_num_rows($query_result);

if ($num_records > $display) { // more than one page
$num_pages = ceil($num_records/$display);
} else {
$num_pages = 1;
}
}

$first = TRUE;

$result = mysql_query($viewquery);
$num = $num_records;

if($result)	{
$bg = '#f5f5f5'; // Set the background color.

while ($row = mysql_fetch_array ($result, MYSQL_ASSOC)) {	
// switch background colours:
$bg = ($bg=='#f5f5f5' ? '#cccccc' : '#f5f5f5');
// If this is the first record, create the table header.	

$fileid = $row['FileID'];
$title = $row['Title'];
$articledata = $row['Articledata'];
$authorid = $row['AuthorID'];
$date = $row['date'];


if ($first) {

echo <<<EOF
<table border="0" cellspacing="0" cellpadding="5" align="center" width="95%"><tr>
<td align="left" width = "30%"><small>Title</small></td>
<td align="left" width = "40%"><small>Summary</small></td>
<td align = "left" width = "10%"><small>Author</small></td>
<td align = "right" width = "20%"><small>Last Updated</small></td></tr>
EOF;

} 

$authorquery = "SELECT FirstName, LastName FROM authors WHERE AuthorID='$authorid'";
$authorresult = mysql_query($authorquery); 
	while ($row = mysql_fetch_array ($authorresult, MYSQL_ASSOC)) { 
	$authorname = $row['FirstName'] . ' ' . $row['LastName']; 
}

if($authorid == '0') {$authorname = 'Guest'; }
// Display each record.	

echo "<tr bgcolor=\"$bg\"><td align=\"left\"><a href=\"v.php?a=$fileid\">$title</a></td>";

echo '<td align="left">';
echo strip_tags(substr(stripslashes($articledata),0,52) . '...');
echo '</td>';
echo "<td align=\"left\">
$authorname</td>

<td align=\"right\">
$date</td></tr>";	

$first = FALSE; 
$authorname = '';
$catid = '';
// One record has been returned

} 

// End of While loop
// If no records were displayed...
if($first) {	

echo '
<p>No articles match the query.</p>

<p>Please search again and use more specific keywords.<br />
Multiple keywords can be used to refine the search.</p>';

$searchwidth='30%';
include('search.php');

echo '</td></tr></table>'; 

} else {	

echo '</td></tr></table>'; 

// Close the table.
		// Make the links to other pages, if necessary.
		if ($num_pages > 1) {
			
			echo '<tr><td colspan="3">';			
// echo '<p class="content">';
			
			// Determine what page the script is on.	
			$current_page = ($start/$display) + 1;
			
			// If it's not the first page, make a Previous button.
			if ($current_page != 1) {
				echo '<a href="abk.php?keyword_list=' . $keyword_list . '&s=' . ($start - $display) . '&np=' . $num_pages . '">Previous</a> ';
			}
			
			// Make all the numbered pages.
			for ($i = 1; $i <= $num_pages; $i++) {
				if ($i != $current_page) {
					echo '<a href="abk.php?keyword_list=' . $keyword_list . '&s=' . (($display * ($i - 1))) . '&np=' . $num_pages . '">' . $i . '</a> ';
				} else {
					echo $i . ' ';
				}
			}
			// If it's not the last page, make a Next button.
			if ($current_page != $num_pages) {
				echo '<a href="abk.php?keyword_list=' . $keyword_list . '&s=' . ($start + $display) . '&np=' . $num_pages . '">Next</a>';
			}
			echo '</td></tr></table><br />';
		} // End of links section.
}
}
// Include the HTML footer file.
foot_page(); 
?>
