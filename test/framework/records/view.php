<?php

	include ("common.php");

	function run_main ()
	{
		global $DB;

		print "<table class=info>\n";
		print "<tr>\n";
		print "<th>Revision</th>\n";
		print "<th>Author</th>\n";
		print "<th>Passes</th>\n";
		print "<th>Fails</th>\n";
		print "<th>Skips</th>\n";
		print "<th>Timeouts</th>\n";

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
			$color = "";
			if ($data["difference"] > 0)
				$color = get_good_color ();
			elseif ($data["difference"] < 0)
				$color = get_bad_color ();
			unset ($data["difference"]);

			# add a link to revision
			$data["revision"] = "<a href=\"details.php?rev=$rev\">$rev</a>";


			foreach ($data as $key => $value)
			{
				print "<td$color>$value</td>\n";
			}
			print "<a/></tr>\n";
		}

	}
?>

