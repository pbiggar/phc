<?

// Blog Script - File Name : oops.php ( introduce
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

//session_start();
error_reporting  (E_ERROR | E_WARNING | E_PARSE);
set_magic_quotes_runtime(0);

$mybloggie_root_path = './';

include_once('./config.php');
include_once('./includes/db.php');
include_once('./includes/template.php');
include_once('./includes/function.php');
include_once('./language/lang_eng.php');

$template = new Template('./templates/'.$style.'/') ;

$template->set_filenames(array(
        'oops' => 'oops.tpl',
         ));

$template->assign_vars(array(
     'CHAR_SET'  => $charset,
     'CONTENT_DIRECTION' => $content_direction,
     'OWNER'             => '<a class="menu" href="http://www.mywebland.com">myBloggie 2.1.3 &copy; 2005</a>',
     'STYLE'             => $style,
     'TIME'              => 'Time [GMT '.$sign.$timezone.'] : '.gmtdate('d M , H:i:s', time(), $timezone ),
     'BLOG_NAME'         => $myblogname,
     'ERROR_MSG'         => $lang['error_hack'],
     'BGCOLOR'           => $blogbgcolor,
     'BLOGGIE_PATH'      => $mybloggie_root_path ,
//     'PINGBACK_SVR'      => self_url()."/pingserver/pingsvr.php" ,

));

// Left Right side menu switch

$template->pparse('oops');

?>
