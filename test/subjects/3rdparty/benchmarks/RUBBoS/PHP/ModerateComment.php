<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "ModerateComment.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();

    $comment_table = $HTTP_POST_VARS['comment_table'];
    if ($comment_table == null)
    {
      $comment_table = $HTTP_GET_VARS['comment_table'];
      if ($comment_table == null)
      {
         printError($scriptName, $startTime, "Moderating comment", "You must provide a comment table!<br>");
         exit();
      }
    }

    $commentId = $HTTP_POST_VARS['commentId'];
    if ($commentId == null)
    {
      $commentId = $HTTP_GET_VARS['commentId'];
      if ($commentId == null)
      {
         printError($scriptName, $startTime, "Moderating comment", "You must provide a comment identifier!<br>");
         exit();
      }
    }

    getDatabaseLink($link);
    printHTMLheader("RUBBoS: Comment moderation");

    $result = mysql_query("SELECT * FROM $comment_table WHERE id=$commentId", $link) or die("ERROR: Query failed");
    if (mysql_num_rows($result) == 0)
     die("<h3>ERROR: Sorry, but this comment does not exist.</h3><br>\n");
    $row = mysql_fetch_array($result);

    print("<p><br><center><h2>Moderate a comment !</h2></center><br>\n<br><hr><br>");
    $username = getUserName($row["writer"], $link);
    print("<TABLE width=\"100%\" bgcolor=\"#CCCCFF\"><TR><TD><FONT size=\"4\" color=\"#000000\"><center><B><a href=\"/PHP/ViewComment.php?comment_table=$comment_table&storyId=".$row["storyId"]."&commentId=".$row["id"]."\">".$row["subject"]."</a></B>&nbsp</FONT> (Score:".$row["rating"].")</center></TABLE>\n");
    print("<TABLE><TR><TD><B>Posted by ".$username." on ".$row["date"]."</B><p>\n");
    print("<TR><TD>".$row["comment"]."</TABLE><p><hr><p>\n".
          "<form action=\"/PHP/StoreModeratorLog.php\" method=POST>\n".
          "<input type=hidden name=commentId value=$commentId>\n".
          "<input type=hidden name=comment_table value=$comment_table>\n".
          "<center><table>\n".
          "<tr><td><b>Nickname</b><td><input type=text size=20 name=nickname>\n".
          "<tr><td><b>Password</b><td><input type=text size=20 name=password>\n".
          "<tr><td><b>Rating</b><td><SELECT name=rating>\n".
          "<OPTION value=\"-1\">-1: Offtopic</OPTION>\n".
          "<OPTION selected value=\"0\">0: Not rated</OPTION>\n".
          "<OPTION value=\"1\">1: Interesting</OPTION>\n".
          "</SELECT></table><p><br>\n".
          "<input type=submit value=\"Moderate this comment now!\"></center><p>\n");

    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>

