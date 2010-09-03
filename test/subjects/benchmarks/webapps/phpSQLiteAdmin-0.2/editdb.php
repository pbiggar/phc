<?php

require_once('include.php');

$title = 'Add new database alias:';
$action = 'insert';
$createdb = 'read-only';

$alias = new dbalias;
$alias->user = $current_user;
$alias->alias = $_POST['alias'];
$alias->path = $_POST['path'];
$alias->description = $_POST['description'];


if (isset($_POST['insert'])) {
	// create the new db is case it does not exist
	if (!file_exists($alias->path)) $newdb =& new SPSQLite($alias->path);
	$sysdbh->query("insert into databases (user,alias,path,description) values ({$alias->user},'{$alias->alias}','{$alias->path}','{$alias->description}')");
	// do we really want this?
	$_SESSION['phpSQLiteAdmin_currentdb'] = $alias->path;
	header("Location: index.php");
	exit;
}


if (isset($_GET['alias'])) {
	$sysdbh->query("select user,alias,path,description from databases where user = $current_user and alias = '".$_GET[alias]."'");
	while($row = $sysdbh->fetchArray()) {
		$alias = new dbalias;
		$alias->alias = $row[1];
		$alias->path = $row[2];
		$alias->description = $row[3];
		$title = 'Edit database alias:';
		$action = 'update';
	}
}


if (isset($_POST['update'])) {
	$sysdbh->query("update databases set alias = '{$alias->alias}', path = '{$alias->path}', description = '{$alias->description}' where user = {$alias->user} and alias = '{$_POST[oldalias]}'");
	header("Location: index.php");
	exit;
}


if (isset($_POST['delete'])) {
	$sysdbh->query("delete from databases where user = {$alias->user} and alias = '{$alias->alias}'");
	//unlink($alias->path); nooooooo don't do that...
	$_SESSION['phpSQLiteAdmin_currentdb'] = '';
	header("Location: index.php");
	exit;
}

$type = text;

echo<<<EOT
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN">
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
	<title>phpSQLiteAdmin</title>
	<meta http-equiv="expires" content="0">
	<script language="javascript" src="javascript.txt" type="text/javascript"></script>
	<link href="phpsla.css" rel="stylesheet" type="text/css">
</head>
<body class="right" onload="document.adddb.alias.focus();">
<h3>$title</h3>
<form name="adddb" action="editdb.php" method="post" target="_top">
<input type="hidden" name="oldalias" value="{$_GET[alias]}">
<table>
<tr><td class=label>Alias:</td><td><input type=text size=80 name=alias value="{$alias->alias}"></td></tr>
<tr><td class=label>Path on server:</td><td><input type=$type size=80 name=path value="{$alias->path}"></td></tr>
<tr><td class=label>Description:</td><td><input type=text size=80 name=description value="{$alias->description}"></td></tr>
<tr><td class=label></td><td class=label><input type=submit name=$action value="Save"> <input type=button value="Cancel" onClick="history.back();"></td></tr>
</form>
</table>
EOT;


if (isset($_GET['alias'])) {
echo<<<EOT
<br><br><br><br><br>
<form name=delete action=editdb.php method=post onsubmit="" target="_top">
<input type=hidden name=user value="{$current_user}">
<input type=hidden name=alias value="{$_GET[alias]}">
<input type=submit name=delete value="Remove this alias">
</form>
EOT;
}


print "</body>\n";
print "</html>\n";


?>