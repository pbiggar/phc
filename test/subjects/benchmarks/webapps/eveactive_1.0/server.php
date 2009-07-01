<?php

    // MY SQL Connection
    //error_reporting(E_ALL);
    ob_start();
    define('MYSQL_HOST',     'localhost');
    define('MYSQL_USER',     'membertrack');
    define('MYSQL_PASS',     'membertrack');
    define('MYSQL_DATABASE', 'membertrack');

    if(!@mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS)) {
        die();
    }

    if(!mysql_select_db(MYSQL_DATABASE)) {
        die();
    }

        function Check()
	{
		$returnValue = false;
		$pattern = "/^EVE-minibrowser.*\/([0-9]+\.[0-9]+).*$/";
		if (preg_match($pattern, $_SERVER['HTTP_USER_AGENT'], $matchs))
			if ($matchs[1] >= 2.0)
				$returnValue = true;

		if (!$returnValue){
		header("Location: URL");
		}
//	 Access comes from External Browser, redirect to Forums
		return $returnValue;

}


?>