<?php

include ("common.php");

	function run_main ()
	{
		$rev = (int)$_GET["rev"];

		if ($rev == 0)
			die ("Invalid revision: {$_GET["rev"]}.");

		print_revision_details ($rev);
		print "<table class=layout><tr><td>\n";
		print_test_details ($rev, "tests");
		print "</td><td>\n";
		print_test_details ($rev, "install_tests");
		print "</td></tr></table>\n";

	}

	function print_revision_details ($rev)
	{
		global $DB;
		$complete_data = $DB->query ("
				SELECT	*
				FROM		complete
				WHERE		revision == $rev 
				")->fetchAll(PDO::FETCH_ASSOC);
		assert (count ($complete_data) == 1);
		$complete_data = $complete_data[0];

		print "<table class=layout>";
		print "	<tr><td>\n";

		print "<table class=info>";
		print "	<tr>\n";
		print "		<th>Revision:					</th><td>"	.$complete_data["revision"].	"</td>";
		print "		<th>Author:						</th><td>"	.$complete_data["author"].		"</td>";
		print "	</tr><tr>\n";
		print "		<th>Test duration:			</th><td>"	.($complete_data["time"]/60.0).	"m	</td>";
		print "		<th>Commit date:				</th><td>"	.$complete_data["commit_date"].	"	</td>";
		print "	</tr><tr>\n";
		print "		<th>Testing Date:				</th><td>"	.date_from_timestamp ($complete_data["test_date"]).		"</td>";
		print "		<th>Tested with revision:	</th><td>"	.$complete_data["test_revision"]."</td>";
		print "	</tr>\n";
		print "</table>\n";

		print "	</td><td>\n";

		print "<table class=info>\n";
		print "	<tr>\n";
		print "		<th><a href=\"results/$rev/log\">					Log					</a>	</th>";
		print "		<th><a href=\"results/$rev/configure.log\">		Configure log		</a>	</th>";
		print "	</tr><tr>\n";
		print "		<th><a href=\"results/$rev/make.log\">				Build log			</a>	</th>";
		print "		<th><a href=\"results/$rev/install.log\">			Install log			</a>	</th>";
		print "	</tr><tr>\n";
		print "		<th><a href=\"results/$rev/test.log\">				Test log				</a>	</th>";
		print "		<th><a href=\"results/$rev/install_test.log\">	Install Test log	</a>	</th>";
		print "	</tr></table>";

		print "	</td></tr>";
		print "</table>\n";
	}

	function print_test_details ($rev, $table)
	{
		global $DB, $td, $th;;

		# fetch the current revisions data
		$test_data = $DB->query ("
				SELECT	revision, testname, pass, fail, timeout, skip
				FROM		$table
				WHERE		revision == $rev
				")->fetchAll(PDO::FETCH_ASSOC);

		print "<table class=info>";
		print "<tr><th colspan=5>$table</th></tr>\n";
		print "<tr><th>Test name</th><th>Passes</th><th>Fails</th><th>Timeouts</th><th>Skips</th></tr>\n";

		# fetch the previous revisions data, for comparison
		$old_rev = $rev - 1;
		$old_test_data = $DB->query ("
				SELECT	revision, testname, pass, fail, timeout, skip
				FROM		$table
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
				$row["testname"] = "<a href=\"results/$rev/{$table}_logs/\">$name</a>";
			else
				$row["testname"] = "<a href=\"results/$rev/{$table}_logs/$name/\">$name</a>";

			print "<tr>\n";
			foreach ($row as $key => $entry)
			{
				print "<td$color>$entry</td>";
			}
			print "</tr>\n";
		}

		print "</table>\n";
	}



?>
