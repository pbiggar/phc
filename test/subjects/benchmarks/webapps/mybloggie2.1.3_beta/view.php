<?

// Blog Script - File Name : view.php
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

include_once('./includes/s_includes.php');
include_once('./includes/checks.php');

$enc = new cls_encrypt;

  if(isset($_SESSION['username']) && isset($_SESSION['passwd']))
  { $guest_comment = true; }
  else
  { $guest_comment = false; }

$pageno = ( isset($HTTP_GET_VARS['pageno']) ) ? intval($HTTP_GET_VARS['pageno']) : 0;

if ($mode=="viewid")
  { if (isset($HTTP_GET_VARS['post_id']))
      { $post_id = intval($HTTP_GET_VARS['post_id']); }
    elseif (isset($_POST['post_id']))
       { $post_id = intval($_POST['post_id']); }
    else
    { die("Error , Post no selected"); }
   $template->assign_vars(array(
      'COMMENT_ACTION'   => $_SERVER['PHP_SELF']."?mode=viewid&amp;post_id=".$post_id,
     )
     );
   }

if ($mode=="editcom")
  {
  if (!isset($_SESSION['username']) && !isset($_SESSION['passwd'])) {
       echo "<meta http-equiv=\"Refresh\" content=\"2;url=".self_url()."/login.php\" />";
     }
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
      'view'        => 'view.tpl',
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

      // If not admin check for security code

      if (!isset($_SESSION['username']) || !isset($_SESSION['passwd']))
      {
        if (isset($_POST['hidden_code'])) { $hidden_code = $_POST['hidden_code']; }
        if (isset($_POST['check_code'])) { $check_code = $_POST['check_code']; }
        $check_code = $enc->html_encrypt($check_code);
        if ($enc->html_decrypt($check_code) == $enc->html_decrypt($hidden_code) )
        {  $guest_comment = true;
            unset($check_code);
            unset($hidden_code);
        }
        else
        {
          error($lang['Error'],$lang['Msg_scode_notmatch']);
        }
       }
      // End security check



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

if ($mode=="viewid" && $guest_comment )
  {
      $sqladd = "INSERT INTO ".COMMENT_TBL." SET post_id='$post_id', comment_subject='$commentsubject', comments='$commenttext', com_tstamp='$timestamp' ,
              poster = '$commentname', email='$commentemail' , home='$commenthome', ip='$user_ip'";
      $result = $db->sql_query($sqladd) or die("Cannot query the database.<br>" . mysql_error());

       if ($emailnotification) {

            $time = date("h:i:s a", $timestamp);
            $date = date("d M Y", $timestamp);

            $body  = "Comment Post Notification\n\n";
            $body .= "Date : ".$date."\n" ;
            $body .= "Time : ".$time."\n\n" ;
            $body .= "Posted by : ".$commentname." IP : ".$user_ip."\n";
            $body .= "Subject : ".$commentsubject."\n\n";
            $body .= "=================================================\n\n";
            $body .= $commenttext."\n\n";
            $body .= "=================================================\n\n";
            sendmail( $sender_email, $receive_email, "Comment Posting Notification", $body );
      }
   }
elseif ($mode=="editcom")
  {
      $sqledit = "UPDATE ".COMMENT_TBL." SET  comment_subject='$commentsubject', comments='$commenttext',
              poster = '$commentname', email='$commentemail' , home='$commenthome' Where comment_id='$comment_id' ";
      $result = $db->sql_query($sqledit) or die("Cannot query the database.<br>" . mysql_error());
  }
     }
}

  $sql = "SELECT ".CAT_TBL.".cat_desc, ".POST_TBL.".cat_id, ".CAT_TBL.".cat_id, ".POST_TBL.".post_id, ".POST_TBL.".subject,".POST_TBL.".message, ".USER_TBL.".user, ".POST_TBL.".timestamp, ".USER_TBL.".id, ".POST_TBL.".user_id FROM ".POST_TBL.", ".USER_TBL.", ".CAT_TBL."
  WHERE ".POST_TBL.".user_id=".USER_TBL.".id  AND  ".CAT_TBL.".cat_id=".POST_TBL.".cat_id AND ".POST_TBL.".post_id = ".$post_id. "
  Order by ".POST_TBL.".post_id DESC ";

if( !($result = $db->sql_query($sql)) )
   {
    $sql_error = $db->sql_error();
    die($sql_error['message']);;
   }

$row = $db->sql_fetchrow($result) ;

$message=$row['message'];
$message=viewsmile($message);
$message=viewbbcode($message);
$message=viewlink($message);
$message=autolink($message);
$message = nl2br($message);

/// Query for No of Comments/Trackbacks //
$querycomment  = "SELECT comment_id FROM ".COMMENT_TBL."
WHERE ".COMMENT_TBL.".post_id = ".$row['post_id']." and comment_type!='trackback'";

if ( !($commentresult = $db->sql_query($querycomment)) )
    {
    $sql_error = $db->sql_error();
    die($sql_error['message']);;
    }
$nocom = $db->sql_numrows($commentresult) ;

$querytb  = "SELECT comment_id FROM ".COMMENT_TBL."
WHERE ".COMMENT_TBL.".post_id = ".$row['post_id']." and comment_type='trackback'";

if ( !($commentresult = $db->sql_query($querytb)) )
    {
    $sql_error = $db->sql_error();
    die($sql_error['message']);;
    }
$notb = $db->sql_numrows($commentresult) ;

/////////////////////////////////


$time = date("h:i:s a", $row['timestamp']) ;
$date = date("d M Y", $row['timestamp']) ;

$template->assign_vars(array(
          'MENU'             => 'Home',
          'USER_NAME'        => $row['user'],
          'SUBJECT'          => $row['subject'],
          'MESSAGE'          => $message,
          'TIME'             => $time ,
          'DATE'             => $date ,
          'CATEGORY'         => $row['cat_desc'],
          'POST_ID'          => $post_id,
          // Add no of comment -- need to change Blog_body.tpl as well //
          'COMMENT_NO'       => " [".$nocom."]",
          /////////////////////////////////////////
          'U_CATEGORY'       => $_SERVER['PHP_SELF']."?mode=viewcat&amp;cat_id=".$row['cat_id'],
          'U_COMMENT'        => $_SERVER['PHP_SELF']."?mode=viewid&amp;post_id=".$row['post_id'],

          'L_POSTED_BY'      => $lang['Posted By'],
          'L_TIME'           => $lang['Time'],
          'L_NAME'           => $lang['Name'],
          'L_COMMENT'        => $lang['Comments'],
          /// Add in Trackback
          'L_TRACKBACK'      => $lang['Trackback'],
          'L_TB_URL_DESC'    => $lang['Tb_url_desc'],
          'TRACKBACK_URL'    => self_url()."/trackback.php/".$post_id,
          'TB_RDF'           => tb_rdf($post_id,$row['subject']),
          'PERMALINK'        => "<a href=\"".gen_permalink($post_id)."\"><img src=\"templates/".$style."/images/permalink.gif\" border=\"0\" title=\"".$lang['Permalink']."\"></a>" ,
          'TRACKBACK_NO'     => " [".$notb."]",
          'U_TRACKBACK'      => $_SERVER['PHP_SELF']."?mode=viewid&amp;post_id=".$row['post_id'],
          /// End Trackback

          'L_CATEGORY'       => $lang['Category'],
          'L_SUBJECT'        => $lang['Subject'],
          'L_EMAIL_ADD'      => $lang['Email_Add'],
          'L_HOME_PAGE'      => $lang['Home_Page'],
          'L_OPTIONAL'       => $lang['Optional'],
          'L_COMMENT_HEADER' => $lang['Comment_Header'],
 )
 );

 /////////// Add in track back ...
$sql = "SELECT * FROM ".COMMENT_TBL."
WHERE ".COMMENT_TBL.".post_id = ".$post_id. " AND ".COMMENT_TBL.".comment_type = 'trackback'
Order by ".COMMENT_TBL.".com_tstamp ASC ";

if( !($result = $db->sql_query($sql)) )
   {
    $sql_error = $db->sql_error();
    die($sql_error['message']);;
   }

$result = $db->sql_query($sql) ;

while ($row = $db->sql_fetchrow($result)){
      if (!(preg_match("#^http\\:\\/\\/#i", $row['home']))) {
      $commenthome1 = "http://".$row['home'] ;
      }
      else
      {       $commenthome1 = $row['home'] ;            }
if (!empty($row['email'])) { $com_email =" <a class=\"std\" href=\"mailto:".$row['email']."\">".$lang['Email']."</a> : "; } else { $com_email = " | ";}
if (!empty($row['home']))  { $com_home = $lang['Track_from']." <a class=\"std\"  href=\"".$commenthome1."\">".$row['poster']."</a>"; } else { $com_home = "";}
$comments  =  $row['comments'] ;
$comment_id = $row['comment_id'] ;
$comments=viewsmile($comments);
$comments=viewbbcode($comments);
$comments=viewlink($comments);
$comments=autolink($comments);
$comments = nl2br($comments);

$time = date("h:i:s a", $row['com_tstamp']) ;
$date = date("d M Y", $row['com_tstamp']) ;

$template->assign_block_vars('trackback', array(

  'COM_TIME'         => $date." ".$time,
  'POSTER'           => $row['poster'],
  'L_BY'             => $lang['By'],
  'L_TIME'           => $lang['Time'],
  'COM_EMAIL'        => $com_email,
  'COM_HOME'         =>  $com_home,
  'COMMENTS'         => $comments,
  'COM_SUBJECT'      => $row['comment_subject'],
));
  if(isset($_SESSION['username']) && isset($_SESSION['passwd']))
  {
    $template->assign_block_vars('trackback.admin', array(
      'ADMIN'         => "[<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=editcom&amp;post_id=".$post_id."&amp;comment_id=".$comment_id."\">".$lang['Edit']."</a>] [<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=delcom&amp;comment_id=".$comment_id."\">".$lang['Del']."</a>]",
   ));
   }
  }
 /////////// End Add in track back ...

$sql = "SELECT * FROM ".COMMENT_TBL."
WHERE ".COMMENT_TBL.".post_id = ".$post_id. " AND ".COMMENT_TBL.".comment_type <> 'trackback'
Order by ".COMMENT_TBL.".com_tstamp ASC ";

if( !($result = $db->sql_query($sql)) )
   {
    $sql_error = $db->sql_error();
    die($sql_error['message']);;
   }

$result = $db->sql_query($sql) ;

while ($row = $db->sql_fetchrow($result)){
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

$template->assign_block_vars('comment', array(

  'COM_TIME'         => $date." ".$time,
  'POSTER'           => $row['poster'],
  'L_BY'             => $lang['By'],
  'L_TIME'           => $lang['Time'],
  'COM_EMAIL'        => $com_email,
  'COM_HOME'        =>  $com_home,
  'COMMENTS'         => $comments,
  'COM_SUBJECT'      => $row['comment_subject'],
));
  if (isset($_SESSION['username']) && isset($_SESSION['passwd']))
  {
    $template->assign_block_vars('comment.admin', array(
      'ADMIN'         => "[<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=editcom&amp;post_id=".$post_id."&amp;comment_id=".$comment_id."\">".$lang['Edit']."</a>] [<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=delcom&amp;post_id=".$post_id."&amp;comment_id=".$comment_id."\">".$lang['Del']."</a>]",
   ));
   }
}

//Security Code  -- Only  applicable to guest commenting only
  if (!isset($_SESSION['username']) || !isset($_SESSION['passwd']))
   {

    $show_code ="";
    $imagecode ="";
    $chars = "ABCDEFGHJKMNPRSTUVWXYZ23456789";
    $len   = strlen($chars)-1;

    for($i=0;$i<5;$i++)
     {
       $randomcode = substr($chars,rand(0,$len),1);
       $show_code .= $randomcode;
       // And we encrypt it
       $randomcode = $enc->html_encrypt($randomcode);
       $imagecode .= "<img src=\"scode.php?code=".$randomcode."\" alt=\"\" title=\"\" />";
     }

     $show_code = $enc->html_encrypt($show_code);

     $security_code = "<table background=\"./templates/".$style."/images/dot.png\"><tr><td>".$imagecode."</td></tr></table>";

     $template->assign_block_vars('scodeswitch', array(
          'SHOW_IMAGE_CODE'  => $security_code,
          'SHOW_CODE'        => $show_code,
          'SECURITY_CODE'    => $lang['Security_Code'],
          'SECURITY_PROMPT'  => $lang['Security_Prompt'],
           ));
     }
/// End Security Code

$template->pparse('commentcode');
// End
$template->pparse('view');

?>
