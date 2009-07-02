<?php
/***************************************************************************
 *                                 db.php
 *                            -------------------
 *   begin                : Saturday, Feb 13, 2001
 *   copyright            : (C) 2001 The phpBB Group
 *   email                : support@phpbb.com
 *
 *   $Id: db.php,v 1.10 2002/03/18 13:35:22 psotfx Exp $
 *
 *
 ***************************************************************************/

/***************************************************************************
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 ***************************************************************************/

if ( !defined('IN_MYBLOGGIE') )
{
    die("You are not authorized to access this file");
}

include('../includes/mysql.php');


// Make the database connection.
$db = new sql_db($dbhost, $dbuser, $dbpasswd, $dbname, false);
if(!$db->db_connect_id)
{
   echo "<center><b>myBloggie ...Connect to DataBase</center></b>";
   echo "<center><b>Fatal Error!</b>... Could not connect to the database, Please check your configuration file.</center>";
   exit;
}

?>
