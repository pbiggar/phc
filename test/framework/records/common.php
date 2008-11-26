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

	function date_from_timestamp ($timestamp)
	{
		return date ("D, d M Y H:i:s ", $timestamp);
	}

	function get_good_color () { return " style=\"color:green; font-weight: bold\""; }
	function get_bad_color ()	{ return " style=\"color:red; font-weight: bold;\""; }

	// TODO coppied from lib/header.php. Avoid duplication
	/* Prints diffs if the xdiff extension is available, and simple outputs both
	 * strings otherwise. 
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

	function get_prev_revision ($rev)
	{
		global $DB;
		$branch = get_branch ($rev);
		$data = $DB->query ("
				SELECT	revision
				FROM		complete
				WHERE		revision < $rev
				AND		branch == '$branch'
				")->fetchAll(PDO::FETCH_ASSOC);

		rsort ($data);

		if ($data === false)
			return 0;

		return $data[0]["revision"];


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
			die ("bad old data");

		return $data[0]["branch"];
	}







?>
	</body>
</html>
