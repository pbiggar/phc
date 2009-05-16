<?php

//	error_reporting (E_ALL);
	$ABBREVIATIONS = array ("branches/dataflow" => "df",
									"branches/0.2.0" => "0.2.0", "unknown_branch" => "??",
									"paul.biggar" => "pb", "edskodevries" => "edv",
									);


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
			"time_taken",
			"test_date",
			"revision_used",
			"failed",
			"redo");

		foreach ($order as $header)
		{
			$headers[$header] = ucfirst (str_replace ("_", " ", $header));
		}
		$headers["revision"] = "Rev";
		$headers["revision_used"] = "Test rev";
		$headers["time_taken"] = "Time";
		$headers["benchmark"] = "Bench";
		$headers["timeout"] = "T/O";


		print "<table class=info>\n";
		print "<tr>\n";
		foreach (array_values ($headers) as $header)
			print "<th>$header</th>\n";

		// Completed tests
		$query = $DB->query ("
				SELECT	revision, branch, author
				FROM		complete
				");
		$completes = $query->fetchAll(PDO::FETCH_ASSOC);

		// Test results
		$query = $DB->query ("
				SELECT	revision, pass, fail, skip, timeout
				FROM		tests
				WHERE		testname == 'Total'
				");
		$tests = $query->fetchAll(PDO::FETCH_ASSOC);

		// Benchmark results
		$query = $DB->query ("
				SELECT	revision, result as benchmark
				FROM		benchmarks
				WHERE		metric = 'All'
				");
		$benchmarks = $query->fetchAll(PDO::FETCH_ASSOC);

		// Compile meta-results
		$query = $DB->query ("
				SELECT	revision, component, time_taken, test_date, revision_used, failed, redo
				FROM		components
				WHERE		component == 'compile'
				");

		$compile_meta = $query->fetchAll(PDO::FETCH_ASSOC);

		// Test meta-results
		$query = $DB->query ("
				SELECT	revision, component, time_taken, test_date, revision_used, failed, redo
				FROM		components
				WHERE		component == 'test'
				");
		$test_meta = $query->fetchAll(PDO::FETCH_ASSOC);

		// Bench meta-results
		$query = $DB->query ("
				SELECT	revision, component, time_taken, test_date, revision_used, failed, redo
				FROM		components
				WHERE		component == 'benchmark'
				");
		$bench_meta = $query->fetchAll(PDO::FETCH_ASSOC);

		$query = $DB->query ("SELECT revision FROM running");
		$running = $query->fetchAll(PDO::FETCH_ASSOC);
		$running = $running[0]["revision"];




		$revisions = array_reduce (array ($completes, $tests, $benchmarks, $compile_meta, $test_meta, $bench_meta), "merge_results");



		ksort ($revisions);

		# process data
		foreach ($revisions as $rev => &$data)
		{
			// Always use the correct branch for relative data
			$branch = $data["branch"];

			$data["difference"] = add_difference ("pass", $data, $revisions[$prev[$branch]]);
			add_difference ("fail", $data, $revisions[$prev[$branch]]);

			$prev[$branch] = $rev;
		}

		$revisions = array_reverse ($revisions, true);


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

			if ($rev == $running)
				$color = get_running_color ();


			# add a link to revision
			$data["revision"] = "<a href=\"details.php?rev=$rev\">$rev</a>";
			if (isset ($data["test_date"]))
				$data["test_date"] = date_from_timestamp ($data["test_date"]);
			if (isset ($data["time_taken"]))
				$data["time_taken"] = minutes_from_seconds($data["time_taken"]);

			foreach ($order as $header)
			{
				$value = $data[$header];
				print "<td $color>$value</td>\n";
			}
			print "<a/></tr>\n";
		}
	}

	function merge_results ($results, $new_results)
	{
		global $ABBREVIATIONS;

		foreach ($new_results as $new_result)
		{
			$rev = (int)$new_result["revision"];
			foreach ($new_result as $key => $value)
			{
				// abbreviate long words
				if (isset ($ABBREVIATIONS[$value]))
					$value = $ABBREVIATIONS[$value];

				// Result processing (hard to do this one elsewhere)
				if ($key == "failed" || $key == "redo")
				{
					if ($value  == 1)
						$value = strtoupper ($new_result["component"][0]);
					else
						$value = "";
				}



				// Use the larger of the two, if set.
				if (isset ($results[$rev][$key]))
				{
					$old_value =& $results[$rev][$key];

					if ($key == "revision")
						; // do nothing
					else if ($key == "time_taken")
						$value = $old_value + $value;
					else if ($key == "revision_used")
						$value = "$old_value, $value";
					else if ($key == "failed")
						$value = "$old_value$value";
					else if ($key == "test_date")
						$value = max ($old_value, $value);
					else if ($key == "redo")
						$value = "$old_value$value";
					else if ($key == "component")
						; // dont care
					else
						die ("Overwriting $rev, $key ($old_value) with $value");
				}

				$results[$rev][$key] = $value;
			}
		}
		return $results;
	}


?>

