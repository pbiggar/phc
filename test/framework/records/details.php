<?php

	include ("common.php");

	function run_main ()
	{
		$rev = (int)$_GET["rev"];

		if ($rev <= 0)
			die ("Invalid revision: {$_GET["rev"]}.");

		$old_rev = get_prev_revision ($rev);
		$old_bench_rev = get_prev_revision ($rev, "bench");

		print "<table class=layout>";
		print "	<tr><td colspan=2>\n";
		print_revision_details ($rev, $old_rev, $old_bench_rev);
		print "	</td></tr>\n";
		print "	<tr><td>\n";
		print "		<table class=layout>";
		print "		<tr><td>\n";
		print_test_details ($rev, $old_rev);
		print "		</td><td>\n";
		print_benchmark_details ($rev, $old_bench_rev);
		print "		</td></tr>\n";
		print "		</table>";
		print "	</td></tr>\n";
		print "</table>";

	}

	function print_revision_details ($rev, $old_rev, $old_bench_rev)
	{
		global $DB;
		$complete_data = $DB->query ("
				SELECT	*
				FROM		complete
				WHERE		revision == $rev 
				")->fetchAll(PDO::FETCH_ASSOC);
		if (count ($complete_data) != 1)
			die ("Revision not available: $rev");

		$complete_data = $complete_data[0];

		print "<table class=info>";
		print "	<tr>\n";
		print "		<th>Revision:					</th><td>"	.$complete_data["revision"].	"</td>";
		print "		<th>Branch:						</th><td>"	.$complete_data["branch"].		"</td>";
		print "	</tr><tr>\n";
		print "		<th>Test duration:			</th><td>"	.(round ($complete_data["time"]/60.0, 1))."m	</td>";
		print "		<th>Author:						</th><td>"	.$complete_data["author"].		"</td>";
		print "	</tr><tr>\n";
		print "		<th>" . maybe_link ($rev, $old_bench_rev, "benchmark.log", "Benchmark").":</th><td>"	.$complete_data["benchmark"]."</td>";
		print "		<th>Commit date:				</th><td>"	.$complete_data["commit_date"].	"	</td>";
		print "	</tr>\n";
		print "</table>\n";

		print "	</td><td>\n";

		print "<table class=info>\n";
		print "	<tr>\n";
		print "		<th>". maybe_link ($rev, $old_rev, "log.log", "Full Log") ."</th>";
		print "		<th>". maybe_link ($rev, $old_rev, "configure.log", "Configure Log") ."</th>";
		print "	</tr><tr>\n";
		print "		<th>". maybe_link ($rev, $old_rev, "make.log", "Build Log") ."</th>";
		print "		<th>". maybe_link ($rev, $old_rev, "install.log", "Install Log") ."</th>";
		print "	</tr><tr>\n";
		print "		<th>". maybe_link ($rev, $old_rev, "test.log", "Test Log") ."</th>";
		print "		<th colspan=2><a href=\"http://code.google.com/p/phc/source/detail?r=$rev\">Commit log</a></th>";
		print "	</tr></table>";

		print "	</td></tr>";
		print "</table>\n";
	}

	function maybe_link ($rev, $old_rev, $filename, $name, $sort = false)
	{
		$file = "results/$rev/$filename";
		if (file_exists ($file))
		{
			$old_file = "results/$old_rev/$filename";
			if (file_exists ($old_file))
				return "<a href=\"$file\">$name</a> (<a href=\"diff.php?new_rev=$rev&old_rev=$old_rev&sort=$sort&filename=$filename\">D</a>)";
			else
				return "<a href=\"$file\">$name</a>";
		}
		else
			return $name;
	}

	function print_test_details ($rev, $old_rev)
	{
		global $DB, $td, $th;

		# fetch the current revisions data
		$test_data = $DB->query ("
				SELECT	revision, testname, pass, fail, timeout, skip
				FROM		tests
				WHERE		revision == $rev
				")->fetchAll(PDO::FETCH_ASSOC);

		print "<table class=info>";
		print "<tr><th>"
			. "Test Name (+/- vs "
			. "<a href='details.php?rev=$old_rev'>$old_rev</a>"
			. ")</th><th>"
			. maybe_link ($rev, $old_rev, "test_logs/success", "Passes", true) ."</th><th>"
			. maybe_link ($rev, $old_rev, "test_logs/failure", "Fails", true) ."</th><th>"
			. maybe_link ($rev, $old_rev, "test_logs/timeout", "Timeouts", true) ."</th><th>"
			. maybe_link ($rev, $old_rev, "test_logs/skipped", "Skips", true) ."</th></tr>\n";

		# fetch the previous revisions data, for comparison
		$old_test_data = $DB->query ("
				SELECT	revision, testname, pass, fail, timeout, skip
				FROM		tests
				WHERE		revision == $old_rev
				")->fetchAll(PDO::FETCH_ASSOC);

		# process data
		foreach ($test_data as &$row)
		{
			$old_row = array_shift ($old_test_data);
			$row ["difference"] = add_difference ("pass", $row, $old_row);
			add_difference ("fail", $row, $old_row);
			add_difference ("skip", $row, $old_row);
			add_difference ("timeout", $row, $old_row);
		}
		unset ($row); // release the reference to $row

		# print
		foreach ($test_data as $row)
		{
			unset ($row["revision"]);

			# pick a color
			$color = "";
			if ($row["difference"] > 0)
				$color = get_good_color ();
			elseif ($row["difference"] < 0)
				$color = get_bad_color ();
			unset ($row["difference"]);

			# add a link onto the name
			$name = $row["testname"];
			if ($name == "Total")
				$row["testname"] = "<a href=\"results/$rev/test_logs/\">$name</a>";
			else if ($row["fail"])
				$row["testname"] = "<a href=\"results/$rev/test_logs/$name.tar.gz\">$name</a>";

			print "<tr>\n";
			foreach ($row as $key => $entry)
			{
				print "<td$color>$entry</td>";
			}
			print "</tr>\n";
		}
		print "</table>";
	}

	function print_benchmark_details ($rev, $old_rev)
	{
		global $DB, $td, $th;

		# fetch the current revisions data
		$test_data = $DB->query ("
				SELECT	revision, metric, result
				FROM		benchmarks
				WHERE		revision == $rev
				")->fetchAll(PDO::FETCH_ASSOC);

		print "<table class=info>";
		print "<tr><th>Metric</th><th>"
			. "Result (+/- vs "
			. "<a href='details.php?rev=$old_rev'>$old_rev</a>"
			. ")</th><th>";

		# fetch the previous revisions data, for comparison
		$old_test_data = $DB->query ("
				SELECT	revision, metric, result
				FROM		benchmarks
				WHERE		revision == $old_rev
				")->fetchAll(PDO::FETCH_ASSOC);

		# process data
		foreach ($test_data as &$row)
		{
			$old_row = array_shift ($old_test_data);
			$row ["difference"] = add_percentage_difference ("result", $row, $old_row);
		}
		unset ($row); // release the reference to $row

		# print
		foreach ($test_data as $row)
		{
			unset ($row["revision"]);

			# pick a color
			$color = "";
			if ($row["difference"] > 0)
				$color = get_bad_color ();
			elseif ($row["difference"] < 0)
				$color = get_good_color ();
			unset ($row["difference"]);

			print "<tr>\n";
			foreach ($row as $key => $entry)
			{
				print "<td$color>$entry</td>";
			}
			print "</tr>\n";
		}
		print "</table>";
	}


?>
