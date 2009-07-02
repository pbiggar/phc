<?
// Blog Script - File Name : user.php
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

$sql= "SELECT DISTINCT ".POST_TBL.".user_id AS u , ".USER_TBL.".user,  COUNT( 'c' ) as z
FROM ".POST_TBL.", ".USER_TBL."
WHERE ".POST_TBL.".user_id = ".USER_TBL.".id AND ".POST_TBL.".timestamp<='".$timestamp."'
GROUP BY u
ORDER BY ".USER_TBL.".user ASC"
;

$result = $db->sql_query($sql) ;

$template->set_filenames(array(
        'user_post' => 'user_post.tpl',
        ));
$template->assign_vars(array(
     'USER_POST'  => $lang['User_List'],
));
while ($user_post = $db->sql_fetchrow($result)) {

   $template->assign_block_vars('user_post', array(
   'MTH'   => $user_post['user'],
   'POSTS'   => $user_post['z'],
   'U_USER'  => "index.php?mode=viewuser&amp;user_id=".$user_post['u'],
    )
    );
    //echo $archive['m']." ".$archive['t']; $_SERVER['PHP_SELF'].
}

$template->pparse('user_post');

?>