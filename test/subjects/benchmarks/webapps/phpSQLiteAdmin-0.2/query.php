<?php

require_once('include.php');

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN">
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
	<title>phpSQLiteAdmin</title>
	<meta http-equiv="expires" content="0">
	<script language="Javascript" src="javascript.txt" type="text/javascript"></script>
	<link href="phpsla.css" rel="stylesheet" type="text/css">
</head>
<body class="right">
<?php

if ($_POST['object'] != '') $current_table = $_POST['object'];
if ($_GET['object'] != '') $current_table = $_GET['object'];

//$table = new table($current_table);
print_top_links($current_table);

if ($_POST['sql'] != '') {
        $show = trim($_POST['sql']);
} else {
        $show = "select * from $current_table";
}

?>

<form name=query method=post action="<?=$_SERVER['PHP_SELF']?>">
<input type=hidden name=object value="<?=$current_table?>">
<textarea name=sql rows=8 cols=80>
<?=$show?>
</textarea><br>
<input type=submit name=submit value="Execute SQL">
</form>


<?php

if ($_POST['sql'] != '') {
	print "<br><table>\n";
	//sqlite_escape_string($_POST['sql']);
	$userdbh->query(trim($_POST['sql']));
	while($row = $userdbh->fetchArray()) {
		$nr_fields = count($row);
		print "<tr>\n";
		for ($i=0; $i<$nr_fields; $i++) {
			if (strlen($row[$i]) > 50) {
				print '<td>'.substr($row[$i],0,50)."...</td>\n";
			} else {
				print "<td>$row[$i]</td>\n";
			}
		}
		print "</tr>\n";
	}
	print "</table>\n";
}


print "</body>\n";
print "</html>\n";


?>