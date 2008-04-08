<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "SubmitStory.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();

    $nickname = $HTTP_POST_VARS['nickname'];
    if ($nickname == null)
    {
      $nickname = $HTTP_GET_VARS['nickname'];
    }

    $password = $HTTP_POST_VARS['password'];
    if ($password == null)
    {
      $password = $HTTP_GET_VARS['password'];
    }

    $title = $HTTP_POST_VARS['title'];
    if ($title == null)
    {
      $title = $HTTP_GET_VARS['title'];
      if ($title == null)
      {
         printError($scriptName, $startTime, "SubmitStory", "You must provide a story title!<br>");
         exit();
      }
    }

    $body = $HTTP_POST_VARS['body'];
    if ($body == null)
    {
      $body = $HTTP_GET_VARS['body'];
      if ($body == null)
      {
         printError($scriptName, $startTime, "SubmitStory", "<h3>You must provide a story body!<br></h3>");
         exit();
      }
    }
      
    $category = $HTTP_POST_VARS['category'];
    if ($category == null)
    {
      $category = $HTTP_GET_VARS['category'];
      if ($category == null)
      {
         printError($scriptName, $startTime, "SubmitStory", "<h3>You must provide a category !<br></h3>");
         exit();
      }
    }

    getDatabaseLink($link);

    printHTMLheader("RUBBoS: Story submission result");

    print("<center><h2>Story submission result:</h2></center><p>\n");

    // Authenticate the user
    $userId = 0;
    $access = 0;
    if (($nickname != null) && ($password != null))
    {
      $result = mysql_query("SELECT id,access FROM users WHERE nickname=\"$nickname\" AND password=\"$password\"", $link) or die("ERROR: Authentication query failed");
      if (mysql_num_rows($result) != 0)
      {
        $row = mysql_fetch_array($result);
        $userId = $row["id"];
        $access = $row["access"];
      }
      mysql_free_result($result);
    }

    $table = "submissions";
    if ($userId == 0)
      print("Story stored by the 'Anonymous Coward'<br>\n");
    else
    {
      if ($access == 0)
        print("Story submitted by regular user #$userId<br>\n");
      else
      {
        print("Story posted by author #$userId<br>\n");
        $table = "stories";
      }
    }

    // Add story to database
    $now = date("Y:m:d H:i:s");
    $result = mysql_query("INSERT INTO $table VALUES (NULL, \"$title\", \"$body\", '$now', $userId, $category)", $link) or die("ERROR: Failed to insert new story in database.");

    print("Your story has been successfully stored in the $table database table<br>\n");
    
    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
