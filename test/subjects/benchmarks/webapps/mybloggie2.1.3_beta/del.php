<?php


// Blog Script - File Name : del.php
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
       echo "<meta http-equiv=\"Refresh\" content=\"2;url=".self_url()."/login.php\" />";
     }

if (isset($_GET['post_id'])) $post_id = $_GET['post_id'];
if (isset($_GET['confirm'])) {$confirm = $_GET['confirm'];} else {$confirm = "";}
$user_id= $userid['id'];
if ($confirm=="") {
message($lang['Confirm'], $lang['Msg_Del_error3']." <a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=del&post_id=".$post_id."&confirm=yes\">".$lang['Yes']."</a>");
}
elseif ($confirm=="yes") {

if ($level==1){
$sql = "DELETE FROM ".POST_TBL." WHERE post_id='$post_id'";
$result = $db->sql_query($sql);
$confirm ="";
message($lang['Del'], $lang['Msg_Del']);
echo "<meta http-equiv=\"Refresh\" content=\"3;url=./admin.php?mode=viewlist\" />";
}
elseif ($level==2){
$sql = "SELECT * FROM ".POST_TBL." WHERE post_id='$post_id' and  user_id='$user_id'";
$result = $db->sql_query($sql);
if( $db->sql_numrows($result)== 1 ) {
  $sql = "DELETE FROM ".POST_TBL." WHERE post_id='$post_id' and user_id='$user_id'";
  $result = $db->sql_query($sql);
  $confirm ="";
  message($lang['Del'], $lang['Msg_Del']);
/**
  $redirect = ( !empty($HTTP_POST_VARS['redirect']) ) ? str_replace('&amp;', '&', htmlspecialchars($HTTP_POST_VARS['redirect'])) : '';
  $redirect = str_replace('?', '&', $redirect);
  if (strstr(urldecode($redirect), "\n") || strstr(urldecode($redirect), "\r"))
  {
      error(GENERAL_ERROR, 'Tried to redirect to potentially insecure url.');
  }
// "<meta http-equiv=\"refresh\" content=\"3;url=login.$phpEx?redirect=$redirect\">"
  if (isset($redirect)) {
  if ( $redirect == "
  echo "<meta http-equiv=\"Refresh\" content=\"3;url=./admin.php?mode=viewlist\" />"
  }
  else {
  echo "<meta http-equiv=\"Refresh\" content=\"3;url=./admin.php?mode=viewlist\" />";
  } **/
}
else { message($lang['Error'], $lang['Msg_Del_error1']  );  }
}
}
else message( $lang['Error'],$lang['Msg_Del_error2'] );
?>