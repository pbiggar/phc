<?

// Blog Script - File Name : search.php
// Copyright (C) myBloggie 2.1.1 2004 Sean
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

////////////////////////////////////////////


//////////////////////

if (isset($_GET['select'])) $select=$_GET['select'];
if (isset($_POST['keyword'])) $keyword=$_POST['keyword'];
if (isset($_GET['keyword'])) $keyword=$_GET['keyword'];

if ($searchstriptagsenable!="no") {
$keyword = strip_tags($keyword); }

if ($searchhtmlsafe!="yes") {
//keyword = htmlspecialchars(trim(stripslashes($keyword)));
$keyword = preg_replace($html_entities_match, $html_entities_replace,$keyword);
}

if (!get_magic_quotes_gpc()) {
    $keyword = addslashes($keyword);
}

//Build search logic
$keywords = explode(" ", str_replace(array("+","-","*","~","\"","(",")","<",">","\\"),"",$keyword));
$searchlogic = "";
$nokeywords = count($keywords);
for ($n=0 ; $n < $nokeywords ; $n++ )
{
 $searchlogic =$searchlogic." ( ".POST_TBL.".subject like '%".$keywords[$n]."%' OR ".POST_TBL.".message like '%".$keywords[$n]."%' )" ;
 if ($n+1 != $nokeywords ) { $searchlogic = $searchlogic." AND " ; }
}
//end search logic


$pageno = ( isset($HTTP_GET_VARS['pageno']) ) ? intval($HTTP_GET_VARS['pageno']) : 0;

$sql = "SELECT COUNT(a.post_id) AS num_posts
FROM " . POST_TBL . " a
WHERE a.subject like '%".$keyword."%' OR a.message like '%".$keyword."%'" ;

if ( !($result = $db->sql_query($sql)) )
    { $sql_error = $db->sql_error();  echo $sql_error['message']; }
$numrow= ( $row = $db->sql_fetchrow($result) ) ? intval($row['num_posts']) : 0;

$pagination = pagelink("search&keyword=".$keyword, $pageno, $bloglimit, $numrow);

$sql = "SELECT ".CAT_TBL.".cat_desc, ".POST_TBL.".cat_id, ".CAT_TBL.".cat_id, ".POST_TBL.".post_id, ".POST_TBL.".subject,".POST_TBL.".message, ".USER_TBL.".user, ".POST_TBL.".timestamp, ".USER_TBL.".id, ".POST_TBL.".user_id FROM ".POST_TBL.", ".USER_TBL.", ".CAT_TBL."
WHERE ".POST_TBL.".user_id=".USER_TBL.".id  AND  ".CAT_TBL.".cat_id=".POST_TBL.".cat_id AND  ( $searchlogic )
Order by ".POST_TBL.".post_id DESC
LIMIT $pageno, $bloglimit";
//".POST_TBL.".subject like '%".$keyword."%' OR ".POST_TBL.".message like '%".$keyword."%'

if( !($result = $db->sql_query($sql)) )
   {
    $sql_error = $db->sql_error();
    echo $sql_error['message'];
   }

$result = $db->sql_query($sql) ;

if( $db->sql_numrows($result)==0 ) {
    error($lang['Error'],$lang['Search_Error']." ".$keyword);
    }

$template->assign_block_vars('search', array(
          'KEYWORD'        => $lang['Search_Results']." : <b>".$keyword."</b>",
));

while ($row = $db->sql_fetchrow($result)) {

$message=$row['message'];
$message=viewsmile($message);
$message=viewbbcode($message);
$message=viewlink($message);
$message=autolink($message);
$message = nl2br($message);

//$keywords = explode(" ", str_replace(array("+","-","*","~","\"","(",")","<",">","\\"),"",$keyword));
$message = highlight($message,$keywords);
$subject = highlight($row['subject'],$keywords);

$message = chop_text($message, 500, 10)."<br />....<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=viewid&amp;post_id=".$row['post_id']."\">Continue</a>";

/// Query for No of Comments //
$querycomment  = "SELECT comment_id FROM ".COMMENT_TBL."
WHERE ".COMMENT_TBL.".post_id = ".$row['post_id'];

if ( !($commentresult = $db->sql_query($querycomment)) )
    {
    $sql_error = $db->sql_error();
    echo $sql_error['message'];
    }

$nocom = $db->sql_numrows($commentresult) ;
/////////////////////////////////

$time = date("h:i:s a", $row['timestamp']) ;
$date = date("d M Y", $row['timestamp']) ;

$template->assign_block_vars('blogparse', array(

          'USER_NAME'        => $row['user'],
          'SUBJECT'          => $subject,
          'MESSAGE'          => $message,
          'TIME'             => $time ,
          'DATE'             => $date ,
          'L_COMMENT'        => $lang['Comments'],
          // Add no of comment -- need to change Blog_body.tpl as well //
          'COMMENT_NO'       => " [".$nocom."]",
          /////////////////////////////////////////
          'L_CATEGORY'       => $lang['Category'],
          //'CATEGORY'         => $row['cat_desc'],
          'U_CATEGORY'       => "<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=viewcat&amp;cat_id=".$row['cat_id']."\">".$row['cat_desc']."</a>",
          'U_COMMENT'        => $_SERVER['PHP_SELF']."?mode=viewid&amp;post_id=".$row['post_id'],
          'L_POSTED_BY'      => $lang['Posted By'],
          'L_TIME'           => $lang['Time'],

 )
 );
}
$template->assign_vars(array(
          'PAGE'        => $pagination,
));

$template->pparse('blog_body');
?>