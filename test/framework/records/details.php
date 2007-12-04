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
<?php

	$rev = (int)$_GET["rev"];

	if ($rev == 0)
		die ("Invalid revision: {$_GET["rev"]}.");

	$DB = new PDO ("sqlite:results/results.db");
	$td = "td style=\"color: white; background-color: #8a7640;\"";
	$th = "th style=\"color: black; background-color: #8a7640;\" ";

	print_revision_details ($rev);
	print "<table width=\100%><tr><td>\n";
	print_test_details ($rev, "tests");
	print "</td><td>\n";
	print_test_details ($rev, "install_tests");
	print "</td></tr></table>\n";

	function print_revision_details ($rev)
	{
		global $DB, $td, $th;
		$complete_data = $DB->query ("
				SELECT	*
				FROM		complete
				WHERE		revision == $rev 
				")->fetchAll(PDO::FETCH_ASSOC);
		assert (count ($complete_data) == 1);
		$complete_data = $complete_data[0];

		print "<table cellpadding=\"0\">";
		print "<tr><td>\n";
		print "<table width=\"100%\" cellpadding=\"5\">";
		print "<tr>	<$th>	Revision:		</th><$td>"	.$complete_data["revision"].		"	</td>";
		print "		<$th>	Author:			</th><$td>"	.$complete_data["author"].			"	</td>";
		print "<tr>	<$th>	Test duration:	</th><$td>"	.($complete_data["time"]/60.0).	"m	</td>";
		print "		<$th>	Commit date:	</th><$td>"	.$complete_data["commit_date"].	"	</td></tr></table>";
		print "</td><td><table>\n";
		print "		<$th><a href=\"results/$rev/log\">					Log					</a>	</th>";
		print "		<$th><a href=\"results/$rev/configure.log\">		Configure log		</a>	</th></tr>";
		print "<tr>	<$th><a href=\"results/$rev/make.log\">			Build log			</a>	</th>";
		print "		<$th><a href=\"results/$rev/install.log\">		Install log			</a>	</th></tr>";
		print "<tr>	<$th><a href=\"results/$rev/test.log\">			Test log				</a>	</th>";
		print "		<$th><a href=\"results/$rev/install_test.log\">	Install Test log	</a>	</th></tr>";
		print "</table></td></tr></table>";
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

		print "<table width=\"100%\" cellpadding=\"3\">";
		print "<tr><$th colspan=5>$table</th></tr>\n";
		print "<tr><$th>Test name</th><$th>Passes</th><$th>Fails</th><$th>Timeouts</th><$th>Skips</th></tr>\n";

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
			$color = "white";
			if ($row["difference"] > 0)
				$color = "green";
			elseif ($row["difference"] < 0)
				$color = "red";
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
				print "<td style=\"color: $color; background-color: #8a7640;\">$entry</td>";
			}
			print "</tr>\n";
		}

		print "</table>\n";
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
