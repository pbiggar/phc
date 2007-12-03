<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
	<head>
		<title>phc -- the open source PHP compiler</title>
		<link rel="stylesheet" type="text/css" href="phc.css">
	</head>
	<body>
		<table>
			<tr>
				<td>
					<table width="100%" cellpadding="5">
						<tr>
							<th>Revision</th>
							<th>Author</th>
							<th>Passes</th>
							<th>Fails</th>
							<th>Skips</th>
							<th>Timeouts</th>
<?php

	$DB = new PDO ("sqlite:results/results.db");
	$query = $DB->query ("
			SELECT	c.revision, c.author, t.pass, t.fail, t.skip, t.timeout
			FROM		complete AS c, tests AS t
			WHERE		t.revision == c.revision AND t.testname == 'Total'
			ORDER BY c.revision DESC
			");
	
	$completes = $query->fetchAll(PDO::FETCH_ASSOC);


	foreach ($completes as $complete)
	{
		print "<tr>\n";
		foreach ($complete as $entry)
		{
			print "<td style=\"color: white; background-color: #8a7640;\" >$entry</td>";
		}
		print "</tr>\n";
	}

?>
		</table>
	</body>
</html>
