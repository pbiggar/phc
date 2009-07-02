<?

// Blog Script - File Name : list.php
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

$pageno = ( isset($HTTP_GET_VARS['pageno']) ) ? intval($HTTP_GET_VARS['pageno']) : 0;

$sql = "SELECT COUNT(p.post_id) AS num_posts
FROM " . POST_TBL . " p ";
if ( !($result = $db->sql_query($sql)) )
    { $sql_error = $db->sql_error();  echo $sql_error['message']; }
$numrow= ( $row = $db->sql_fetchrow($result) ) ? intval($row['num_posts']) : 0;

$pagination = pagelink("viewlist", $pageno, $editlimit, $numrow);

$sql = "SELECT ".CAT_TBL.".cat_desc, ".POST_TBL.".cat_id, ".CAT_TBL.".cat_id, ".POST_TBL.".post_id, ".POST_TBL.".subject,".POST_TBL.".message, ".USER_TBL.".user, ".POST_TBL.".timestamp, ".USER_TBL.".id, ".POST_TBL.".user_id FROM ".POST_TBL.", ".USER_TBL.", ".CAT_TBL."
WHERE ".POST_TBL.".user_id=".USER_TBL.".id  AND  ".CAT_TBL.".cat_id=".POST_TBL.".cat_id
Order by  ".POST_TBL.".timestamp DESC, ".POST_TBL.".post_id DESC
LIMIT ".$pageno." , ".$editlimit;

if( !($result = $db->sql_query($sql)) )
   {
    $sql_error = $db->sql_error();
    echo $sql_error['message'];
   }

$result = $db->sql_query($sql) ;
$n = 0;
while ($row = $db->sql_fetchrow($result)) {

/// Query for No of Comments/Trackbacks //
$querycomment  = "SELECT comment_id FROM ".COMMENT_TBL."
WHERE ".COMMENT_TBL.".post_id = '".$row['post_id']."'";

if ( !($commentresult = $db->sql_query($querycomment)) )
    {
    $sql_error = $db->sql_error();
    echo $sql_error['message'];
    }
$nocom = $db->sql_numrows($commentresult) ;

$post_id = $row['post_id'];
$cat_id = $row['cat_id'];
$time = date("h:i:s a", $row['timestamp']) ;
$date = date("d M Y", $row['timestamp']) ;

$template->assign_vars(array(
           'PAGE'        => $pagination, ));


if ( $n % 2 ) { $alt_clr =" class=\"whitebg\""; } else { $alt_clr = " class=\"greybg\""; }

$template->assign_block_vars('listing', array(
          'ALT_CLR'          => $alt_clr,
          'POSTER_NAME'        => $row['user'],
          'SUBJECT'          => "<a class=\"lblock\" href=\"./index.php?mode=viewid&post_id=".$post_id."\">".$row['subject']."</a>",
          'CATEGORY'         => $row['cat_desc'],
          'COMMENTS'          => "<a class=\"block\" href=\"".$_SERVER['PHP_SELF']."?mode=clist&amp;post_id=".$post_id."\">".$nocom."</a>",
          'TIME'             => $time ,
          'DATE'             => $date ,
          'U_EDIT'           => "<a class=\"block\" href=\"".$_SERVER['PHP_SELF']."?mode=edit&cat_id=".$cat_id."&amp;post_id=".$post_id."\">".$lang['Edit']."</a>",
          'U_DELETE'         => "<a class=\"block\" href=\"".$_SERVER['PHP_SELF']."?mode=del&post_id=".$post_id."\">".$lang['Del']."</a>" ,
 )
 );
$n++;
}
$template->pparse('list');
//          'SUBJECT'          => "<a href=\"javascript:void(window.open('./index.php?mode=viewid&post_id=".$post_id."', 'display1', 'left=50,top=50,resizable=yes,scrollbars=yes,width=760,height=450'))\">".$row['subject']."</a>",

?>