<?php

require_once('include.php');

if (isset($_POST['create'])) {
	$name = $_POST['tablename'];
	$columns = $_POST['columns'];

	$sql = "create table $name (\n";
	for ($i=1; $i<=$columns; $i++) {
		$sql .= "\t{$_POST['name'.$i]} {$_POST['type'.$i]}";
		if (is_numeric($_POST['size'.$i])) $sql .= "({$_POST['size'.$i]})";
		if (isset($_POST['notnull'.$i])) $sql .= ' not null';
		if (isset($_POST['unique'.$i])) $sql .= ' unique';
		if ( (isset($_POST['pk'])) && ($_POST['pk'] == "pk$i") ) $sql .= ' primary key';
		if ($i < $columns) $sql .= ',';
		$sql .= "\n";
	}
	$sql .= ");\n";
//	print $sql;
	$userdbh->query($sql);
	header("Location: index.php");
	exit;
}

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
<body>
<form name="create_table" method="post" action="table_create.php" target="_top">

<?php

$name = $_POST['tablename'];
$columns = $_POST['columns'];

print "<h3>Create a new table named '$name'</h3>\n";

print "<table border=1>\n";
print "<tr><th></th><th>Column name</th><th>Data type</th><th>Size</th><th>Not null</th><th>Unique</th><th>Primary key</th></tr>\n";

for ($i=1; $i<=$columns; $i++) {
	print "<tr>\n";
	print "<td>$i</td>\n";
	print "<td><input type=text name=name$i size=30></td>\n";
	print "<td><select name=type$i>\n";
	print_column_types();
	print "</select></td>\n";
	print "<td><input type=text size=4 maxlengh=5 name=size$i></td>\n";
	print "<td><input type=checkbox name=notnull$i></td>\n";
	print "<td><input type=checkbox name=unique$i></td>\n";
	print "<td><input type=radio name=pk value=pk$i></td>\n";
	print "</tr>\n";
}

print "</table><br>\n";
print "<input type=hidden name=columns value=$columns>\n";
print "<input type=hidden name=tablename value=$name>\n";
print "<input type=submit name=create value=\"Create table\">\n";
print "</form>\n";


print "</body>\n";
print "</html>\n";


?>