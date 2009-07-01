<?php
$tagfirst=TRUE;
 $mysqldb = new mysql();
 $mysqldb->connect();
 $mysqldb->select(); 

$mysqldb->query("SELECT DISTINCT id, tag FROM tags GROUP BY tag ORDER BY COUNT(*) DESC LIMIT 10");

while ( $row = $mysqldb->fetchObject()){

if($tagfirst==TRUE  && $row) {
echo "<p><b>Article Tags:</b></p>";
}
echo '<a href="abk.php?keyword_list=' . $row->tag . '">' . $row->tag . '</a> ';
$tagfirst=FALSE;
}
echo '<br /><br />'; 
?>
