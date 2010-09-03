<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "StoreComment.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();
    
    $to = $HTTP_POST_VARS['to'];
    if ($to == null)
    {
      $to = $HTTP_GET_VARS['to'];
      if ($to == null)
      {
         printError($scriptName, $startTime, "PutComment", "You must provide a 'to user' identifier!<br>");
         exit();
      }
    }      

    $from = $HTTP_POST_VARS['from'];
    if ($from == null)
    {
      $from = $HTTP_GET_VARS['from'];
      if ($from == null)
      {
         printError($scriptName, $startTime, "PutComment", "You must provide a 'from user' identifier!<br>");
         exit();
      }
    }

    $itemId = $HTTP_POST_VARS['itemId'];
    if ($itemId == null)
    {
      $itemId = $HTTP_GET_VARS['itemId'];
      if ($itemId == null)
      {
         printError($scriptName, $startTime, "PutComment", "You must provide an item identifier!<br>");
         exit();
      }
    }

    $rating = $HTTP_POST_VARS['rating'];
    if ($rating == null)
    {
      $rating = $HTTP_GET_VARS['rating'];
      if ($rating == null)
      {
         printError($scriptName, $startTime, "StoreComment", "<h3>You must provide a user identifier!<br></h3>");
         exit();
      }
    }
      
    $comment = $HTTP_POST_VARS['comment'];
    if ($comment == null)
    {
      $comment = $HTTP_GET_VARS['comment'];
      if ($comment == null)
      {
         printError($scriptName, $startTime, "StoreComment", "<h3>You must provide a comment !<br></h3>");
         exit();
      }
    }

    getDatabaseLink($link);
    begin($link);

    mysql_query("LOCK TABLES users WRITE, comments WRITE", $link) or die("ERROR: Failed to acquire locks on users and comments tables.");
    // Update user rating
    $toRes = mysql_query("SELECT id FROM users WHERE id=\"$to\"") or die("ERROR: User query failed");
    if (mysql_num_rows($toRes) == 0)
    {
      printError($scriptName, $startTime, "StoreComment", "<h3>Sorry, but this user does not exist.</h3><br>");
      exit();
    }
    $userRow = mysql_fetch_array($toRes);
    $rating = $rating + $userRow["rating"];
    mysql_query("UPDATE users SET rating=$rating WHERE id=$to") or die("ERROR: Unable to update user's rating\n");

    // Add bid to database
    $now = date("Y:m:d H:i:s");
    $result = mysql_query("INSERT INTO comments VALUES (NULL, $from, $to, $itemId, $rating, '$now', \"$comment\")", $link) or die("ERROR: Failed to insert new comment in database.");
    mysql_query("UNLOCK TABLES", $link) or die("ERROR: Failed to unlock users and comments tables.");
    commit($link);

    printHTMLheader("RUBiS: Comment posting");
    print("<center><h2>Your comment has been successfully posted.</h2></center>\n");
    
    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
