<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
	<head>
		<title>phc -- the open source PHP compiler</title>
		<style type="text/css">
			table.layout { width: 100%; border-collapse: collapse  }
			table.info { width: 100%; }
			table.info td { color: gray; background-color: #efdba7 }
			table.info th { color: black; background-color: #efdba7 }
		</style>
	</head>
	<body>
<?php
	$DB = new PDO ("sqlite:results/results.db");

	run_main ();

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

	function add_percentage_difference ($name, &$new, $old)
	{
		if ($old)
		{
			$difference = ($new [$name] - $old[$name]);
			$difference_percentage = ($difference * 100 / $old[$name]);
			if (abs ($difference_percentage) < 1/10) // ignore 1/10th of percent or less
				$difference_percentage = 0;
			else
				$difference_percentage = round ($difference_percentage, 1);

			if ($difference_percentage < 0)
				$new[$name] .= " ($difference [$difference_percentage%])";
			elseif ($difference_percentage > 0)
				$new[$name] .= " (+$difference [$difference_percentage%])";
		}
		return $difference_percentage;
	}


	function date_from_timestamp ($timestamp)
	{
		if ($timestamp == 0)
			return "";

		return date ("d M Y H:i:s ", $timestamp);
	}

	function minutes_from_seconds ($seconds)
	{
		if ($seconds == 0)
			return "";

		return round ($seconds/60.0, 1)."m";
	}

	function get_good_color () { return "style=\"color:green; font-weight: bold\""; }
	function get_bad_color ()	{ return "style=\"color:red; font-weight: bold;\""; }
	function get_running_color ()	{ return "style=\"color:white; background-color:black;\""; }

	// TODO copied from lib/header.php. Avoid duplication
	/* Prints diffs if the xdiff extension is available, and simple outputs
	 * both strings otherwise. 
	 * To install xdiff:
	 *   install libxdiff from http://www.xmailserver.org/xdiff-lib.html 
	 *   install xdiff from pecl with "pecl install xdiff". 
	 *   There is no need to load xdiff.so in your php.ini file. */
	function diff ($string1, $string2)
	{
		if (!extension_loaded ("xdiff"))
		{
			$result = @dl ("xdiff.so"); // avoid the E_WARNING
			if (!$result)
			{
				return "Note: xdiff not available for diffing. Outputting both strings:\nString1:\n$string1\nString2:\n$string2";
			}
		}
		return xdiff_string_diff ("$string1\n", "$string2\n");
	}

	function get_prev_revision ($rev, $has_benchmark_results = false)
	{
		global $DB;
		$branch = get_branch ($rev);

		if ($has_benchmark_results)
		{
			// To avoid an edge case here, the results have artificial data for
			// revision 0.
			$data = $DB->query ("
					SELECT	complete.revision as rev
					FROM		complete, components
					WHERE		rev < $rev
								AND branch == '$branch'
								AND components.component == 'benchmark'
								AND components.revision == rev
					")->fetchAll(PDO::FETCH_ASSOC);
		}
		else
		{
			$data = $DB->query ("
					SELECT	revision as rev
					FROM		complete
					WHERE		rev < $rev
					AND		branch == '$branch'
					")->fetchAll(PDO::FETCH_ASSOC);
		}

		rsort ($data);

		if ($data === false)
			return 0;

		return $data[0]["rev"];


	}

	function get_branch ($rev)
	{
		global $DB;
		$data = $DB->query ("
				SELECT	branch
				FROM		complete
				WHERE		revision == $rev 
				")->fetchAll(PDO::FETCH_ASSOC);

		if (empty ($data[0]["branch"]))
			die ("Unknown branch");

		return $data[0]["branch"];
	}

?>
	</body>
</html>
