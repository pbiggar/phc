<?

// Blog Script - File Name : blog.php
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

$pagination = pagelink("viewlist", $pageno, $bloglimit, $numrow);

$sql = "SELECT ".CAT_TBL.".cat_desc, ".POST_TBL.".cat_id, ".CAT_TBL.".cat_id, ".POST_TBL.".post_id, ".POST_TBL.".subject,".POST_TBL.".message, ".USER_TBL.".user, ".POST_TBL.".timestamp, ".USER_TBL.".id, ".POST_TBL.".user_id FROM ".POST_TBL.", ".USER_TBL.", ".CAT_TBL."
WHERE ".POST_TBL.".user_id=".USER_TBL.".id  AND  ".CAT_TBL.".cat_id=".POST_TBL.".cat_id AND ".POST_TBL.".timestamp<='".$timestamp."'
Order by  ".POST_TBL.".timestamp DESC, ".POST_TBL.".post_id DESC
LIMIT $pageno, $bloglimit ";

if( !($result = $db->sql_query($sql)) )
   {
    $sql_error = $db->sql_error();
    echo $sql_error['message'];
   }

$result = $db->sql_query($sql) ;
while ($row = $db->sql_fetchrow($result)) {

$message=$row['message'];

$message = nl2br($message);
$message=viewsmile($message);
$message=viewlink($message);
$message=autolink($message);
$message=viewbbcode($message);

if ($display_chop_text == "yes" )
{
$message = chop_text($message, 500, 10)."<br />....<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=viewid&amp;post_id=".$row['post_id']."\">Continue</a>";
}

/// Query for No of Comments/Trackbacks //
$querycomment  = "SELECT comment_id FROM ".COMMENT_TBL."
WHERE ".COMMENT_TBL.".post_id = ".$row['post_id']." and comment_type!='trackback'";

if ( !($commentresult = $db->sql_query($querycomment)) )
    {
    $sql_error = $db->sql_error();
    echo $sql_error['message'];
    }
$nocom = $db->sql_numrows($commentresult) ;

$querytb  = "SELECT comment_id FROM ".COMMENT_TBL."
WHERE ".COMMENT_TBL.".post_id = ".$row['post_id']." and comment_type='trackback'";

if ( !($commentresult = $db->sql_query($querytb)) )
    {
    $sql_error = $db->sql_error();
    echo $sql_error['message'];
    }
$notb = $db->sql_numrows($commentresult) ;

//////////////////////////////

$time = date("h:i:s a", $row['timestamp']) ;
$date = date("d M Y", $row['timestamp']) ;

if(isset($_SESSION['username']) && isset($_SESSION['passwd']))
{
$template->assign_block_vars('blogparse', array(

          'USER_NAME'        => $row['user'],
          'SUBJECT'          => $row['subject'],
          'MESSAGE'          => $message,
          'TIME'             => $time ,
          'DATE'             => $date ,
          'L_COMMENT'        => $lang['Comments'],
          // Add trackback //
          'L_TRACKBACK'      => $lang['Trackback'],
          'PERMALINK'        => "<a href=\"".gen_permalink($row['post_id'])."\"><img src=\"templates/".$style."/images/permalink.gif\" border=\"0\" title=\"".$lang['Permalink']."\"></a>" ,
          'U_TRACKBACK'      => $_SERVER['PHP_SELF']."?mode=viewid&amp;post_id=".$row['post_id']."#trackback",
          'TRACKBACK_NO'       => " [".$notb."]",
          /////////////////////////////////////////
          'COMMENT_NO'       => " [".$nocom."]",
          'L_CATEGORY'       => $lang['Category'],
          'U_CATEGORY'       => "<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=viewcat&amp;cat_id=".$row['cat_id']."\">".$row['cat_desc']."</a>",
          'U_COMMENT'        => $_SERVER['PHP_SELF']."?mode=viewid&amp;post_id=".$row['post_id']."#comment",
          'L_POSTED_BY'      => $lang['By'],
          'L_TIME'           => $lang['Time'],
          'ADMIN_MENU'       => "<span class=\"f10pxgrey\">[<a class=\"std\" href=\"admin.php?mode=edit&redirect=index&cat_id=".$row['cat_id']."&amp;post_id=".$row['post_id']."\">".$lang['Edit']."</a>]
                                 [<a class=\"std\" href=\"admin.php?mode=del&redirect=index&post_id=".$row['post_id']."\">".$lang['Del']."</a>]</span>",
 )
 );

 }
 else
 {
    $template->assign_block_vars('blogparse', array(
          'USER_NAME'        => $row['user'],
          'SUBJECT'          => $row['subject'],
          'MESSAGE'          => $message,
          'TIME'             => $time ,
          'DATE'             => $date ,
          'L_COMMENT'        => $lang['Comments'],
          // Add trackback //
          'L_TRACKBACK'      => $lang['Trackback'],
          'PERMALINK'        => "<a href=\"".gen_permalink($row['post_id'])."\"><img src=\"templates/".$style."/images/permalink.gif\" border=\"0\" title=\"".$lang['Permalink']."\"></a>" ,
          'U_TRACKBACK'      => $_SERVER['PHP_SELF']."?mode=viewid&amp;post_id=".$row['post_id']."#trackback",
          'TRACKBACK_NO'       => " [".$notb."]",
          /////////////////////////////////////////
          'COMMENT_NO'       => " [".$nocom."]",
          'L_CATEGORY'       => $lang['Category'],
          'U_CATEGORY'       => "<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=viewcat&amp;cat_id=".$row['cat_id']."\">".$row['cat_desc']."</a>",
          'U_COMMENT'        => $_SERVER['PHP_SELF']."?mode=viewid&amp;post_id=".$row['post_id']."#comment",
          'L_POSTED_BY'      => $lang['By'],
          'L_TIME'           => $lang['Time'],
   ));
   }
}
$template->assign_vars(array(
          'PAGE'        => $pagination,
));

$template->pparse('blog_body');

?>