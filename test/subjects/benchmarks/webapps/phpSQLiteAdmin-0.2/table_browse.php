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
<body class=right>
<?php

print_top_links($_GET['object']);

//$sth = sqlite_query($link,"select * from '{$table->name}' limit 30");
//$sth = sqlite_query($link,"select * from '{$table->name}'");

print "<h3>Table '".$_GET['object']."'</h3>\n";
print "<table>\n";

$userdbh->query('select * from '.$_GET['object']);
while($row = $userdbh->fetchArray()) {
	$nr_fields = count($row);
	//$rows = $userdbh->returnRows('num');
	//$table->print_header();
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


print "</body>\n";
print "</html>\n";


?>