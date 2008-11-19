<?php

	include ("common.php");

	function run_main ()
	{
		global $DB;

		$order = array (
			"revision",
			"branch",
			"author",
			"pass",
			"fail",
			"skip",
			"timeout",
			"benchmark",
			"test_date",
			"test_revision",
			"redo");

		print "<table class=info>\n";
		print "<tr>\n";
		foreach ($order as $header)
		{
			$header = ucfirst (str_replace ("_", " ", $header));
			print "<th>$header</th>\n";
		}

		// Completed tests
		$query = $DB->query ("
				SELECT	revision, author, test_date, test_revision, benchmark, branch, failed, redo
				FROM		complete
				");
		$completes = $query->fetchAll(PDO::FETCH_ASSOC);

		foreach ($completes as $complete)
		{
			$rev = (int)$complete["revision"];
			foreach ($complete as $key => $column)
				$revisions[$rev][$key] = $column;
		}


		// Test results
		$query = $DB->query ("
				SELECT	revision, pass, fail, skip, timeout
				FROM		tests
				WHERE		testname == 'Total'
				");
		$tests = $query->fetchAll(PDO::FETCH_ASSOC);

		foreach ($tests as $test)
		{
			$rev = (int)$test["revision"];
			foreach ($test as $key => $column)
				$revisions[$rev][$key] = $column;
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

			foreach ($order as $header)
			{
				$value = $data[$header];
				print "<td$color>$value</td>\n";
			}
			print "<a/></tr>\n";
		}

	}
?>

