<?php


// Blog Script - File Name : delcomment.php
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

if (!isset($_SESSION['username']) && !isset($_SESSION['passwd'])) {
  header( "Location: ./login.php" );
  }

if (isset($HTTP_GET_VARS['comment_id'])) intval($comment_id = $HTTP_GET_VARS['comment_id']);
if (isset($HTTP_GET_VARS['post_id'])) $post_id = intval($HTTP_GET_VARS['post_id']);
if (isset($HTTP_GET_VARS['confirm'])) {$confirm = $HTTP_GET_VARS['confirm']; } else { $confirm = ""; }
  $redirect = ( isset($HTTP_GET_VARS['redirect']) ) ? htmlspecialchars($HTTP_GET_VARS['redirect']) : '';
  //$redirect = str_replace('?', '&', $redirect);
  if  (isset($HTTP_GET_VARS['redirect']))  { $confirmredirect = "&amp;redirect=".$redirect; }

  if (strstr(urldecode($redirect), "\n") || strstr(urldecode($redirect), "\r"))
  {
      error(GENERAL_ERROR, 'Tried to redirect to potentially insecure url.');
  }

if ($confirm=="") {
message($lang['Confirm'], $lang['Msg_Del_error3']." <a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=delcom&amp;post_id=".$post_id."&amp;comment_id=".$comment_id."&amp;confirm=yes".$confirmredirect."\">".$lang['Yes']."</a>");
}
elseif ($confirm=="yes") {

// Data Base Connection  //
$sql = "DELETE FROM ".COMMENT_TBL." WHERE comment_id=$comment_id";
$result = $db->sql_query($sql);
$confirm ="";
message($lang['Del'], $lang['Msg_Del']);

// "<meta http-equiv=\"refresh\" content=\"3;url=login.$phpEx?redirect=$redirect\">"
  if (isset($redirect)) {
  if ( $redirect == "adm" ){
  echo "<meta http-equiv=\"Refresh\" content=\"2;url=".self_url()."/admin.php?mode=clist&post_id=".$post_id."&redirect=adm\" />";
  }
  }
  else {
    echo "<meta http-equiv=\"Refresh\" content=\"3;url=".self_url()."/index.php?mode=viewid&amp;post_id=".$post_id."\" />";
//  echo "<meta http-equiv=\"Refresh\" content=\"2;url=./admin.php?mode=viewlist\" />";
  }


}
else message( $lang['Error'],$lang['Msg_Del_error2'] );
?>