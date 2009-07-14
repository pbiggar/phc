<?

// Blog Script - File Name : index.php
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

session_start();
header("Cache-control: private");
//error_reporting  (E_ERROR | E_WARNING | E_PARSE);
set_magic_quotes_runtime(0);     // changes for 2.1.3

$mybloggie_root_path = './';

include_once('./config.php');
include_once('./includes/db.php');
include_once('./includes/template.php');
include_once('./includes/function.php');
include_once('./language/lang_eng.php');
include_once('./includes/special_for_benchmark.php');


$template = new Template('./templates/'.$style.'/') ;

$template->set_filenames(array(
        'blog_header' => 'blog_header.tpl',
        'sidevert'    => 'sidevert.tpl',
        'blog_body'   => 'blog_body.tpl',
        'footer'      => 'footer.tpl',
        'syndication'      => 'syndication.tpl',
        ));

$template->assign_vars(array(
     'CHAR_SET'  => $charset,
     'CONTENT_DIRECTION' => $content_direction,
     'OWNER'             => '<a class="menu" href="http://www.mywebland.com">myBloggie 2.1.3 &copy; 2005</a>',
     'STYLE'             => $style,
     'TIME'              => 'Time [GMT '.$sign.$timezone.'] : '.gmtdate('d M , H:i:s', time(), $timezone ),
     'BLOG_NAME'         => $myblogname,
     'SYNDICATION'       => $lang['Syndication'],
     'RSS_URL'           => self_url()."/rss/rss.php",
     'RSS2_URL'          => self_url()."/rss/rss2.php"  ,
     'BGCOLOR'           => $blogbgcolor,
     'BLOGGIE_PATH'      => $mybloggie_root_path ,
     'PINGBACK_SVR'      => self_url()."/pingserver/pingsvr.php" ,

));

$timestamp = mktime(gmtdate('H', time(), $timezone ), gmtdate('i', time(), $timezone ), gmtdate('s', time(), $timezone ),
                    gmtdate('n', time(), $timezone ), gmtdate('d', time(), $timezone ), gmtdate('Y', time(), $timezone ));

if(isset($_SESSION['username']) && isset($_SESSION['passwd']))
{
   $template->assign_vars(array(
     'ADMIN_MENU'  => '<center><span class="menuitem"><b><a class="std" href="./admin.php">Admin CP</a></b><span></center>',
   ));
}


// Left Right side menu switch

if (!isset($mode)) {  $search = true ; }
if ($right_menu){
$template->assign_block_vars('rightsidemenu', array( ));
}
else {
$template->assign_block_vars('leftsidemenu', array( ));
}

$template->pparse('blog_header');

$search = true ;
if (isset($_GET['mode'])) $mode=$_GET['mode'];

// if sidemenu is set on the right ==>  $right_menu = true; in config.php
if ($right_menu){
if (isset($mode)) {
    switch ($mode) {
    case "viewid":
    include 'view.php';
    $search = false ;
    break;
    case "viewdate" :
    include 'viewmode.php';
    break;
    case "viewmonth":
    include 'viewmode.php';
    break;
    case "delcom":
    include 'delcomment.php';
    $search = false ;
    break;
    case "editcom":
    include 'view.php';
    $search = false ;
    break;
    case "viewcat":
    include 'viewmode.php';
    break;
    case "search":
    include 'search.php';
    break;
    case "viewuser":
    include 'viewuser.php';
    break;
    default: include('./blog.php'); break;
    }
}
if (!isset($mode)) {
    include('./blog.php');
}
$template->pparse('sidevert');
}

// End right sidemenu condition

// Sidemenu menu items. You can change the menu item order here
include('./calendar.php');
include('./spacer.php');
include('./category.php');
include('./spacer.php');
include('./recent.php');
include('./spacer.php');
include('./archives.php');
include('./spacer.php');
include('./user.php');
include('./spacer.php');
if ($search) {
include('./searchform.php');
include('./spacer.php');
}
$template->pparse('syndication');
// End sidemenu menu items

// if sidemenu is set on the left ==>  $right_menu = false; in config.php
if (!$right_menu){

$template->pparse('sidevert');
if (isset($mode)) {
    switch ($mode) {
    case "viewid":
    include 'view.php';
    $search = false ;
    break;
    case "viewdate" :
    include 'viewmode.php';
    break;
    case "viewmonth":
    include 'viewmode.php';
    break;
    case "delcom":
    include 'delcomment.php';
    $search = false ;
    break;
    case "editcom":
    include 'view.php';
    $search = false ;
    break;
    case "viewcat":
    include 'viewmode.php';
    break;
    case "search":
    include 'search.php';
    break;
    case "viewuser":
    include 'viewuser.php';
    break;
}
}
if (!isset($mode)) {
    include('./blog.php');
}
}
// End left sidemenu condition

$template->pparse('footer');

?>
