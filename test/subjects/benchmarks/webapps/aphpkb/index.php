<?php // index.php index page

include('./config/config.php');
if(KBINSTALL==0){
header ("Location:  http://" . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']) . "/install/index.php");
exit();
}


$title = KBNAME . ' KB';

$pagetitle = $title;
include"./classes/mysql.class.php";
include"functions.php";

head_page($title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

echo '
<table border="0" width="95%" cellspacing="5">
    <tr>
        <td width="33%" valign="top">
';
$mysqldb = new mysql();
 $mysqldb->connect();
 $mysqldb->select(); 
 
 $maxnum = DB_MAX_REC;
 
 //----------------------------------------------------------------
 // List Top ($num_records) Viewed Articles
 // ---------------------------------------------------------------

$first = TRUE; 
  
 $mysqldb->query("SELECT FileID, Title, Views, Articledata, DATE_FORMAT(Submitdate, '%e %M, %Y') AS date  FROM  articles  WHERE Approved='Y' AND ParentID = 0 ORDER by Views DESC LIMIT $maxnum");

$num_records = $mysqldb->numRows();
while ( $row = $mysqldb->fetchObject()){

if ($first) {
echo 'Top ';
echo $num_records;
echo '  Viewed Articles:<br />';     
echo '<table border="0" width="100%" cellspacing="3" cellpadding="3" align="center">'; 
} 

echo '<tr><td align="left"><a href="v.php?a=' . $row->FileID . '">  ' .  stripslashes ($row->Title) . '</a><br />';

echo strip_tags(substr(stripslashes($row->Articledata),0,65) . '...');

echo "</td></tr>\n";	

$first = FALSE; 

// One record has been returned

} 
// End of While loop
// If no records were displayed...
if ($first) {	

     echo '<div id="smallandcenter">Top Viewed : There are no articles available.</div>';

} else {	

echo '</table>'; 

// close the table
} 
            ?> 
        </td>
       <td width="33%" valign="top">

<?php
 //----------------------------------------------------------------
 // List Last ($num_records) created Articles
 // ---------------------------------------------------------------
$first = TRUE;
 $mysqldb->query("SELECT FileID, Title, Articledata, DATE_FORMAT(Submitdate, '%e %M, %Y') AS date FROM articles WHERE Approved='Y' AND ParentID =0 ORDER by FileID DESC LIMIT $maxnum");

$num_records = $mysqldb->numRows();
while ( $row = $mysqldb->fetchObject()){

if ($first) {
echo 'Last ';
echo $num_records;
echo '  Created Articles:<br />';     
echo '<table border="0" width="100%" cellspacing="3" cellpadding="3" align="center">'; 
} 

echo '<tr><td align="left"><a href="v.php?a=' . $row->FileID . '">  ' .  stripslashes ($row->Title) . '</a><br />';

echo strip_tags(substr(stripslashes($row->Articledata),0,65) . '...');

echo "</td></tr>\n";	

$first = FALSE; 

// One record has been returned

} 
// End of While loop
// If no records were displayed...
if ($first) {	

     echo '<div id="smallandcenter">Last Created : There are no articles available.</div>';

} else {	

echo '</table>'; 

// close the table
} 
?>       
		  
        </td>
                <td width="33%" valign="top">

<?php
 //----------------------------------------------------------------
 // List Top ($num_records) Rated Articles
 // ---------------------------------------------------------------
$first = TRUE; 

$first = TRUE; 
  
 $mysqldb->query("SELECT FileID, Title, Views, Articledata, DATE_FORMAT(Submitdate, '%e %M, %Y') AS date FROM articles WHERE Approved='Y' AND ParentID =0 ORDER by RatingTotal/RatedTotal DESC LIMIT $maxnum");

$num_records = $mysqldb->numRows();
while ( $row = $mysqldb->fetchObject()){

if ($first) {
echo 'Top ';
echo $num_records;
echo '  Rated Articles:<br />';     
echo '<table border="0" width="100%" cellspacing="3" cellpadding="3" align="center">'; 
} 

echo '<tr><td align="left"><a href="v.php?a=' . $row->FileID . '">  ' .  stripslashes ($row->Title) . '</a><br />';

echo strip_tags(substr(stripslashes($row->Articledata),0,65) . '...');

echo "</td></tr>\n";	

$first = FALSE; 

// One record has been returned

} 
// End of While loop
// If no records were displayed...
if ($first) {	

     echo '<div id="smallandcenter">Top Rated : There are no articles available.</div>';

} else {	

echo '</table>'; 

// close the table
} 
?>  
        </td>
    </tr>
</table>
</div>
<?php foot_page(); ?>