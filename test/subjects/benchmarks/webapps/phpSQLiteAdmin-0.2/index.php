<?php

require_once('include.php');

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Frameset//EN">
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
	<meta http-equiv="expires" content="0">
	<title>phpSQLiteAdmin</title>
	<script language="Javascript" src="javascript.txt" type="text/javascript"></script>
	<link href="phpsla.css" rel="stylesheet" type="text/css">
</head>

<frameset cols="150,*">
<!--
<frame src="leftframe.php?<?=SID?>" name=tablelist scrolling=auto>
<frame src="mainframe.php?<?=SID?>" name=mainframe scrolling=auto>
-->
<frame src="leftframe.php" name=tablelist scrolling=auto>
<frame src="mainframe.php" name=mainframe scrolling=auto>
</frameset>

</html>
