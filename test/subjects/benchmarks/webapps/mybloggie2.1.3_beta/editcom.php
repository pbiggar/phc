<?

// Blog Script - File Name : editcom.php
// Copyright (C) myBloggie 2005 Sean
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

include_once('./includes/s_includes.php');
 include_once('./includes/checks.php');

  if(isset($_SESSION['username']) && isset($_SESSION['passwd']))
  { $guest_comment = true; }
  else
  { $guest_comment = false; }

$pageno = ( isset($HTTP_GET_VARS['pageno']) ) ? intval($HTTP_GET_VARS['pageno']) : 0;

if ($mode=="editcom")
  {
    if (isset($HTTP_GET_VARS['comment_id']))
       { $comment_id = intval($HTTP_GET_VARS['comment_id']); }
    elseif (isset($_POST['comment_id']))
       { $comment_id = intval($_POST['comment_id']); }
    else
    { die("Error , Post no selected"); }
    if (isset($HTTP_GET_VARS['post_id']))
       { $post_id = intval($HTTP_GET_VARS['post_id']); }
    elseif (isset($_POST['post_id']))
       { $post_id = intval($_POST['post_id']); }
    else
    { error('Error', 'invalid Post ID '); }

  $redirect = ( isset($HTTP_GET_VARS['redirect']) ) ? htmlspecialchars($HTTP_GET_VARS['redirect']) : '';
  if  (isset($HTTP_GET_VARS['redirect']))  { $confirmredirect = "&amp;redirect=".$redirect; }
  if (strstr(urldecode($redirect), "\n") || strstr(urldecode($redirect), "\r"))
  {
      error(GENERAL_ERROR, 'Tried to redirect to potentially insecure url.');
  }
  if ( isset($HTTP_GET_VARS['redirect'])) {
  $template->assign_block_vars('redirectswitch', array(
      'REDIRECT'         => "allcom",
   ));
   }
if ( !isset($post_id) || empty($post_id) || $post_id=="") { error('Error', 'invalid Post_ID'); }
check_postid($post_id);
check_commentid($comment_id);

  $sql = $sql = "SELECT * FROM ".COMMENT_TBL." WHERE ".COMMENT_TBL.".comment_id = ".$comment_id;
  $result = $db->sql_query($sql);
   if( $db->sql_numrows($result)== 1 ) {
   $edit = $db->sql_fetchrow($result);
  if (!isset($_POST["submit"]))
  {
         $template->assign_vars(array(
          'COMMENT_ACTION'   => $_SERVER['PHP_SELF']."?mode=editcom&amp;post_id=".$post_id."&amp;comment_id=".$comment_id,
          'COMMENTSUBJECT'   => $edit['comment_subject'],
          'COMMENTTEXT'      => $edit['comments'],
          'COMMENTNAME'      => $edit['poster'],
          'COMMENTEMAIL'     => $edit['email'],
          'COMMENTHOME'     =>  $edit['home'],
   )
   );  }
  }
  }
  $template->set_filenames(array(
      'editcomment'        => 'admin/comment.tpl',
      'commentcode' => 'admin/commentcode.tpl',
  ));

  if (isset($_POST['commentemail'])) {$commentemail = $_POST['commentemail'];} else { $commentemail="" ;}
  $commentemail = trim($commentemail);

  if (isset($_POST["submit"])) {

     $user_ip = $HTTP_SERVER_VARS['REMOTE_ADDR'];  // Changes for 2.1.3  ( moved up )

        // Flood control  --> implented 2.1.3

        $current_time = mktime(gmtdate('H', time(), $timezone ),
                  gmtdate('i', time(), $timezone ),
                  gmtdate('s', time(), $timezone ),
                  gmtdate('n', time(), $timezone ),
                  gmtdate('d', time(), $timezone ),
                  gmtdate('Y', time(), $timezone ));
        $sql = "SELECT MAX(com_tstamp) AS most_recent_time
            FROM ".COMMENT_TBL."
            WHERE ip = '".$user_ip."' AND post_id = '".$post_id."'";

        if ($result = $db->sql_query($sql))
        {
            if ($row = $db->sql_fetchrow($result))
            {
                if (intval($row['most_recent_time']) > 0 && ($current_time - intval($row['most_recent_time'])) < intval($floodcontrol))
                {
                    error($lang['Alert'], $lang['Flood_Control']);
                }
            }
        }

      $commentsubject = $_POST['commentsubject'];
      $commenttext = $_POST['commenttext'];
      $commentname = $_POST['commentname'];
      $commenthome = $_POST['commenthome'];

      if (isset($commenttext) && isset($commentname) ) {

      if ($commenthtmlsafe=="no") {
         $commentname = trim((stripslashes($commentname)));
         $commentsubject = trim((stripslashes($commentsubject)));
         $commenttext = trim((stripslashes($commenttext)));
         $commentemail = trim((stripslashes($commentemail)));
         $commenthome = trim((stripslashes($commenthome)));

        }

     else {
         $commentname = preg_replace($html_entities_match, $html_entities_replace,$commentname); 
         $commentsubject = preg_replace($html_entities_match, $html_entities_replace,$commentsubject); 
         $commenttext = preg_replace($html_entities_match, $html_entities_replace,$commenttext); 
         $commentemail = preg_replace($html_entities_match, $html_entities_replace,$commentemail); 
         $commenthome = preg_replace($html_entities_match, $html_entities_replace,$commenthome); 
        }

     $timestamp = mktime(gmtdate('H', time(), $timezone ),
                  gmtdate('i', time(), $timezone ),
                  gmtdate('s', time(), $timezone ),
                  gmtdate('n', time(), $timezone ),
                  gmtdate('d', time(), $timezone ),
                  gmtdate('Y', time(), $timezone ));

      if (!get_magic_quotes_gpc()) {
      $commentsubject = addslashes($commentsubject);
      $commenttext = addslashes($commenttext);
     }

if ($mode=="editcom")
  {
      $sqledit = "UPDATE ".COMMENT_TBL." SET  comment_subject='$commentsubject', comments='$commenttext',
              poster = '$commentname', email='$commentemail' , home='$commenthome' Where comment_id='$comment_id' ";
      $result = $db->sql_query($sqledit) or die("Cannot query the database.<br>" . mysql_error());
       message($lang['Edit'] , $lang['Msg_posted'] );
   $redirect = ( isset($HTTP_POST_VARS['redirect']) ) ? htmlspecialchars($HTTP_POST_VARS['redirect']) : '';
  if (isset($redirect)) {
  if ( $redirect == "allcom" ){
  echo "<meta http-equiv=\"Refresh\" content=\"2;url=".self_url()."/admin.php?mode=all_com&amp;redirect=allcom\" />";
  }
  else {
      echo "<meta http-equiv=\"Refresh\" content=\"2;url=".$_SERVER['PHP_SELF']."?mode=clist&amp;post_id=".$post_id."\" />";
  }
  }
  }
}}
else {
$template->assign_vars(array(
          'L_POSTED_BY'      => $lang['Posted By'],
          'L_TIME'           => $lang['Time'],
          'L_NAME'           => $lang['Name'],
          'L_COMMENT'        => $lang['Comments'],
          'L_SUBJECT'        => $lang['Subject'],
          'L_EMAIL_ADD'      => $lang['Email_Add'],
          'L_HOME_PAGE'      => $lang['Home_Page'],
          'L_OPTIONAL'       => $lang['Optional'],
          'L_COMMENT_HEADER' => $lang['Comment_Header'],
 )
 );

$template->pparse('commentcode');
// End
$template->pparse('editcomment');
}
?>
