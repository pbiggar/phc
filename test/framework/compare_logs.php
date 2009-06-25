<?php


	/*
	 * Usage:
	 *		php test/framework/compare_logs.php test/logs/latest test/logs/Sat_20_Jun_13_13_50/
	 * 
	 * The first argument gets its results first. We ignore results missing in one set or the other.
	 */

	require_once ("lib/header.php");

	define ("FA", "Failure");
	define ("SU", "Success");
	define ("TI", "Timeout");
	define ("SK", "Skipped");



	function readmyfile ($filename)
	{

		$str = "";

		// Read the files with the results
		foreach (array ("failure", "skipped", "success", "timeout") as $ending)
		{
			$str .= file_get_contents ("$filename/$ending");
		}

		// reorder the lines for sorting
		preg_match_all ("/(\S+):\s+(Timeout|Success|Failure|Skipped)\s+(\S+)( - (.*))?/",
			$str,
			$matches,
			PREG_SET_ORDER);

		foreach ($matches as $match)
		{
			$testname = $match[1];
			$success = $match[2];
			$filename = $match[3];
			$reason = isset($match[5]) ? $match[5] : "";
			$result[$testname][$filename] = $success;
		}

		return $result;
	}

	$file0 = readmyfile ($argv[1]);
	$file1 = readmyfile ($argv[2]);


	$new_timeout = 0;	
	$old_timeout = 0;
	$missing = 0;
	foreach ($file0 as $testname => $test)
	{
		foreach ($test as $filename => $result)
		{
			if (isset ($file1[$testname][$filename]))
			{
				$otherresult = $file1[$testname][$filename];
				if ($otherresult != $result)
				{
					if (false
						|| ($result == FA && $otherresult == SU)
						|| ($result == SU && $otherresult == FA)
						|| ($result == SK && $otherresult == FA)
						|| ($result == SK && $otherresult == SU)
						)
					{
						echo "$result != $otherresult for ($testname, $filename)\n";
					}
					else if (false
						|| ($result == TI && $otherresult == SU)
						|| ($result == TI && $otherresult == FA)
						)
					{
						$new_timeout += 1;
					}
					else if (false
						|| ($result == SU && $otherresult == TI)
						|| ($result == FA && $otherresult == TI)
						)
						$old_timeout += 1;
				}
			}
			else
				$missing++;
		}
	}
	echo "Timeouts: (+$new_timeout, -$old_timeout)\n";
	echo "Missing: $missing\n";




?>
