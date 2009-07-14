<?

// Blog Script - File Name : admin.php
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

//error_reporting('E_ALL');
define('IN_MYBLOGGIE', true);

$mybloggie_root_path = './';
set_magic_quotes_runtime(0); 
//$mybloggie_root_path = "./";

include_once('./config.php');
include_once('./includes/db.php');
include_once('./includes/template.php');
include_once('./includes/function.php');
include_once('./language/lang_eng.php');
include_once('./includes/special_for_benchmark.php');

$mth_text[0]  = $lang['January'];
$mth_text[1]  = $lang['February'];
$mth_text[2]  = $lang['March'];
$mth_text[3]  = $lang['April'];
$mth_text[4]  = $lang['May'];
$mth_text[5]  = $lang['June'];
$mth_text[6]  = $lang['July'];
$mth_text[7]  = $lang['August'];
$mth_text[8]  = $lang['September'];
$mth_text[9]  = $lang['October'];
$mth_text[10] = $lang['November'];
$mth_text[11] = $lang['December'];

$template = new Template('./templates/'.$style.'/') ;

//session_start();

if (isset($_GET['mode'])) $mode=$_GET['mode'];  else { $mode=""; }
if (isset($_GET['select'])) { $select=$_GET['select']; } else { $select=""; }
if (isset($_GET['post_id'])) $post_id=intval($_GET['post_id']);

if (!verifyuser() )
  {
  echo "<meta http-equiv=\"Refresh\" content=\"0;url=login.php\" />";
  }
else {
if ($select=='logoff')
{
  if(isset($_SESSION['username']) || isset($_SESSION['passwd'])) {
  unset($_SESSION['username']);
  unset($_SESSION['passwd']); session_destroy();
  header( "Location: ./" );
  }
}

$template->set_filenames(array(
      'adminheader'    => 'admin/admin_header.tpl',
      'code'          => 'admin/code.tpl',
      //'sidevert'      => 'admin/sidevert.tpl',
      'blog_body'     => 'blog_body.tpl',
      'formsubmit'    => 'admin/formsubmit.tpl',
      //'adminmenu'     => 'admin/adminmenu.tpl',
      'admincontent'  => 'admin/admincontent.tpl',
      'list'          => 'admin/list_body.tpl',
      'all_com'       => 'admin/all_com.tpl',
      'comment_list'  => 'admin/comment_list.tpl',
      'footer'        => 'admin/footer.tpl',
      'userlist'      => 'admin/user_list_body.tpl',

));

$template->assign_vars(array(
     'CHAR_SET'          => $charset,
     'CONTENT_DIRECTION' => $content_direction,
     'OWNER'             => '<a class="copyright" href="http://www.mywebland.com">myBloggie 2.1.3 &copy; 2004 2005</a>',
     'STYLE'             => $style,
     'TIME'              => 'Time [GMT '.$sign.$timezone.'] : '.gmtdate('d M , H:i:s', time(), $timezone ),
     'BLOG_NAME'         => "Administration Area",
));

if(isset($_SESSION['username']) && isset($_SESSION['passwd'])) {
  $username = $_SESSION['username'];
  $result = mysql_query( "SELECT id, user, level FROM ".USER_TBL." WHERE user='$username'" ) or error( mysql_error() );
  $userid = mysql_fetch_array( $result );
  $_SESSION['user_id'] =   $userid['id'];
  $level =   $userid['level'];
$template->assign_block_vars('logoff', array(
           'L_LOGOFF'       => "<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?select=logoff\">".$lang['Logoff']."</a>",
             ));
}


if ($level==1) {
$template->assign_vars(array(
     'MENU'             => 'Home',
     'ADMIN_TITLE'      => 'myBloggie - Administration Area',
     'L_USER_LIST'      => $lang['User_listing'],
     'L_CATEGORY'       => $lang['Category'],
     'L_LEVEL'          => $lang['Level'],
     'L_POSTED_BY'      => $lang['Posted By'],
     'L_TIME'           => $lang['Time'],
     'L_DATE'           => $lang['Date'],
     'L_LIST'           => $lang['Listing'],
     'L_NAME'           => $lang['Name'],
     'L_MESSAGE'        => $lang['Message'],
     'L_SUBJECT'        => $lang['Subject'],
     'L_CATEGORY'       => $lang['Category'],
     'L_DEL'            => $lang['Del'],
     'L_EDIT'           => $lang['Edit'],
     'L_COMMENTS'       => $lang['Comments'],
     'L_TRACKBACK_URLS' => $lang['Trackback_urls'],
     'L_DATE_POST'      => $lang['Publish_Date'],
     'L_EDIT_TIMESTAMP' => $lang['Edit_Timestamp'],
     'L_UID'            => $lang['User_id'],
     'USER_NAME'        => $username,
     'ADMINIMAGE'       => "images/adminpanel.jpg",
     'MENU_HOME'        => "<a  href=\"index.php\">Blog Home</a>",
     'MENU_ADD'         => "<a href=\"".$_SERVER['PHP_SELF']."?mode=add\">".$lang['New_post']."</a>",
     'MENU_EDIT'        => "<a href=\"".$_SERVER['PHP_SELF']."?mode=viewlist\">".$lang['Edit']."</a>",
     'MENU_CAT'         => "<a href=\"".$_SERVER['PHP_SELF']."?mode=addcat\">".$lang['Category']."</a>",
//     'MENU_HEADER2'      => $lang['User_Admin'],
     'MENU_USER'       => "<a href=\"".$_SERVER['PHP_SELF']."?mode=adduser\">".$lang['User_Admin']."</a>",
//     'MENU_HEADER3'      => "File Management",
     'MENU_TOOLS'       => "<a href=\"".$_SERVER['PHP_SELF']."?mode=upload\">".$lang['Tools']."</a>",
));
} elseif ($level==2) {
$template->assign_vars(array(
     'MENU'             => 'Home',
     'ADMIN_TITLE'      => "- ". $lang['Admin_area'],
     'L_USER_LIST'      => $lang['User_listing'],
     'L_CATEGORY'       => $lang['Category'],
     'L_LEVEL'          => $lang['Level'],
     'L_POSTED_BY'      => $lang['Posted By'],
     'L_TIME'           => $lang['Time'],
     'L_DATE'           => $lang['Date'],
     'L_LIST'           => $lang['Listing'],
     'L_NAME'           => $lang['Name'],
     'L_MESSAGE'        => $lang['Message'],
     'L_SUBJECT'        => $lang['Subject'],
     'L_CATEGORY'       => $lang['Category'],
      'L_DEL'           => $lang['Del'],
      'L_EDIT'          => $lang['Edit'],
     'L_TRACKBACK_URLS' => $lang['Trackback_urls'],
     'USER_NAME'        => $username,
     'ADMINIMAGE'       => "images/adminpanel.jpg",
//     'MENU_HEADER1'     => "Blog Admin - User",
     'MENU_HOME'        => "<a href=\"index.php\">Blog Home</a>",
     'MENU_ADD'         => "<a href=\"".$_SERVER['PHP_SELF']."?mode=add\">".$lang['New_post']."</a>",
     'MENU_EDIT'        => "<a href=\"".$_SERVER['PHP_SELF']."?mode=viewlist\">".$lang['Edit_Del']."</a>",
//     'MENU_HEADER2'     => $lang['User_Admin'],
//     'MENU_HEADER3'     => "File Management",
));

if ( $enable_user_upload )
$template->assign_vars(array(
     'MENU_HEADER3'      => "File Management",
     'MENU_TOOLS'       => "<a href=\"".$_SERVER['PHP_SELF']."?mode=upload\">".$lang['Tools']."</a>",
));
}

if (isset($mode)) {
     if ($mode =="add") {
     $template->assign_vars(array(
     'CURRENT_ADD'      => " class=\"current\"",
     ));
     }
     elseif ($mode =="viewlist" || $mode =="edit" || $mode =="all_com") {
     $template->assign_vars(array(
     'CURRENT_EDIT'      => " class=\"current\"",
     ));
        if ($mode =="viewlist") {
        $template->assign_block_vars('editsubmenu', array(
        'SUBMENU_1'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=viewlist\" class=\"current\">".$lang['Edit']."</a>",
        'SUBMENU_2'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=all_com\">".$lang['Comments']."</a>",
        ));
        }
        elseif ($mode =="all_com") {
        $template->assign_block_vars('editsubmenu', array(
        'SUBMENU_1'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=viewlist\">".$lang['Edit']."</a>",
        'SUBMENU_2'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=all_com\" class=\"current\">".$lang['Comments']."</a>",
        ));
        }
     }
     elseif ($mode =="adduser" || $mode =="edituserlist" || $mode =="deluserlist" ) {
        $template->assign_vars(array(
        'CURRENT_USER'      => " class=\"current\"",
        ));
        if ($mode =="adduser") {
        $template->assign_block_vars('usersubmenu', array(
        'SUBMENU_1'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=adduser\" class=\"current\">".$lang['Msg_add_user']."</a>",
        'SUBMENU_3'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=deluserlist\">".$lang['Msg_del_user']."</a>",
        'SUBMENU_2'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=edituserlist\">".$lang['Msg_edit_user']."</a>", ));
        }
        elseif ($mode =="deluserlist") {
        $template->assign_block_vars('usersubmenu', array(
        'SUBMENU_1'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=adduser\">".$lang['Msg_add_user']."</a>",
        'SUBMENU_3'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=deluserlist\" class=\"current\">".$lang['Msg_del_user']."</a>",
        'SUBMENU_2'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=edituserlist\">".$lang['Msg_edit_user']."</a>", ));
        }
        elseif ($mode =="edituserlist") {
        $template->assign_block_vars('usersubmenu', array(
        'SUBMENU_1'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=adduser\">".$lang['Msg_add_user']."</a>",
        'SUBMENU_3'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=deluserlist\">".$lang['Msg_del_user']."</a>",
        'SUBMENU_2'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=edituserlist\" class=\"current\">".$lang['Msg_edit_user']."</a>", ));
        }
     }
     elseif ($mode =="addcat" || $mode =="delcat" || $mode =="editcat") {
        $template->assign_vars(array(
        'CURRENT_CAT'      => " class=\"current\"",
        ));
        if ($mode =="upload") {
        $template->assign_block_vars('toolssubmenu', array(
           'SUBMENU_1'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=upload\" class=\"current\">".$lang['Upload']."</a>",
            ));
        }
     }
     elseif ($mode =="tools" || $mode =="upload" ) {
     $template->assign_vars(array(
     'CURRENT_TOOLS'      => " class=\"current\"",
     ));
        if ($mode =="upload") {
        $template->assign_block_vars('toolssubmenu', array(
           'SUBMENU_1'  => "<a href=\"".$_SERVER['PHP_SELF']."?mode=upload\" class=\"current\">".$lang['Upload']."</a>",
            ));
        }
     }


}



$template->pparse('adminheader');
include('./spacer6.php');
//$template->pparse('adminmenu');
//$template->pparse('sidevert');

if (isset($mode)) {
    switch ($mode) {
    case "add":
    $template->pparse('code');
    include 'add.php';
    break;
//    case "set" :
  //  include 'set.php'; // pb - where is this file
    break;
    case "del":
    include 'del.php';
    break;
    case "deluser":
    include 'deluser.php';
    break;
    case "edit":
    $template->pparse('code');
    include 'edit.php';
    break;
    case "edituser":
    include 'edituser.php';
    break;
    case "viewlist":
    include 'post_list.php';
    break;
    case "clist":
    include 'comment_list.php';
    break;
    case "all_com":
    include 'all_com.php';
    break;
    case "editcom":
    $template->pparse('code');
    include 'editcom.php';
    break;
    case "delcat":
    include 'delcat.php';
    break;
    case "addcat":
    include 'addcat.php';
    break;
    case "editcat":
    include 'editcat.php';
    break;
    case "adduser":
    include 'adduser.php';
    break;
    case "edituserlist":
    include 'edituserlist.php';
    break;
    case "deluserlist":
    include 'deluserlist.php';
    break;
    case "upload":
    include 'upload.php';
    break;
    default: $template->pparse('admincontent') ; break;
    }
}
if (!isset($mode)) {
   $template->pparse('admincontent') ;
}

$template->pparse('footer');
}

?>
