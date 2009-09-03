<?php
/*
*
* Combines results from individual files into the benchmark they are a member of in a combined_results table.
*
* Usage: php test/framework/bench/combine_bench_results.php <path of database>
*
*/

	
	$date = date ("c");


	$DB = new PDO ("sqlite:".$argv[1]);

	$benches = array(
			"test/subjects/benchmarks/zend/individual/", 
			"test/subjects/benchmarks/php-benchmarks/benchcli/tests/",
			"test/subjects/benchmarks/RUBBoS/PHP/",
			"test/subjects/benchmarks/RUBiS/",
			"test/subjects/benchmarks/shootout/",
			"test/subjects/benchmarks/SPEC/bank/",
			"test/subjects/benchmarks/webapps/aphpkb/",
			"test/subjects/benchmarks/webapps/eveactive_1.0/",
			"test/subjects/benchmarks/webapps/phpshell-2.1/",
			"test/subjects/benchmarks/webapps/phpSQLiteAdmin-0.2/",
			"test/subjects/benchmarks/webapps/tigerPhpNewsSystem_1.0_beta_build39/"
			);
	
	$DB->exec ("DROP table combined_results");

	$DB->exec ("
		CREATE table combined_results 
		(date date,
		file varchar(200),
		flags varchar(200),
		test varchar(200),
		num real)
		");

	$DB->exec ("
		CREATE table results_temp
		(date date,
		file varchar(200),
		flags varchar(200),
		test varchar(200),
		strings varchar(200),
		num real)
		");


	$DB->exec ("INSERT INTO results_temp SELECT * FROM results");
	foreach ($benches as $bench)
	{			
		$data = $DB->query ("SELECT * FROM results_temp WHERE file LIKE '$bench%'");

		
		foreach ($data as $d)
		{
			
			$num = 0;
			// Doesn't check date
			$moredata = $DB->query ("SELECT flags,test,num FROM results_temp WHERE file LIKE '$bench%'
											AND flags = '".$d['flags']."'
											AND test = '".$d['test']."'
											");
	
			foreach ($moredata as $md)
			{
				$num += $md['num'];
			}

			$DB->exec ("INSERT INTO combined_results
							VALUES('$date',
									'$bench',
									'".$d['flags']."',
									'".$d['test']."',
									'$num')
									");
		
			$DB->exec ("DELETE FROM results_temp WHERE file LIKE '$bench%'
							AND flags = '".$d['flags']."'
							AND test = '".$d['test']."'
						");


		}
	}	
	$DB->exec ("DROP TABLE results_temp");
