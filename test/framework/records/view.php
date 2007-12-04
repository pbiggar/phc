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

	# arrange by revision
	foreach ($completes as $complete)
	{
		$rev = (int)$complete["revision"];
		$revisions[$rev] = $complete;
	}

	# process data
	foreach ($revisions as $rev => &$data)
	{
		$data["difference"] = add_difference ("pass", $data, $revisions[$rev-1]);
		add_difference ("fail", $data, $revisions[$rev-1]);
		add_difference ("skip", $data, $revisions[$rev-1]);
		add_difference ("timeout", $data, $revisions[$rev-1]);
	}


	# print out rows
	foreach ($revisions as $rev => $data)
	{
		print "<tr>\n";

		# pick a color
		$color = "white";
		if ($data["difference"] > 0)
			$color = "green";
		elseif ($data["difference"] < 0)
			$color = "red";
		unset ($data["difference"]);


		foreach ($data as $key => $value)
		{
			print "<td style=\"color: $color; background-color: #8a7640;\" >$value</td>";
		}
		print "</tr>\n";
	}

	# add a string with the difference of the old data to the new data
	function add_difference ($name, &$new, $old)
	{
		if ($old)
		{
			$difference = $new [$name] - $old[$name];
			if ($difference < 0)
				$new[$name] .= " ($difference)";
			elseif ($difference > 0)
				$new[$name] .= " (+$difference)";
		}
		return $difference;
	}

?>
		</table>
	</body>
</html>
