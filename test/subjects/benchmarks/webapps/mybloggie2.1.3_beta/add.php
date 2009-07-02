<?

// Blog Script - File Name : add.php
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

include_once('./includes/trackback.inc.php');
include_once('./includes/tb.class.php');

if (isset($_GET['post_id'])) $post_id = intval($_GET['post_id']);
if (isset($_GET['page'])) $page = intval($_GET['page']) ;
if (isset($_SESSION['username'])) $username = $_SESSION['username'];
if (isset($_SESSION['user_id'])) $user_id = $_SESSION['user_id'] ;
if (isset($_POST['category'])) { $cat_id = $_POST['category']; } else { $cat_id =""; }


$template->assign_vars(array(
     'FORMHEADER'       => $lang['New_post'],
     ));

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

//if ($edit_date)
//{
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
//}

if (isset($_POST["trackback_url"])) {$trackback_url = $_POST['trackback_url']; }

$sqlcat= "SELECT ".CAT_TBL.".cat_desc
FROM ".CAT_TBL."
WHERE ".CAT_TBL.".cat_id ='".$_POST['category']."'";
$resultcat = $db->sql_query($sqlcat) ;
$rowcat = $db->sql_fetchrow($resultcat);

$category  = $rowcat['cat_desc'];

  if (isset($message)) {

if ($htmlsafe=="no") {
    $premessage = trim($message);
    $presubject = trim($subject);   }

else {
    $premessage = preg_replace($html_entities_match, $html_entities_replace, $message);
    $presubject = preg_replace($html_entities_match, $html_entities_replace, $subject);
    }

/**
$datetime1 =  mktime(gmtdate('H', time(), $timezone ),
                     gmtdate('i', time(), $timezone ),
                     gmtdate('s', time(), $timezone ),
                     gmtdate('n', time(), $timezone ),
                     gmtdate('d', time(), $timezone ),
                     gmtdate('Y', time(), $timezone ));   **/

if (!get_magic_quotes_gpc()) {
    $presubject = addslashes($presubject);
    $premessage = addslashes($premessage);
}

    $premessage = viewbbcode($premessage);
    $premessage = viewlink($premessage);
    $premessage = autolink($premessage);
    $premessage = viewsmile($premessage);
    $premessage = nl2br($premessage);

if ($edit_date) {
$timestamp = mktime($hh, $min, $ss, $mm, $dd, $yy);
$checked = "checked";
}
else {
$timestamp = mktime(gmtdate('H', time(), $timezone ),
                    gmtdate('i', time(), $timezone ),
                    gmtdate('s', time(), $timezone ),
                    gmtdate('n', time(), $timezone ),
                    gmtdate('d', time(), $timezone ),
                    gmtdate('Y', time(), $timezone ));
$checked = "";
}


$posttime = date("h:i:s a", $timestamp) ;
$postdate = date("d M Y", $timestamp) ;

$template->assign_block_vars('preview', array('L_PREVIEW'       => $lang['Preview'], ));
$template->assign_block_vars('blogparse', array(
          'USER_NAME'        => $username,
          'SUBJECT'          => stripslashes($presubject),
          'MESSAGE'          => stripslashes($premessage),
          'TIME'             => $posttime ,
          'DATE'             => $postdate ,
          'L_COMMENT'        => $lang['Comments'],
          'L_CATEGORY'       => $lang['Category'],
          'L_POSTED_BY'      => $lang['Posted By'],
          'L_TIME'           => $lang['Time'],
          'U_CATEGORY'        => $category,
          'U_COMMENT'        => $_SERVER['PHP_SELF']."?select=viewcat&amp;post_id=".$row['post_id'],
          'L_TRACKBACK'      => $lang['Trackback'],

              ));

$template->assign_vars(array(

          'SUBJECT'          => trim((stripslashes(preg_replace($html_entities_match, $html_entities_replace, $subject)))),
          'MESSAGE'          => trim((stripslashes(preg_replace($html_entities_match, $html_entities_replace, $message)))),
          'TIME'             => $posttime ,
          'DATE'             => $postdate ,
          'U_CATEGORY'       => $category,
          'DATE'             => $postdate,
          'CHECKED'          => $checked,
          'POST_DATE'      =>  $dd,
          'POST_YEAR'      =>  $yy,
          'POST_HOUR'      =>  $hh,
          'POST_MIN'       =>  $min,
          'POST_SEC'       =>  $ss,

        ));

$template->assign_block_vars('showtrackback', array(
          'TRACKBACK_URL'    => $trackback_url ,
           'L_TRACKBACK_URLS' => $lang['Trackback_urls'],
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

      if (isset($_POST["trackback_url"])) {$trackback_url = $_POST['trackback_url']; }

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

      if ($edit_date) {
         $timestamp = mktime($hh, $min, $ss, $mm, $dd, $yy);
         $checked = "checked";
      }
      else {
         $timestamp = mktime(gmtdate('H', time(), $timezone ),
                      gmtdate('i', time(), $timezone ),
                      gmtdate('s', time(), $timezone ),
                      gmtdate('n', time(), $timezone ),
                      gmtdate('d', time(), $timezone ),
                      gmtdate('Y', time(), $timezone ));
         $checked = "";
      }

      /**
      $timestamp = mktime(gmtdate('H', time(), $timezone ),
                  gmtdate('i', time(), $timezone ),
                  gmtdate('s', time(), $timezone ),
                  gmtdate('n', time(), $timezone ),
                  gmtdate('d', time(), $timezone ),
                  gmtdate('Y', time(), $timezone ));  **/

      if (!get_magic_quotes_gpc()) {
      $subject = addslashes($subject);
      $message = addslashes($message);
      }

      if ($enable_trackback=1 and (isset($_POST["trackback_url"]) and !empty($_POST["trackback_url"])) ) {
      $post_urls          = $_POST["trackback_url"];
      $tb['blogEntryTitle'] = $subject;
      $tb['blogEntryURL']   = $myblogURL;
      $tb['blogName']       = $myblogname;
      $tb['blogExcerpt']    = $message;
      multi_tb($post_urls, $tb) ;
      $tbstatus ="<br /><br /><center><div class=\"quote\">".$lang['Trackback_status']." : <br />".$tbreply."</div></center>";
      }
      else { $tbstatus ="";  }

      $sql = "INSERT INTO ".POST_TBL." SET user_id='$user_id', subject='$subject', message='$message', timestamp='$timestamp', cat_id='$cat_id'";
      $query = mysql_query($sql) or die("Cannot query the database.<br>" . mysql_error());
      message($lang['New_post'], $lang['Msg_posted'].".........".$tbstatus );
      echo "<meta http-equiv=\"Refresh\" content=\"10;url=".self_url()."/admin.php\" />";
      }
   }
   else {
    $template->assign_block_vars('showtrackback', array(
          'L_TRACKBACK_URLS' => $lang['Trackback_urls'],
          ));

      $nn  = date('F');
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

      $hh  = gmtdate('H', time(), $timezone );
      $min = gmtdate('i', time(), $timezone );
      $ss  = gmtdate('s', time(), $timezone );
      $mm  = gmtdate('n', time(), $timezone );
      $dd  = gmtdate('d', time(), $timezone );
      $yy  = gmtdate('Y', time(), $timezone );


      $template->assign_vars(array(
     'POST_DATE'      =>  $dd,
     'POST_YEAR'      =>  $yy,
     'POST_HOUR'      =>  $hh,
     'POST_MIN'       =>  $min,
     'POST_SEC'       =>  $ss,
     ));

    $template->pparse('formsubmit');
    }
unset($mth_text) ;
?>
