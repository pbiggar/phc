<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "Search.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();

    $storyId = $HTTP_POST_VARS['storyId'];
    if ($storyId == null)
    {
      $storyId = $HTTP_GET_VARS['storyId'];
      if ($storyId == null)
      {
         printError($scriptName, $startTime, "Posting comment", "You must provide a story identifier!<br>");
         exit();
      }
    }
    $parent = $HTTP_POST_VARS['parent'];
    if ($parent == null)
    {
      $parent = $HTTP_GET_VARS['parent'];
      if ($parent == null)
      {
         printError($scriptName, $startTime, "Posting comment", "You must provide a follow up identifier!<br>");
         exit();
      }
    }

    $comment_table = $HTTP_POST_VARS['comment_table'];
    if ($comment_table == null)
    {
      $comment_table = $HTTP_GET_VARS['comment_table'];
      if ($comment_table == null)
      {
         printError($scriptName, $startTime, "Viewing comment", "You must provide a comment table!<br>");
         exit();
      }
    }

    printHTMLheader("RUBBoS: Comment submission");
    print("<p><br><center><h2>Post a comment !</h2><br>\n".
          "<form action=\"/PHP/StoreComment.php\" method=POST>\n".
          "<input type=hidden name=storyId value=$storyId>\n".
          "<input type=hidden name=parent value=$parent>\n".
          "<input type=hidden name=comment_table value=$comment_table>\n".
          "<center><table>\n".
          "<tr><td><b>Nickname</b><td><input type=text size=20 name=nickname>\n".
          "<tr><td><b>Password</b><td><input type=text size=20 name=password>\n".
          "<tr><td><b>Subject</b><td><input type=text size=100 name=subject>\n".
          "</SELECT></table><p><br>\n".
          "<TEXTAREA rows=\"20\" cols=\"80\" name=\"body\">Write your comment here</TEXTAREA><br><p>\n".
          "<input type=submit value=\"Post your comment now!\"></center><p>\n");

    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>

