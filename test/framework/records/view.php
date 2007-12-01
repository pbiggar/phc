<?php

	$DB = new PDO ("sqlite:results/results.db");

	$revs = $DB->query ("SELECT revision FROM complete ORDER BY revision ASC")->fetchAll(PDO::FETCH_COLUMN);

	var_dump ($revs);

	foreach ($revs as $rev)
	{
		print "$revs\n";
	}

?>
