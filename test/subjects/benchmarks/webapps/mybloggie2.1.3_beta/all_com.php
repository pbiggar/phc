<?

// Blog Script - File Name : all_com.php
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

    if (!isset($_SESSION['username']) && !isset($_SESSION['passwd'])) {
       echo "<meta http-equiv=\"Refresh\" content=\"2;url=".self_url()."/login.php\" />";
     }

$pageno = ( isset($HTTP_GET_VARS['pageno']) ) ? intval($HTTP_GET_VARS['pageno']) : 0;
/**
if (isset($HTTP_GET_VARS['post_id']))
   { $post_id = intval($HTTP_GET_VARS['post_id']); }
elseif (isset($_POST['post_id']))
   { $post_id = intval($_POST['post_id']); }
else
   { error('Error', 'invalid Post ID '); }    **/

$sql = "SELECT COUNT(p.comment_id) AS num_comments
FROM " . COMMENT_TBL . " p ";
if ( !($result = $db->sql_query($sql)) )
    { $sql_error = $db->sql_error();  echo $sql_error['message']; }
$numrow= ( $row = $db->sql_fetchrow($result) ) ? intval($row['num_comments']) : 0;


//$nocom = ( $db->sql_numrows($result) ) ? intval( $db->sql_numrows($result)) : 0;

$pagination = pagelink("all_com", $pageno, $editlimit, $numrow);

$template->assign_vars(array(
           'PAGE'        => $pagination, ));

$sql = "SELECT * FROM ".COMMENT_TBL."
Order by ".COMMENT_TBL.".com_tstamp ASC, ".COMMENT_TBL.".comment_type ASC
LIMIT ".$pageno." , ".$editlimit;

if ( !($result = $db->sql_query($sql)) )
    {
    $sql_error = $db->sql_error();
    echo $sql_error['message'];
    }
if( !($result = $db->sql_query($sql)) )
   {
    $sql_error = $db->sql_error();
    die($sql_error['message']);;
   }

//$result = $db->sql_query($sql) ;

while ($row = $db->sql_fetchrow($result)){

//if ( $n % 2 ) { $alt_clr =" class=\"whitebg\""; } else { $alt_clr = " class=\"greybg\""; }

      if (!(preg_match("#^http\\:\\/\\/#i", $row['home']))) {
      $commenthome1 = "http://".$row['home'] ;
      }
      else
      {       $commenthome1 = $row['home'] ;            }
if (!empty($row['email'])) { $com_email =" : <a class=\"std\" href=\"mailto:".$row['email']."\">".$lang['Email']."</a> : "; } else { $com_email = " : ";}
if (!empty($row['home']))  { $com_home ="<a class=\"std\"  href=\"".$commenthome1."\">".$lang['Home']."</a>"; } else { $com_home = "";}
$comments  =  $row['comments'] ;
$comment_id = $row['comment_id'] ;
$comments=viewsmile($comments);
$comments=viewbbcode($comments);
$comments=viewlink($comments);
$comments=autolink($comments);
//  end
$comments = nl2br($comments);

$time = date("h:i:s a", $row['com_tstamp']) ;
$date = date("d M Y", $row['com_tstamp']) ;

$template->assign_block_vars('listing', array(

  'COM_TIME'         => $date." ".$time,
  'POSTER'           => $row['poster'],
  'L_BY'             => $lang['By'],
  'L_TIME'           => $lang['Time'],
  'L_COMMENTS'       => $lang['Comments'] ,
  'COM_EMAIL'        => $com_email,
  'COM_HOME'         => $com_home,
  'COMMENTS'         => $comments,
  'COM_SUBJECT'      => $row['comment_subject'],
));
  if (isset($_SESSION['username']) && isset($_SESSION['passwd']))
  {
    $template->assign_block_vars('listing.admin', array(
      'ADMIN'         => "[<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=editcom&amp;post_id=".$row['post_id']."&amp;redirect=allcom&amp;comment_id=".$comment_id."\">".$lang['Edit']."</a>] [<a class=\"std\" href=\"index.php?mode=delcom&amp;post_id=".$row['post_id']."&amp;redirect=adm&amp;comment_id=".$comment_id."\">".$lang['Del']."</a>]",
   ));
   }
}

//<a href="javascript:void(window.open('http://localhost/info.php', 'display1', 'left=50,top=50,resizable=yes,scrollbars=yes,width=400,height=220'))">Some limitations apply.</a>
$template->pparse('all_com');

?>