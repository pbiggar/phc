<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "PutComment.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();
    
    $to = $HTTP_POST_VARS['to'];
    if ($to == null)
    {
      $to = $HTTP_GET_VARS['to'];
      if ($to == null)
      {
         printError($scriptName, $startTime, "PutComment", "You must provide a user identifier!<br>");
         exit();
      }
    }      

    $nickname = $HTTP_POST_VARS['nickname'];
    if ($nickname == null)
    {
      $nickname = $HTTP_GET_VARS['nickname'];
      if ($nickname == null)
      {
         printError($scriptName, $startTime, "PutComment", "You must provide a nick name!<br>");
         exit();
      }
    }

    $password = $HTTP_POST_VARS['password'];
    if ($password == null)
    {
      $password = $HTTP_GET_VARS['password'];
      if ($password == null)
      {
         printError($scriptName, $startTime, "PutComment", "You must provide a password!<br>");
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

    getDatabaseLink($link);

    begin($link);
    // Authenticate the user
    $userId = authenticate($nickname, $password, $link);
    if ($userId == -1)
    {
      printError($scriptName, $startTime, "PutComment", "You don't have an account on RUBiS!<br>You have to register first.<br>\n");
      commit($link);
      exit();	
    }

    $result = mysql_query("SELECT * FROM items WHERE items.id=$itemId") or die("ERROR: Item query failed");
    if (mysql_num_rows($result) == 0)
    {
      printError($scriptName, $startTime, "PutComment", "<h3>Sorry, but this item does not exist.</h3><br>");
      commit($link);
      exit();
    }

    $toRes = mysql_query("SELECT * FROM users WHERE id=\"$to\"") or die("ERROR: User query failed");
    if (mysql_num_rows($toRes) == 0)
    {
      printError($scriptName, $startTime, "PutComment", "<h3>Sorry, but this user does not exist.</h3><br>");
      commit($link);
      exit();
    }

    $row = mysql_fetch_array($result);
    $userRow = mysql_fetch_array($toRes);

    printHTMLheader("RUBiS: Comment service");

    print("<center><h2>Give feedback about your experience with ".$userRow["name"]."</h2><br>\n");
    print("<form action=\"/PHP/StoreComment.php\" method=POST>\n".
          "<input type=hidden name=to value=$to>\n".
          "<input type=hidden name=from value=$userId>\n".
          "<input type=hidden name=itemId value=$itemId>\n".
          "<center><table>\n".
          "<tr><td><b>From</b><td>$nickname\n".
          "<tr><td><b>To</b><td>".$userRow["nickname"]."\n".
          "<tr><td><b>About item</b><td>".$row["name"]."\n".
          "<tr><td><b>Rating</b>\n".
          "<td><SELECT name=rating>\n".
          "<OPTION value=\"5\">Excellent</OPTION>\n".
          "<OPTION value=\"3\">Average</OPTION>\n".
          "<OPTION selected value=\"0\">Neutral</OPTION>\n".
          "<OPTION value=\"-3\">Below average</OPTION>\n".
          "<OPTION value=\"-5\">Bad</OPTION>\n".
          "</SELECT></table><p><br>\n".
          "<TEXTAREA rows=\"20\" cols=\"80\" name=\"comment\">Write your comment here</TEXTAREA><br><p>\n".
          "<input type=submit value=\"Post this comment now!\"></center><p>\n");

    mysql_free_result($result);
    commit($link);
    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
