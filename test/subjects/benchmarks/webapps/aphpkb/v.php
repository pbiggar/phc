<?php // v.php
 // variables

  include('./config/config.php');
  include_once('functions.php');
  
   $a=mifi($_REQUEST['a']);
  $aid = $_SESSION['user_id'];
  include "./classes/mysql.class.php";
 $mysqldb = new mysql();
 $mysqldb->connect();
 $mysqldb->select(); 
 
 // admin override for viewing un-approved articles
 if($_SESSION['adfl']){
 $adminview = '';
 } else {
 $adminview = "AND Approved='Y'";
}
 // query
 
 $mysqldb->query("
 SELECT articles.FileID, (SELECT ArticleData FROM articles WHERE Approved='A' AND ParentID=$a LIMIT 1) as question, articles.ParentID, articles.AuthorID, (SELECT authors.UserName FROM authors  WHERE authors.AuthorID=articles.AuthorID) as AuthorName, articles.Title, articles.Keywords, articles.ArticleData, articles.Approved, articles.Views, articles.RatingTotal, articles.RatedTotal, articles.SubmitDate 
 FROM 
 articles 
 WHERE FileID='$a'
 $adminview
 ");

 // retrieve result as an object
 
 $row = $mysqldb->fetchObject();

$fileid = $row->FileID;
$title = $row->Title;
$parentid = $row->ParentID;
$approved = $row->Approved;
$keywords = $row->Keywords;
$views = $row->Views + 1;
$ratingtotal = $row->RatingTotal;
$ratedtotal = $row->RatedTotal;
$datesubmitted = $row->SubmitDate;
$authorname = $row->AuthorName;
$authorid = $row->AuthorID;
$question = '<i>' . $row->question . '</i><br /><br />'; 
// variables and conditions
$articletext = ereg_replace("\n", "<br />", $row->ArticleData); 
//approval variable
if(!$_SESSION['adfl']){
switch ($row->Approved) {
case ('Y'):
 $mysqldb->select();
 $mysqldb->query("
 UPDATE articles 
 SET Views = $views 
 WHERE FileID='$a' 
 ");

break;

case ('S'):
$articletext = 'Not Submitted For Approval';
break;

case ('N'):
$articletext = 'Not Approved';
break;
}
 } // end of admin check for approval and view updates
// Output the data


if(!$articletext){
$title = 'article unavailable';
$soft404 = '<p>Sorry, this article may have been updated, deleted or in the process of being approved.<br /><br />


Please feel free to search using keywords to match available articles.<br /><br />

Multiple keywords can be used to refine the search.<br />';
$nodetails = TRUE;
head_page($title);
menu_options($title, $v, $viewop, $pid, $keys, $adfl);
contentinit($title);

echo $soft404;
$searchwidth = '30%';
include"search.php";
echo '</div>';

foot_page(); exit();
}

$pagetitle = $title;

head_page($title);
menu_options($title, $v, $viewop, $pid, $keys, $adfl);
contentinit($title);

echo $question . $articletext . '</div>';

// Rating

//if you are  logged in you can rate a guest article
if(isset($_SESSION['user_id'])){$canrate=TRUE;}
//if you are a guest you can rate an author article
if(!isset($_SESSION['user_id'])){$canrate=TRUE;}
//if you are  logged in you can't rate your own article
if($authorid == isset($_SESSION['user_id'])){$canrate=FALSE;}
//if you are a guest you cannot rate a guest article
if($authorid == 0 && !isset($_SESSION['user_id'])){$canrate=FALSE;}
//if you are admin you cannot rate any articles
if($_SESSION['adfl']){$canrate=FALSE;}



if($canrate==TRUE){
echo "<div class='content'><p><b>Article Rating:</b></p>";    
include('./inc/rating.php');
echo '</div>';
}


// check for attachments.
$attachfirst = TRUE;
 $mysqldb->query("SELECT UploadID, AuthorID, FileName, FileDescription FROM uploads WHERE AuthorID='$authorid' AND FileID='$a'");

while($row = $mysqldb->fetchObject()){
     
// If this is the first record
if ($attachfirst==TRUE) {

echo '<div class="content"><b>Attachments:</b><br />';

	} // End of $first IF.

	// Display each record.
	
echo '<a href="' . KBURL . "attach/$row->UploadID-$row->AuthorID-$a-$row->FileName\">$row->FileDescription</a><br />";

	$attachfirst = FALSE; // One record has been returned.
				
				echo '</div>';
				
				} //end of attachment while
		

// check for comments
$mysqldb->select();
 // query
 $mysqldb->query("
 SELECT FileID, Title, ParentID, Approved, Keywords, Views, RatingTotal, RatedTotal, SubmitDate, ArticleData 
 FROM 
 articles 
 WHERE Approved='Y' AND ParentID='$a'
 ");

 // retrieve result as an object
$comfirst=TRUE; 

while($row = $mysqldb->fetchObject()){
$commenttitle = $row->Title;

$comment = $row->ArticleData;

if($comfirst==TRUE) { echo '
<div class ="content"><br /><p><b>Comments:</b></p>'; }
echo "$commenttitle:<br /><br >&nbsp;&nbsp;&nbsp;&nbsp;$comment<br /><br />
";

$comfirst=FALSE;
} 
echo '</div>'; //</div></div>';

if($parentid==0){ // no comments on comments

echo <<<_EOF
<div class ="content">
<br /><br /><p>Submit a <a href="submit_comment.php?parentid=$a">comment</a> with your feedback/suggestions.</p>
</div>
_EOF;

}


if(strlen($authorname)==0) { $authorname = 'Guest Author'; }


if($_SESSION['adfl']){

switch ($approved){
case 'N':
$approvelink = "<a href=\"a_approve.php?fileid=$fileid\">Approve	:	$approved</a><br />";
break;

case 'Q':
$approvelink = "<a href=\"saa.php?aid=$aid&a=$fileid\">Answer	:	$approved</a><br />";
break;

}
}
if(!$nodetails){
echo <<<_EOF
<div class ="content">
<p><b>Article Details:</b></p>
FileID 			:  	$fileid<br />
$approvelink
Keywords	:	$keywords<br />
Authored by :    $authorname<br />
Views			:	$views<br />
RatingTotal	:	$ratingtotal<br />
RatedTotal	:	$ratedtotal<br />
Submit Date	:	$datesubmitted<br />
</div>
_EOF;


if(PLUGINPDF){
echo '<div class ="content">';
include('./plugins/pdfClasses/pdfform.php');
echo '</div>';
}


$firstquery = "SELECT FileID, Title, Keywords FROM articles WHERE ParentID='0' $adminview AND ( Keywords LIKE ";
	$endquery = " ORDER by FileID DESC LIMIT 5";
	$arrkeywords = explode(' ', $keywords);
	$firsttime = "TRUE";
 
foreach ($arrkeywords as $keyword) {
	if($keyword == " " || $keyword == "") continue;
		if ($firsttime == "FALSE") {
			$keywordquery = $keywordquery . " OR Keywords LIKE " ;
		}
	     $keywordquery = $keywordquery . "'%{$keyword}%'";
     	$firsttime = "FALSE";
	}
$relatedquery = $firstquery . $keywordquery . " ) " . $endquery;
// That's the end of our query making.  
 $mysqldb->select();
 $mysqldb->query($relatedquery);

 // retrieve result as an object
 
 $row = $mysqldb->fetchObject();
$relatedfirst = TRUE;
if($keywords){
while($row = $mysqldb->fetchObject()){
if($row->FileID!=$a) {

if ($relatedfirst==TRUE) {
echo '<div class ="content"><br /><p><b>Related Articles:</b></p>';
} 
echo "<a href=\"v.php?a=$row->FileID\">$row->Title</a><br /><br />";

$relatedfirst = FALSE; 

} // end of not showing the article we are viewing in the related article list
} // end of while related article result
} // end of keywords
//echo '</div>';
} // end of not showing details for unavailable articles
foot_page();
?>
