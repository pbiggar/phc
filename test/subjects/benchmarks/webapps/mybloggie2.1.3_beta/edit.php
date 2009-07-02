<?


// Blog Script - File Name : edit.php
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

if (isset($_GET['post_id'])) $post_id = $_GET['post_id'];
if (isset($_GET['page'])) $page = $_GET['page'] ;
if (isset($_SESSION['username'])) $username = $_SESSION['username'];
if (isset($_SESSION['user_id'])) $user_id = $_SESSION['user_id'] ;
if (isset($_POST['category'])) { $cat_id = $_POST['category']; }
elseif (isset($_GET['cat_id'])) { $cat_id = $_GET['cat_id']; } else { $cat_id =""; }

$template->assign_vars(array(
           'FORMHEADER'       => "EDIT POST",
           'ACTIONFILENAME'   =>  $_SERVER['PHP_SELF']."?mode=edit&amp;post_id=".$post_id, ));

if ($level==1){
$sql = "SELECT * FROM ".POST_TBL." WHERE post_id='$post_id'";
} elseif ($level==2)  {
$sql = "SELECT * FROM ".POST_TBL." WHERE post_id='$post_id' and  user_id='$user_id'";
}

$result = $db->sql_query($sql);
if( $db->sql_numrows($result)== 1 ) {
$edit = $db->sql_fetchrow($result);

$timestamp = $edit['timestamp'];
$posttime = date("h:i:s a", $timestamp) ;
$postdate = date("d M Y", $timestamp) ;




$sql= "SELECT ".CAT_TBL.".cat_desc , ".CAT_TBL.".cat_id
FROM ".CAT_TBL."
ORDER BY ".CAT_TBL.".cat_desc ASC";

$result = $db->sql_query($sql) ;
while ($row = $db->sql_fetchrow($result)) {
if ( $row['cat_id'] <> $cat_id ){
$template->assign_block_vars('option', array(
          'DB_CATEGORY'        => $row['cat_desc'],
          'DB_CAT_ID'        => $row['cat_id'],
          ));
   }
    else
   { $template->assign_block_vars('optionselected', array(
          'DB_CATEGORY'        => $row['cat_desc'],
          'DB_CAT_ID'        => $row['cat_id'],
          ));
          }
}

if (isset($_POST["preview"])){

$message = $_POST['message'];
$subject = $_POST['subject'];

if (isset($_POST['edit_date']))  { $edit_date  = $_POST['edit_date']; } else { $edit_date  = 0; }

   $hh  = $_POST['hh'];
   $min = $_POST['min'];
   $ss  = $_POST['sec'];
   $mm  = $_POST['mm'];
   $dd  = $_POST['dd'];
   $yy  = $_POST['yy'];

   $nn  = $mth_text[$mm-1];
   $disp_mth_opt = "";
   for ($i=0; $i<12; $i++ ) {
      if ( $nn != $mth_text[$i] ){
          $disp_mth_opt .="<option value=\"".($i+1)."\">".$mth_text[$i]."</option>";
      }
      else
      {
          $disp_mth_opt .="<option value=\"".($i+1)."\" selected=\"selected\">".$mth_text[$i]."</option>" ;
      }
   }
      $template->assign_block_vars('monthoption', array(
        'MTH_OPTION'  => $disp_mth_opt,
      ));

$sqlcat= "SELECT ".CAT_TBL.".cat_desc
FROM ".CAT_TBL."
WHERE ".CAT_TBL.".cat_id ='".$_POST['category']."'";
$resultcat = $db->sql_query($sqlcat) ;
$rowcat = $db->sql_fetchrow($resultcat);

$cat_desc  = $rowcat['cat_desc'];

  if (isset($message)) {

  if ($htmlsafe=="no") {
    $premessage = trim($message);
    $presubject = trim($subject);  }
  else { 
    $premessage = preg_replace($html_entities_match, $html_entities_replace, $message);
    $presubject = preg_replace($html_entities_match, $html_entities_replace, $subject);
     }

    $datetime1 = time();
if (!get_magic_quotes_gpc()) {
    $presubject = addslashes($presubject);
    $premessage = addslashes($premessage);
}
    $premessage = trim($premessage);
    $premessage=viewbbcode($premessage);
    $premessage=viewsmile($premessage);
    $premessage=viewlink($premessage);
    $premessage=autolink($premessage);
    $premessage = nl2br($premessage);

if ($edit_date) {
$timestamp = mktime($hh, $min, $ss, $mm, $dd, $yy);
$checked = "checked";
}
else {
$timestamp = $edit['timestamp'];
$checked = "";
}


$posttime = date("h:i:s a", $timestamp) ;
$postdate = date("d M Y", $timestamp) ;

$template->assign_block_vars('preview', array(
           'L_PREVIEW'       => $lang['Preview'],
             ));
$template->assign_block_vars('blogparse', array(
          'USER_NAME'        => $username,
          'SUBJECT'          => stripslashes($presubject),
          'MESSAGE'          => stripslashes($premessage),
          'TIME'             => $posttime ,
          'DATE'             => $postdate ,
          'L_COMMENT'        => $lang['Comment'],
          'L_CATEGORY'       => $lang['Category'],
          'L_POSTED_BY'      => $lang['Posted By'],
          'L_TIME'           => $lang['Time'],
          'U_CATEGORY'        => $cat_desc,
          'U_COMMENT'        => $_SERVER['PHP_SELF']."?select=viewcat&amp;post_id=".$row['post_id'],
          'L_TRACKBACK'      => $lang['Trackback'],
              ));
$template->assign_vars(array(
          'SUBJECT'          => trim((stripslashes($subject))),
          'MESSAGE'          => trim((stripslashes($message))),
          'TIME'             => $posttime ,
          'DATE'             => $postdate ,
          'U_CATEGORY'         => $cat_desc,
          'CHECKED'          => $checked,
          'POST_DATE'      =>  $dd,
          'POST_YEAR'      =>  $yy,
          'POST_HOUR'      =>  $hh,
          'POST_MIN'       =>  $min,
          'POST_SEC'       =>  $ss,
          ));

           $template->pparse('blog_body');
           $template->pparse('formsubmit');



    } else {
             error($lang['Error'],$lang['Msg_empty_msg']);
            }

   }
   elseif (isset($_POST["submit"])) {

      $subject = $_POST['subject'];
      $message = $_POST['message'];
      $cat_id = $_POST['category'];
      if (isset($_POST['edit_date']))  { $edit_date  = $_POST['edit_date']; } else { $edit_date  = 0; }

      $hh  = $_POST['hh'];
      $min = $_POST['min'];
      $ss  = $_POST['sec'];
      $mm  = $_POST['mm'];
      $dd  = $_POST['dd'];
      $yy  = $_POST['yy'];

      if (isset($message)) {

      if ($htmlsafe=="no") {
      $subject = trim($subject);
      $message = trim($message);  }

      else
      {
       $message = preg_replace($html_entities_match, $html_entities_replace, $message);
       $subject = preg_replace($html_entities_match, $html_entities_replace, $subject);
      }

      $message = trim($message);
      if (!get_magic_quotes_gpc()) {
      $subject = addslashes($subject);
      $message = addslashes($message);
      }


      if ($edit_date) {
         $timestamp = mktime($hh, $min, $ss, $mm, $dd, $yy);
         //$checked = "checked";
         $sql = "UPDATE ".POST_TBL." SET  subject='$subject', message='$message', timestamp='$timestamp', cat_id='$cat_id' WHERE post_id='$post_id'";

      }
      else {
         $sql = "UPDATE ".POST_TBL." SET  subject='$subject', message='$message', cat_id='$cat_id' WHERE post_id='$post_id'";
         //$checked = "";
      }

      $result = $db->sql_query($sql);

     message($lang['Edit'] , $lang['Msg_posted'] );
     echo "<meta http-equiv=\"Refresh\" content=\"3;url=./admin.php?mode=viewlist\" />";
      }
   }
   else {
     $subject = $edit['subject'];
     $message = $edit['message'];

   $hh  = date("h", $timestamp);
   $min = date("i", $timestamp);
   $ss  = date("s", $timestamp);
   $mm  = date("F", $timestamp);
   $dd  = date("d", $timestamp);
   $yy  = date("Y", $timestamp);

   $nn  = $mm;
   $disp_mth_opt = "";
   for ($i=0; $i<12; $i++ ) {
      if ( $nn != $mth_text[$i] ){
          $disp_mth_opt .="<option value=\"".($i+1)."\">".$mth_text[$i]."</option>";
      }
      else
      {
          $disp_mth_opt .="<option value=\"".($i+1)."\" selected=\"selected\">".$mth_text[$i]."</option>" ;
      }
   }
      $template->assign_block_vars('monthoption', array(
        'MTH_OPTION'  => $disp_mth_opt,
      ));

    $template->assign_vars(array(
          'SUBJECT'          => $subject,
          'MESSAGE'          => trim((stripslashes($message))),
          'TIME'             => $posttime ,
          'DATE'             => $postdate ,
          'U_CATEGORY'        => $row['cat_desc'],
          'POST_DATE'      =>  $dd,
          'POST_YEAR'      =>  $yy,
          'POST_HOUR'      =>  $hh,
          'POST_MIN'       =>  $min,
          'POST_SEC'       =>  $ss,
          ));

    $template->pparse('formsubmit');
    }
//}
 }
 else
 { message($lang['Error'] , $lang['Msg_Del_error1']);  }
?>