<?php


// Blog Script - File Name : deluser.php
// Copyright (C) myBloggie Sean
// http://www.mywebland.com , http://mybloggie.mywebland.com

// You are requested to retain this copyright notice in order to use
// this software.


//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

if ( !defined('IN_MYBLOGGIE') )
  {
    die("You are not allowed to access this page directly !");
  }

// Added security
if (!isset($_SESSION['username']) && !isset($_SESSION['passwd'])) {
  header( "Location: ./login.php" );
  }
else {
  $username = $_SESSION['username'];
  $result = mysql_query( "SELECT id, user, level FROM ".USER_TBL." WHERE user='$username'" ) or error( mysql_error() );
  $userid = mysql_fetch_array( $result );
  $_SESSION['user_id'] =   $userid['id'];
  $level =   $userid['level'];
}

if ($level==1) {

if (isset($_GET['id'])) $id = $_GET['id'];
if (isset($_GET['confirm'])) {$confirm = $_GET['confirm'];} else {$confirm = "";}

if ($confirm=="") {
message($lang['Confirm'], $lang['Msg_Del_error3']." <a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=deluser&id=".$id."&confirm=yes\">".$lang['Yes']."</a>");
}
elseif ($confirm=="yes")  {
// Data Base Connection  //
$sql = "DELETE FROM ".USER_TBL." WHERE id=$id";
$result = $db->sql_query($sql);

$sql = "DELETE FROM ".POST_TBL." WHERE user_id=$id";
$result = $db->sql_query($sql);

$confirm ="";
message($lang['Del'], $lang['Msg_Del']);
echo "<meta http-equiv=\"Refresh\" content=\"3;url=./admin.php?mode=deluserlist\" />";
}
else { message( $lang['Error'],$lang['Msg_Del_error2'] );}
 }
else
{
echo "<meta http-equiv=\"Refresh\" content=\"1;url=".self_url()."/oops.php\" />";
}
?>