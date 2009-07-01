<?php // search.php - search form.
if(!$searchwidth){ $searchwidth='100%'; }
?>
<form action="abk.php" method="post">
<table border="0" width="100%" cellspacing="5">
<tr>
<td>Search Keywords</td><td></td></tr>
<tr><td><input type="text" style="width:<?php echo $searchwidth; ?>" name="keyword_list"></td><td></td></tr>
<tr><td colspan="2">&nbsp;&nbsp;<input type="submit" value="Search"></td></tr>
</table>
</form>