<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
	<head>
		<title>phc -- the open source PHP compiler</title>
		<style type="text/css">
			table.layout { width: 100% }
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
		# 2007-12-03 19:02:25 +0000 (Mon, 03 Dec 2007)
		return date ("D, d M Y h:i:s ", $timestamp);
	}

	function get_good_color () { return " style=\"color:green; font-weight: bold\""; }
	function get_bad_color ()	{ return " style=\"color:red; font-weight: bold;\""; }

?>
	</body>
</html>
