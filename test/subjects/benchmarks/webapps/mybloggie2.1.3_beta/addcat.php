<?

// Blog Script - File Name : addcat.php
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
        'catform' => 'admin/catform.tpl'));

$template->assign_vars(array(
     'FORMHEADER'       => $lang['Add_category'],
     'CAT_HEAD'       => $lang['Cat_head'],
     'L_CAT_NAME'       => $lang['Category'],
     'L_CAT_ID'       => $lang['Cat_id'],
     'L_REENTER_PASS'       => $lang['Reenter_password'],
     ));

$sql = "SELECT cat_id, cat_desc FROM ".CAT_TBL ;
$result = $db->sql_query($sql);
$n=0;
while ($row = $db->sql_fetchrow($result)) {
if ( $n % 2 ) { $alt_clr =" class=\"whitebg\""; } else { $alt_clr = " class=\"greybg\""; }
     $cat_id      = $row['cat_id'];
     $cat_name    =  $row['cat_desc'] ;
$template->assign_block_vars('parsecat', array(
     'ALT_CLR'    => $alt_clr,
     'CAT_ID'     => $cat_id,
     'CAT_NAME'   => $cat_name,
     'CAT_EDIT'   =>   "<a class=\"block\" href=\"".$_SERVER['PHP_SELF']."?mode=editcat&cat_id=".$cat_id."\">".$lang['Edit']."</a>",
     'CAT_DEL'    =>   "<a class=\"block\" href=\"".$_SERVER['PHP_SELF']."?mode=delcat&cat_id=".$cat_id."\">".$lang['Del']."</a>",
     ));
$n++;
}

if (isset($_POST["cat_desc"])) {
 $cat_desc = $_POST["cat_desc"] ;
 $sql = "SELECT cat_desc FROM ".CAT_TBL." WHERE cat_desc='$cat_desc'";
 $result = $db->sql_query($sql);

if( $db->sql_numrows($result)> 0 ) error( $lang['Error'], $lang['Msg_cat_available'] );

if( !isset($cat_desc) || $cat_desc == "" || empty($cat_desc))  {
$error_flag = true;
$errormsg = $errormsg. $lang['Msg_invalid_cat']."<br />" ; }
else { $error_flag = false; }

if ($error_flag) error( $lang['Error'], "$errormsg");

}
if (isset($_POST["cat_desc"])) {  $cat_desc = $_POST['cat_desc']; }

 if (isset($_POST["submit"])) {

     $cat_desc = trim($cat_desc);

      $sql = "INSERT INTO ".CAT_TBL." SET cat_desc='$cat_desc'";
      $result = $db->sql_query($sql);
     message($lang['Msg_add_cat'], $lang['Msg_posted']);
     echo "<meta http-equiv=\"Refresh\" content=\"3;url=./admin.php?mode=addcat\" />";
      }
    else {

    $template->pparse('catform');
    }
?>