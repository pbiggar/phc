<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "Author.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();
    
    $nickname = $HTTP_POST_VARS['nickname'];
    if ($nickname == null)
    {
      $nickname = $HTTP_GET_VARS['nickname'];
      if ($nickname == null)
      {
         printError($scriptName, $startTime, "Author", "You must provide a nick name!<br>");
         exit();
      }
    }

    $password = $HTTP_POST_VARS['password'];
    if ($password == null)
    {
      $password = $HTTP_GET_VARS['password'];
      if ($password == null)
      {
         printError($scriptName, $startTime, "Author", "You must provide a password!<br>");
         exit();
      }
    }

    getDatabaseLink($link);

    // Authenticate the user
    $userId = 0;
    $access = 0;
    if (($nickname != null) && ($password != null))
    {
      $result = mysql_query("SELECT id,access FROM users WHERE nickname=\"$nickname\" AND password=\"$password\"", $link) or die("ERROR: Authentification query failed");
      if (mysql_num_rows($result) != 0)
      {
        $row = mysql_fetch_array($result);
        $userId = $row["id"];
        $access = $row["access"];
      }
      mysql_free_result($result);
    }

    if (($userId == 0) || ($access == 0))
    {
      printHTMLheader("RUBBoS: Author page");
      print("<p><center><h2>Sorry, but this feature is only accessible by users with an author access.</h2></center><p>\n");
    }
    else
    {
      printHTMLheader("RUBBoS: Author page");
      print("<p><center><h2>Which administrative task do you want to do ?</h2></center>\n", 
            "<p><p><a href=\"/PHP/ReviewStories.php?authorId=$userId\">Review submitted stories</a><br>\n");
    }

    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
