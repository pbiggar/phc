<?
  define('IN_MYBLOGGIE', true);
  $mybloggie_root_path = trim('../');
  include_once('../config.php');
  include_once('../includes/db.php');
  include_once('../includes/function.php');

  if  (isset($_SERVER['PHP_SELF']) && isset($_SERVER['HTTP_HOST'])) {
   $me = $_SERVER['PHP_SELF'];
   $path_pieces = explode("/", $me);
   $trim1= array_pop($path_pieces);
   $trim2 = array_pop($path_pieces);
   $pathweb = implode("/", $path_pieces);
   $mybloggie_url = "http://".$_SERVER['HTTP_HOST'].$pathweb;
   }
elseif (isset($_SERVER['PHP_SELF']) && isset($_SERVER['SERVER_NAME'])) {
   $me = $_SERVER['PHP_SELF'];
   $path_pieces = explode("/", $me);
   $trim1= array_pop($path_pieces);
   $trim2 = array_pop($path_pieces);
   $pathweb = implode("/", $path_pieces);
   $mybloggie_url = 'http://'.$_SERVER['SERVER_NAME'].$pathweb;
   }

  $sql = "SELECT ".CAT_TBL.".cat_desc, ".POST_TBL.".cat_id, ".CAT_TBL.".cat_id, ".POST_TBL.".post_id, ".POST_TBL.".subject,".POST_TBL.".message, ".USER_TBL.".user, ".POST_TBL.".timestamp, ".USER_TBL.".id, ".POST_TBL.".user_id FROM ".POST_TBL.", ".USER_TBL.", ".CAT_TBL."
WHERE ".POST_TBL.".user_id=".USER_TBL.".id  AND  ".CAT_TBL.".cat_id=".POST_TBL.".cat_id
Order by  ".POST_TBL.".timestamp DESC, ".POST_TBL.".post_id DESC
LIMIT 0,5 ";

 // $sql = "SELECT ".POST_TBL.".post_id, ".POST_TBL.".subject, ".POST_TBL.".message, ".POST_TBL.".timestamp FROM ".POST_TBL."
 // Order by  ".POST_TBL.".timestamp DESC
  //LIMIT 0, 5 ";

  if( !($result = $db->sql_query($sql)) )
   {
    $sql_error = $db->sql_error();
    echo $sql_error['message'];
   }

$result = $db->sql_query($sql) ;

header("Content-type: application/xml");
echo "<?xml version=\"1.0\"?".">";
?>
<!-- generator="mybloggie/<? echo $mb_version  ?>" -->
<rss version="2.0" xmlns:content="http://purl.org/rss/1.0/modules/content/" xmlns:wfw="http://wellformedweb.org/CommentAPI/">
     <channel>
        <title><? echo $myblogname ?></title>
        <link><? if (isset($_SERVER['HTTP_HOST'])) { echo "http://".$_SERVER['HTTP_HOST']; }
                 elseif (isset($_SERVER['SERVER_NAME'])) { echo "http://".$_SERVER['SERVER_NAME']; } ?></link>
        <description><? echo $blog_desc ?></description>
        <docs>http://backend.userland.com/rss</docs>
        <generator>http://mybloggie.mywebland.com/?v=<?php echo $mb_version ?></generator>
        <? while ($row = $db->sql_fetchrow($result)){
           $time = date("h:i:s a", $row['timestamp']) ;
           $date = date("d M Y", $row['timestamp']) ;
           $message=$row['message'];
           //filter_1($message);
           $message = str_replace("&", "&amp;", $message);
        ?>
        <item>
            <title><? echo $row['subject'] ?></title>
            <link><? echo $mybloggie_url."/index.php?mode=viewid&amp;post_id=".$row['post_id'] ?></link>
            <pubDate><? echo $date." ".$time." GMT ".$sign.$timezone ?></pubDate>
            <category><? echo htmlspecialchars($row['cat_desc']) ?></category>
            <guid><? echo $mybloggie_url."/index.php?mode=viewid&amp;post_id=".$row['post_id']  ?></guid>
            <description><? echo $message ?></description>
            <content:encoded><![CDATA[<? echo "<p>".chop_text($message, 300, 10)."...</p>"  ?>]]></content:encoded>
            <comments><? echo $mybloggie_url."/index.php?mode=viewid&amp;post_id=".$row['post_id'] ?></comments>
        </item>
        <? } ?>
    </channel>
</rss>

