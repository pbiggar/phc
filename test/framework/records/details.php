<?php

	$test_order = array (
			"Total",
			"Annotated_test",
			"BasicParseTest",
			"NoWhitespace",
			"cb_ast",
			"cb_sua",
			"cb_AST-to-HIR",
			"cb_hir",
			"cb_mir",
			"HIR-to-MIR_dump",
			"mir_dump",
			"InterpretOptimized",
			"InterpretCanonicalUnparsed",
			"InterpretStrippedIncludes",
			"InterpretObfuscated",
			"Generate_C",
			"CompiledVsInterpreted",
			"CompileOptimized",
			"RaisedCompileOptimized",
			"Refcounts",
			"Demi_eval_false",
			"Demi_eval_true",
			"ParseASTDot",
			"plugin_inconsistent_st_attr",
			"plugin_linear",
			"plugin_cloning",
			"plugin_pre_vs_post_count",
			"ReparseUnparsed",
			"plugin_source_vs_semantic_values",
			"CompilePluginTest",
			"XML_roundtrip",
			"regression_dump_ast",
			"regression_dump_php",
			"regression_dump_xml",
			);
	$benchmark_order = array (
			"instruction",
			"instruction_l1_miss",
			"instruction_l2_miss",
			"data",
			"data_l1_miss",
			"data_l1_miss_read",
			"data_l1_miss_write",
			"data_l2_miss",
			"data_l2_miss_read",
			"data_l2_miss_write",
			"data_read",
			"data_write",
			"l2",
			"l2_miss",
			"l2_miss_read",
			"l2_miss_write",
			"l2_read",
			"l2_write",
			"branch",
			"branch_conditional",
			"branch_conditional_misprediction",
			"branch_indirect",
			"branch_indirect_misprediction",
			"branch_misprediction",

			);

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
		print "		<tr><td valign=top>\n";
		print_test_details ($rev, $old_rev);
		print "		</td><td valign=top>\n";
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
		print "		<th>". maybe_link ($rev, $old_rev, "log.log",			"Log")			."</th>";
		print "		<th>Revision:						</th><td><a href=\"http://code.google.com/p/phc/source/detail?r=$rev\">"	.$complete_data["revision"]		."</a></td>";
		print "		<th>Branch:							</th><td>"	.$complete_data["branch"]			."</td>";
		print "		<th>Author:							</th><td>"	.$complete_data["author"]			."</td>";
		print "		<th>Commit date:					</th><td>"	.$complete_data["commit_date"]	."	</td>";
		print "	</tr>";
		print "</table>";
		print "<table class=info>";
		print_component_header ();
		print_component_row ("compile", $rev, $old_rev);
		print_component_row ("test", $rev, $old_rev);
		print_component_row ("benchmark", $rev, $old_rev);
		print "</table>";
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

	function print_component_header ()
	{
		print "<tr>\n";
		print "<th>Log</th>\n";
		print "<th>Time taken</th>\n";
		print "<th>Test date</th>\n";
		print "<th>Revision used</th>\n";
		print "<th>Failed</th>\n";
		print "<th>Redo</th>\n";
		print "</tr>\n";
	}


	function print_component_row ($component, $rev, $old_rev)
	{
		global $DB;
		$uc_name = ucfirst ($component);
		$log_title = $uc_name;
		$log_file = "$component.log";

		print "<tr>";
		print "<td>". maybe_link ($rev, $old_rev, $log_file, $log_title). "</td>";
		$data = $DB->query ("
				SELECT	time_taken, test_date, revision_used, failed, redo
				FROM		components
				WHERE		revision == $rev
				AND		component == '$component'
				")->fetchAll(PDO::FETCH_ASSOC);

		if (isset ($data[0]))
			foreach ($data[0] as $key => $value)
			{
				if ($key == "test_date")
					$value = date_from_timestamp ($value);
				else if ($key == "time_taken")
					$value = minutes_from_seconds ($value);

				print "<td>$value</td>";
			}


		print "\n</tr>";
	}

	function print_test_details ($rev, $old_rev)
	{
		global $DB, $td, $th, $test_order;

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

		$test_data = order_by ($test_data, $test_order, "testname");

		# print
		foreach ($test_data as $row)
		{
			$row = $row[0];
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
				print "<td $color>$entry</td>";
			}
			print "</tr>\n";
		}
		print "</table>";
	}

	function print_benchmark_details ($rev, $old_rev)
	{
		global $DB, $td, $th, $benchmark_order;

		# fetch the current revisions data
		$test_data = $DB->query ("
				SELECT	revision, name, metric, result
				FROM		benchmarks
				WHERE		revision == $rev
				")->fetchAll(PDO::FETCH_ASSOC);

		print "<table class=info>";
		print "<tr>"
			. "<th>Benchmark</th>"
			. "<th>Metric</th>"
			. "<th>Result (+/- vs "
			. "<a href='details.php?rev=$old_rev'>$old_rev</a>"
			. ")</th>";

		# fetch the previous revisions data, for comparison
		$old_test_data = $DB->query ("
				SELECT	revision, name, metric, result
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

		$test_data = order_by ($test_data, $benchmark_order, "metric");

		# print
		foreach ($test_data as $row_set)
		{
			foreach ($row_set as $row)
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
					print "<td $color>$entry</td>";
				}
				print "</tr>\n";
			}
		}
		print "</table>";
	}

	/*
	 * Return a new array with DATA sorted. The key for sorting is
	 * $DATA[$ROW_INDEX], and it should be ordered by the order in which it
	 * appears in $ORDERING.
	 */
	function order_by ($data, $ordering, $row_index)
	{
		$result = array ();
		$indexed = array ();

		// Make an index
		foreach ($data as $row)
		{
			$indexed[$row[$row_index]][] = $row;
		}

		// Put them in order
		foreach ($ordering as $name)
		{
			if (isset ($indexed[$name]))
			{
				$result[] = $indexed[$name];
				unset ($indexed[$name]);
			}
		}

		// There might be some left - put them on the end
		foreach ($indexed as $row)
			$result[] = $row;

		return $result;
	}


?>
