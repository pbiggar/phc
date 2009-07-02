<?

// Blog Script - File Name : category.php
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

$sql= "SELECT DISTINCT ".POST_TBL.".cat_id AS c, ".CAT_TBL.".cat_id, ".CAT_TBL.".cat_desc,  COUNT( 'c' ) as z
FROM ".POST_TBL.", ".CAT_TBL."
WHERE ".POST_TBL.".cat_id = ".CAT_TBL.".cat_id AND ".POST_TBL.".timestamp<='".$timestamp."'
GROUP BY c
ORDER BY ".CAT_TBL.".cat_desc ASC"
;

$result = $db->sql_query($sql) ;

$template->set_filenames(array(
        'categories' => 'categories.tpl',
        ));
$template->assign_vars(array(
     'CATEGORIES'  => $lang['Categories'],
));
while ($categories = $db->sql_fetchrow($result)) {

   $template->assign_block_vars('categories', array(
   'MTH'   => $categories['cat_desc'],
   'POSTS'   => $categories['z'],
   'U_ARCHIVE'  => $_SERVER['PHP_SELF']."?mode=viewcat&amp;cat_id=".$categories['cat_id'],
    )
    );
    //echo $archive['m']." ".$archive['t'];
}

$template->pparse('categories');

?>

