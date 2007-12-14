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
		print "<th>Test Date</th>\n";
		print "<th>Testing revision</th>\n";

		// successful
		$query = $DB->query ("
				SELECT	c.revision, c.author, t.pass, t.fail, t.skip, t.timeout, c.test_date, c.test_revision, c.failed
				FROM		complete AS c, tests AS t
				WHERE		t.revision == c.revision AND t.testname == 'Total'
				ORDER BY c.revision DESC
				");
		$pass_completes = $query->fetchAll(PDO::FETCH_ASSOC);


		// failed
		$query = $DB->query ("
				SELECT	revision, author, '' AS pass, '' AS fail, '' as skip, '' as timeout, test_date, test_revision, failed
				FROM		complete
				WHERE		failed == 1
				ORDER BY revision DESC
				");
		$fail_completes = $query->fetchAll(PDO::FETCH_ASSOC);

		$completes = array_merge ($pass_completes, $fail_completes);
		

		# arrange by revision
		foreach ($completes as $complete)
		{
			$rev = (int)$complete["revision"];
			$revisions[$rev] = $complete;
		}

		krsort ($revisions);

		# process data
		foreach ($revisions as $rev => &$data)
		{
			$data["difference"] = add_difference ("pass", $data, $revisions[$rev-1]);
			add_difference ("fail", $data, $revisions[$rev-1]);
			add_difference ("skip", $data, $revisions[$rev-1]);
			add_difference ("timeout", $data, $revisions[$rev-1]);

			$data["test_date"] = date_from_timestamp ($data["test_date"]);
			unset ($data["failed"]);
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

