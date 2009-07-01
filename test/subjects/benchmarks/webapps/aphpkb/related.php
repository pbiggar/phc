<?php // related articles when viewing article

// lets do some related linking...
// We need to sort out the query first, because we are searching from
// any number of keywords, this is an involved process.
if(!isset($dbkeywords)) { $dbkeywords = $keywordse; } // from author editing result.
$fuzzy=1;

if(strlen($dbkeywords)>0){

$firstquery = "SELECT FileID, Title, Keywords FROM articles WHERE Approved='Y' AND ( Keywords LIKE ";
	$endquery = " ORDER by FileID DESC LIMIT 5";
	$arrkeywords = explode(' ', $dbkeywords);
	$firsttime = "TRUE";

foreach ($arrkeywords as $keyword) {
	if($keyword == " " || $keyword == "") continue;
		if ($firsttime == "FALSE") {
			$keywordquery = $keywordquery . " OR Keywords LIKE " ;
		}
		if (isset($fuzzy)) {
			$keywordquery = $keywordquery . "'%{$keyword}%'";
		} else {
			$keywordquery = $keywordquery . "' {$keyword} '";
		}
		$firsttime = "FALSE";
	}
$relatedquery = $firstquery . $keywordquery . " ) " . $endquery;
// That's the end of our query making.  

// Let's query and get our list...

$relatedfirst = TRUE;
 // Initialize the variable

$relatedresult = mysql_query($relatedquery);

// Display all the URLs
while ($row = mysql_fetch_array ($relatedresult, MYSQL_ASSOC)) {	
// If this is the first record, create the table header.	

if($row['FileID']!=$vnum) { // don't show anything if the the result is from the article we are viewing.

if ($relatedfirst==TRUE) {
echo '<br /><br /><p><b>Related Articles:</b></p>';
} 
// End of first IF
// Display each record.	

//we don't need to display a link to the article we are viewing
echo "<a href=\"aview.php?num={$row['FileID']}\">{$row['Title']}</a><br /><br />";

$relatedfirst = FALSE; 
// One record has been returned
 
// End of While loop
}
// If no records were displayed...

}

}
 
?>