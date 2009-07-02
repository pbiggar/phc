<?php


// myBloggie 2.1.3 config.php file
// This file is auto generated , Please do not change anything in this file!

$dbms = 'mysql';

$dbhost = 'localhost';
$dbname = '';           // Fill in database name
$dbuser = '';           // Fill in database user name
$dbpasswd = '';         // Fill in database user password

$table_prefix = '';     // Fill in table prefix... different prefix for different blog site

$timezone = '';         // GMT time zone

define('POST_TBL',$table_prefix."posts" );
define('USER_TBL',$table_prefix."user" );
define('CAT_TBL',$table_prefix."category" );
define('COMMENT_TBL',$table_prefix."comment" );

include('setting.php');

?>