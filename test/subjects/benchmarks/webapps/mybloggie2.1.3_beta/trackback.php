<?
define('IN_MYBLOGGIE', true);
$mybloggie_root_path = './';

include_once('./config.php');
include_once('./includes/db.php');
//include_once('./includes/template.php');
include_once('./includes/function.php');
include_once('./language/lang_eng.php');
include_once('./includes/tb.class.php');
$tback = new tb;

if(empty($tb_id))
 {
    $url_elements = explode( '/', $_SERVER['REQUEST_URI'], 30 );
    $tb_id = intval( $url_elements[count($url_elements)-1] );
 }
  $sql = $sql = "SELECT post_id FROM ".POST_TBL." WHERE ".POST_TBL.".post_id = ".$tb_id;
  $result = $db->sql_query($sql);

  if ($enable_trackback!="1") {
  $tback->trackback_reply(1, "<p>Sorry, this weblog does not allow any trackback at this moment.</p>"); }
  elseif ( $db->sql_numrows($result) == 0 ) {
   $tback->trackback_reply(1, "<p>Sorry, Trackback target post not found</p>"); }
   else {

if(!empty($_REQUEST['title'])) {
$title=urldecode(substr($_REQUEST['title'],0,$tb_title_len));
}
else { $tback->trackback_reply(1, "<p>Sorry, Trackback failed.. Reason : No title</p>"); }

if(!empty($_REQUEST['url'])) {
$url=urldecode($_REQUEST['url']);

if (validate_url($url)==false) { $tback->trackback_reply(1, "<p>Sorry, Trackback failed.. Reason : URL not valid</p>"); }
}
else { $tback->trackback_reply(1, "<p>Sorry, Trackback failed.. Reason : No URL</p>"); }

if(!empty($_REQUEST['excerpt']))
 {
  $excerpt=urldecode(substr($_REQUEST['excerpt'],0,$tb_excerpt_len));
 } else {
    $tback->trackback_reply(1, "<p>Sorry, Trackback failed.. Reason : No Excerpt</p>");
 }

// The blog name
if(!empty($_REQUEST['blog_name']))
 {
    $blog_name=urldecode(substr($_REQUEST['blog_name'],0,$tb_blogname_len));
 } else
 {
    $blog_name="No Blog Name";
 }

$timestamp = mktime(gmtdate('H', time(), $timezone ),gmtdate('i', time(), $timezone ),
             gmtdate('s', time(), $timezone ), gmtdate('n', time(), $timezone ),
             gmtdate('d', time(), $timezone ), gmtdate('Y', time(), $timezone ));

$sql = "INSERT INTO ".COMMENT_TBL." SET post_id='$tb_id', comment_subject='$title', comments='$excerpt', com_tstamp='$timestamp' ,
              poster = '$blog_name', home='$url', comment_type='trackback'";
$result = $db->sql_query($sql) or die("Cannot query the database.<br>" . mysql_error());

$tback->trackback_reply(0, "<p>Trackback successful completed</p>");
}
?>
