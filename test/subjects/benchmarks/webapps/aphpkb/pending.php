<?php // pending.php list articles from search or article tag.
include"./functions.php";
require"./config/auth.php";
include"./config/config.php";
include "./classes/mysql.class.php";
if($_REQUEST['type']){
// this uses the delete function, but may be expanded to include approvals also.

$type = $_REQUEST['type'];
$id = $_REQUEST['id'];

$pagetitle = delete($type, $id);
}


$acq=$_REQUEST['acq'];
$aid = mifi($_SESSION['user_id']);
$pagesize = DB_MAX_REC;
$recordstart = (isset($_GET['start'])) ? $_GET['start'] : 0;

switch ($acq){
case 'a':
$table = 'articles';
$query = "SELECT FileID, 
(SELECT COUNT('FileID') as count FROM articles WHERE Approved='N' AND ParentID='0'), 
Title, Articledata, Approved, AuthorID, 
(SELECT authors.UserName FROM authors  WHERE authors.AuthorID=articles.AuthorID) 
as AuthorName, 
DATE_FORMAT(SubmitDate, '%m/%e/%y') 
as date FROM articles WHERE 
Approved='N' AND ParentID='0' LIMIT $recordstart, $pagesize";
$updateoremail = 'Last Updated';
break;

case 'c':
$table = 'comments';
$query = "SELECT FileID, 
(SELECT COUNT('FileID') as count FROM articles WHERE Approved='N' AND ParentID!=0), 
Title, Articledata, Approved, 
DATE_FORMAT(SubmitDate, '%m/%e/%y') 
as date FROM articles WHERE 
Approved='N' AND ParentID!=0 LIMIT $recordstart, $pagesize";
$updateoremail = 'Last Updated';
break;

case 'q':
$table = 'questions';
$query = "SELECT FileID, 
(SELECT COUNT('FileID') as count FROM articles WHERE Approved='Q' AND ParentID='0'), 
Title, Articledata, Approved, AuthorID, 
(SELECT authors.UserName FROM authors  WHERE authors.AuthorID=articles.AuthorID) 
as AuthorName, 
DATE_FORMAT(SubmitDate, '%m/%e/%y') 
as date FROM articles WHERE 
Approved='Q' AND ParentID='0' LIMIT $recordstart, $pagesize";
$updateoremail = 'Last Updated';
break;





}

if(!$pagetitle) { $pagetitle = "Pending $table";}
$title = $pagetitle;


$mysqldb = new mysql();
$mysqldb->connect();
$mysqldb->select();
$mysqldb->query($query);

head_page($title);
menu_options($title, $v, $viewop, $pid, $keys, $adfl);
contentinit($title);

 $flcl = TRUE;
while($row = $mysqldb->fetchObject()){
$bg = ($bg=='#f5f5f5' ? '#cccccc' : '#f5f5f5');


if($flcl==TRUE){

echo '<table border="0" width="98%" cellspacing="3" cellpadding="3" align="center"><tr> 
<td align="left" width="30%"><small>Title</small></td> 
<td align="left" width="20%"><small>Author</small></td> 
<td align="right" width="20%"><small>' . $updateoremail . '</small></td> 
<td align="right" width="30%"><small>Approve-Edit-Delete</small></td>	 
</tr>';	}  
// Display each record.	

if($table=='questions'){
echo "<tr bgcolor=\"$bg\"><td align=\"left\"><a href=\"saa.php?aid=$aid&a=$row->FileID\">" . strip_tags(substr($row->Title,0,40) . '...') . "</a></td>";
} else {
echo "<tr bgcolor=\"$bg\"><td align=\"left\"><a href=\"v.php?a=$row->FileID\">$row->Title</a></td>";
}

echo '<td align=\"left\">';
if($row->AuthorName == '' && $row->UserName=='') { echo 'Guest'; } else { echo $row->AuthorName . $row->UserName; }

echo "
</td>
<td align=\"right\">
$row->date</td>";

if($table=='questions'){
echo "<td align=\"right\"><a href=\"saa.php?ans=1&aid=$aid&a=$row->FileID\">Edit</a>&nbsp;&nbsp;
<a href=\"pending.php?acq=$acq&type=q&id=$row->FileID\">Delete</a>
</td> 
</tr>";	 

} else {
echo "
<td align=\"right\"><a href=\"a_approve.php?fileid=$row->FileID\">Approve</a>&nbsp;&nbsp;
<a href=\"a_edita.php?num=$row->FileID\">Edit</a>&nbsp;&nbsp;<a href=\"pending.php?acq=$acq&type=a&id=$row->FileID\">Delete</a>
</td> 
</tr>";	 
}

$flcl = FALSE; 
$authorname = '';
$approved='';
// One record has been returned

} 

$totalrows = $row->count;

if($flcl) {	

    echo '<div align="center"><br /><br />There are currently no pending ' . $table . ' to view.<br /></div>'; 

echo '</td></tr></table>'; 
} else {
echo '</td></tr></table>'; 
}

//Create the 'previous' link
if ($recordstart > 0) {
$prev = $recordstart - $pagesize;
$url = $_SERVER['PHP_SELF'] . "?keyword_list=$keyword_list&start=$prev";
echo '<a href="' . $url . '">Prev </a>&nbsp;&nbsp;';
}

//Create the 'next' link
if ($totalrows > ($recordstart + $pagesize)) {
$next = $recordstart + $pagesize;
$url = $_SERVER['PHP_SELF'] . "?keyword_list=$keyword_list&start=$next";
echo '&nbsp;&nbsp;<a href="' . $url . '">Next</a>';
}
echo '</div>';
foot_page();
?>
