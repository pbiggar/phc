<?

// Blog Script - File Name : adduser.php
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

$template->set_filenames(array(
        'userform' => 'admin/userform.tpl'));

$template->assign_vars(array(
     'FORMHEADER'       => "ADD USER",
     'L_LEVEL'       => $lang['Level'],
     'L_PASSWORD'       => $lang['Password'],
     'L_REENTER_PASS'       => $lang['Reenter_password'],
     ));
$template->assign_block_vars('pass', array(
     'L_PASSWORD'       => $lang['Password'],
     'L_REENTER_PASS'   => $lang['Reenter_password'],
     ));

if (isset($_POST["user"])) {
     $repassword = $_POST['repassword'];
     $user = $_POST['user'];
     $password = $_POST['password'];
     $level = $_POST['level'];

 $sql = "SELECT user FROM ".USER_TBL." WHERE user='$user'";
 $result = $db->sql_query($sql);
 if( $db->sql_numrows($result)> 0 ) error( $lang['Error'], $lang['Msg_user_available'] );

if ($repassword!=$password) {
$error_flag = true;
$errormsg = $lang['Msg_pwd_notmatch']."<br />";  }
if ( !isset($user) or $user=="") {
$error_flag = true;
$errormsg =$errormsg." ".$lang['Msg_req_name']."<br />" ; }
if( $password == "" || $repassword == "" || empty($password) ||  !isset($password))  {
$error_flag = true;
$errormsg = $errormsg." ".$lang['Msg_2x_pwd']."<br />" ; }
if (!isset($error_flag)) $error_flag = false;
if ($error_flag) error( $lang['Error'], "$errormsg");

}

 if (isset($_POST["submit"])) {

      $user = trim($user);
      $password = md5(trim($password));
      $level = trim($level);

      $sql = "INSERT INTO ".USER_TBL." SET user='$user', password='$password', level='$level'";
      $result = $db->sql_query($sql);
     message($lang['Msg_add_user'], ".........".$lang['Msg_posted']);
     echo "<meta http-equiv=\"Refresh\" content=\"3;url=./admin.php?mode=adduser\" />";
      }
    else {

    $template->pparse('userform');
    }
?>