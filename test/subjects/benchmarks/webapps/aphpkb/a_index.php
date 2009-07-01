<?php // This is the main page for the admin site. 
 
//Set Authentication for the Admin Area 
 
$adfl = TRUE; 
$page_title = 'KB Admin - Statistics';
$title = 'Statistics';


include('./config/config.php');
include('./functions.php');
require_once ('./config/auth.php');
include "./classes/mysql.class.php";
$mysqldb = new mysql();
$mysqldb->connect();
$mysqldb->select(); 
 
 // query
 
$mysqldb->query("SELECT COUNT(*) as articley FROM articles WHERE Approved='Y' AND  ParentID=0");
$row = $mysqldb->fetchObject();
$approvedarticles = $row->articley;
$mysqldb->query("SELECT COUNT(*) as articlen FROM articles WHERE Approved = 'N' AND ParentID=0");
 $row = $mysqldb->fetchObject();
 $pendingarticles = $row->articlen;
$mysqldb->query("SELECT COUNT(*)  as commenty FROM articles WHERE Approved='Y' AND  ParentID>0");
 $row = $mysqldb->fetchObject();
 $approvedcomments = $row->commenty;
$mysqldb->query("SELECT COUNT(*) as commentn FROM articles WHERE Approved = 'N' AND ParentID>0");
 $row = $mysqldb->fetchObject();
 $pendingcomments = $row->commentn;
$mysqldb->query("SELECT count(*) as qy from articles WHERE Approved = 'Q'");
 $row = $mysqldb->fetchObject();
 $respondedquestions = $row->qy;
$mysqldb->query("SELECT count(*) as qn from articles WHERE Approved = 'A'");
 $row = $mysqldb->fetchObject();
 $pendingquestions = $row->qn;

$totalarticles = $pendingarticles + $approvedarticles;
$totalcomments = $approvedcomments + $pendingcomments;
$totalquestions = $respondedquestions + $pendingquestions;

// if all is good, we've got our count variables and we can now display...

head_page($page_title);
menu_options($title, $vnum, $viewop, $pid, $keys, $adfl);
contentinit($title);

echo <<<_EOF
<br />

<table>
<tr>
<td><a href="pending.php?acq=a">Pending Articles</a></td><td><a href="a_pendinga.php">$pendingarticles</a></td>
</tr>
<tr>
<td>Approved Articles</td><td>$approvedarticles</td>
</tr>
<tr>
<td>Total Articles</td><td>$totalarticles</td>
</tr>
<tr>
<td colspan="2">&nbsp;&nbsp; <td>
</tr>
<tr>
<td><a href="pending.php?acq=c">Pending Comments</a></td><td><a href="a_pendingc.php">$pendingcomments</a></td>
</tr>
<tr>
<td>Approved Comments</td><td>$approvedcomments</td>
</tr>
<tr>
<td>Total Comments</td><td>$totalcomments</td>
</tr>
<tr>
<td colspan="2">&nbsp;&nbsp; <td>
</tr>
<tr>
<td><a href="pending.php?acq=q">Pending Questions</a></td><td><a href="a_pendingq.php">$pendingquestions</a></td>
</tr>
<tr>
<td>Responded Questions</td><td>$respondedquestions</td>
</tr>
<tr>
<td>Total Questions</td><td>$totalquestions</td>
</tr>

</table>	 		 
_EOF;
foot_page();
?>