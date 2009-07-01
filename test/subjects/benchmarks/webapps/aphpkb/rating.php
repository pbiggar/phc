<?php   /* article rating */
include"./config/dbsettings.php";
if(isset($_REQUEST['score'])) {$score = mifi($_REQUEST['score']);}
$newratedtotal = '';
// get existing rating

$query = "SELECT RatingTotal, RatedTotal from articles WHERE FileID=$vnum";

$result = mysql_query($query);
        while ($row = mysql_fetch_array ($result, MYSQL_ASSOC)) {
        $sum = "{$row['RatingTotal']}";
        $count = "{$row['RatedTotal']}";
}
if ($count > 0) {
   $articleRating = $sum/$count;
} else {
   $articleRating = 0;
}

if(!isset($score)){ /* if we don't have a score, we'll just display the form */

// display rating form

echo "<p><form action=\"aview.php?num=$vnum\" method=\"post\">";
$begbuttonstr = '<input type="radio" name="score" value="';
$endbuttonstr = '" />';
$starstr = '<img src="./imgs/star.gif" height="10" width="10" />';
$count = 5;
$star = 5;
while($count >0 ) {
echo $begbuttonstr . $count . $endbuttonstr;
while($star > 0) {
echo $starstr;
$star = $star - 1;
}
echo '<br />';
$count = $count - 1;
$star = $count;
}
echo '&nbsp;&nbsp;<input type=submit name="submit" value="Submit"></form></p>';

} else {
/* else if we have the new score we can add the score to the running total RatingTotal and
add 1 to the count which is RatedTotal */

// add score to RatingTotal and add 1 to RatedTotal

$newratingtotal = $score + $sum;
$newratedtotal = $count + 1;
if(!$vnum) { $vnum = $num; }
// pop the values back into the database

   $query = "UPDATE articles SET RatingTotal = '$newratingtotal', RatedTotal = '$newratedtotal' WHERE FileID='$vnum'";
   $result = mysql_query($query);
   if (mysql_errno()) {
      echo "MySQL error ".mysql_errno().": ".mysql_error()."\n<br>When
executing:<br>\n$query\n<br>";
   }
}
// display $score and $newrating
if ($newratedtotal > 0) {
   $newrating = $newratingtotal / $newratedtotal;
} else {
   $newrating = 0;
}

if(isset($score)) { echo 'You have rated this article at: ' . $score . '<br />  The overall rating for this article is: ' . substr($newrating,0,4) . '<br />'; }
else { echo 'Article Rating: ' . substr($articleRating,0,4) . '<br />';}

/* end of article rating */ 
?>