<?php
$tagfirst=TRUE;
$query = "SELECT DISTINCT id, tag FROM tags GROUP BY tag ORDER BY COUNT(*) DESC";

$result = mysql_query($query);

while ($row = mysql_fetch_array ($result, MYSQL_ASSOC)) {
        $id = $row['id'];
        $tag = $row['tag'];

if($tagfirst==TRUE  && $result) {
echo "<br /><p><b>Article Tags:</b></p>";
}
echo '<a href="abk.php?keyword_list=' . $tag . '">' . $tag . '</a> ';
$tagfirst=FALSE;
}
echo '<br /><br />';
?>