<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "ReviewStories.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();

    getDatabaseLink($link);

    printHTMLheader("RUBBoS: Review Stories");

    $now = date("Y:m:d H:i:s");
    $result = mysql_query("SELECT * FROM submissions ORDER BY date DESC LIMIT 10", $link) or die("ERROR: Query failed");
    if (mysql_num_rows($result) == 0)
      print("<h2>Sorry, but there is no submitted story available at this time.</h2><br>\n");

    while ($row = mysql_fetch_array($result))
    {
      print("<br><hr>\n");
      printHTMLHighlighted($row["title"]);
      $username = getUserName($row["writer"], $link);
      print("<B>Posted by ".$username." on ".$row["date"]."</B><br>\n");
      print($row["body"]);
      print("<br><p><center><B>[ <a href=\"AcceptStory.php?storyId=".$row["id"]."\">Accept</a> | <a href=\"RejectStory.php?storyId=".$row["id"]."\">Reject</a> ]</B><p>\n");
    }
    mysql_free_result($result);
    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
