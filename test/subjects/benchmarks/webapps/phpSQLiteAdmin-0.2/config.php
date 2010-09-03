<?php

/*config.php*/

$config['root_path'] = "C:/Arquivos de programas/Apache Group/Apache2/htdocs/hp/";

$datetime_format = 'd.m.Y - H:i:s';


// hoster mode stuff

// in your directory structure, at which depth is the users directory
// e.g. for /home/USER/public_html it would be 2
// e.g. for /home/webroot/users/USER/public_html it would be 4
$hm_userdirposition = '2';

// subdirectory in the users homedir that will store his sqlite databases.
// You must create this directory and give it the adequate permissions (Webserver must have write-access)
$hm_dbdir = 'sqlite';


?>