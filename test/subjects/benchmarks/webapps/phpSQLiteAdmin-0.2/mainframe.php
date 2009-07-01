<?php

require_once('include.php');

echo<<<EOT
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN">
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
	<title>phpSQLiteAdmin</title>
	<meta http-equiv="expires" content="0">
	<script language="javascript" src="javascript.txt" type="text/javascript"></script>
	<link href="phpsla.css" rel="stylesheet" type="text/css">
	<base target="mainframe">
</head>
<body class=right>
<div id="currentdb">Database: {$_SESSION['phpSQLiteAdmin_currentdb']}</div>
EOT;

if (check_db()) print "<p class=\"sqliteversion\">SQLite version: ".$sqliteversion."</p>\n";

print "<h3>phpSQLiteAdmin 0.2</h3>\n";

if (!check_db()) {
        die("<p>The selected database is either read-only or does not exist</p>\n");
}

$dbinfo = $userdbh->dbInfo();

print "<table id=\"dbinfotable\">\n";
print "<tr><th colspan=2>Database file information</th></tr>\n";
print "<tr><td>Size:</td><td>".($dbinfo['size']/1024)."KB</td></tr>\n";
print "<tr><td>Last modification:</td><td>".$dbinfo['last_mod']."</td></tr>\n";

if(function_exists("posix_getpwuid")) {
	$user = posix_getpwuid($dbinfo['owner']);
	$group = posix_getgrgid($user['gid']);
	print "<tr><td>Owner:</td><td>".$user['name']."</td></tr>\n";
	print "<tr><td>Group:</td><td>".$group['name']."</td></tr>\n";
}

print "</table><br>\n";


print "<h3>Tables:</h3>\n";
/*
$userdbh->listTables();
$rows = $userdbh->returnRows('num');
print "<table id=\"tabletable\">\n";
print "<tr><th>Name</th><th>Rows</th><th>Action</th></tr>\n";
if (count($rows) > 0) {
	foreach($rows as $row) {
		print "<tr><td>".$row[0]."</td>\n";
		print "<td>".$userdbh->numRows($row[0])."</td><td>\n";
		print_table_action_links($row[0]);
		print "</td></tr>\n";
	}
}
print "</table><br>\n";
*/

print "<table id=\"tabletable\">\n";
print "<tr><th>Name</th><th>Rows</th><th>Action</th></tr>\n";
$userdbh->query("select name,upper(name) from SQLITE_MASTER where type = 'table' order by 2");
while($row = $userdbh->fetchArray()) {
	print "<tr><td>".$row[0]."</td>\n";
	$userdbh2->query("select count(*) from $row[0]");
	while($row2 = $userdbh2->fetchArray()) {
		$numrows = $row2[0];
	}
	print "<td>$numrows</td><td>\n";
	print_table_action_links($row[0]);
	print "</td></tr>\n";
}
print "</table><br>\n";



echo<<<EOT
<h3>Database operations:</h3>

<table class="blind">
<form action="table_create.php" method=post onsubmit="">
<tr>
<td>Create a new table named</td>
<td><input type=text name=tablename value="" size=20><td>with</td>
<td><input type=text name=columns value="" size=3> colums</td>
<td><input type=submit name=submit value="Go"></td>
</tr>
</form>


<!--
<form action="index_create.php" method=post onsubmit="">
<tr>
<td>Create an index on table</td>
<td><select name=create_index>\n
EOT;

foreach($rows as $row) {
	print "<option value=\"$row[0]\">$row[0]</option>\n";
}

echo<<<EOT
</select></td>
<td colspan=3 align=right><input type=submit name=submit value="Go"></td>
</tr>
</form>
-->

<tr><td colspan=5><a href="dbaction.php?action=schema" target="mainframe">Show Database schema</a></td></tr>
<tr><td colspan=5><a href="dbaction.php?action=vacuum" target="_top" onclick="return confirm_vacuum_db();">Vacuum Database</a></td></tr>
EOT;

if ($current_db != 'phpsla.sqlite') print "<tr><td colspan=5><a href=\"dbaction.php?action=drop\" target=\"_top\" onclick=\"return confirm_drop_db();\">Drop Database</a></td></tr>\n";

print "</table>\n";


print "</body>\n";
print "</html>\n";


?>
