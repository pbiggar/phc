<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "BrowseCategories.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();

    $region = $HTTP_POST_VARS['region'];
    if ($region == null)
      $region = $HTTP_GET_VARS['region'];

    $username = $HTTP_POST_VARS['nickname'];
    if ($username == null)
      $username = $HTTP_GET_VARS['nickname'];

    $password = $HTTP_POST_VARS['password'];
    if ($password == null)
      $password = $HTTP_GET_VARS['password'];

    getDatabaseLink($link);

    $userId = -1;
    if (($username != null && $username !="") || ($password != null && $password !=""))
    { // Authenticate the user
      $userId = authenticate($username, $password, $link);
      if ($userId == -1)
      {
        printError($scriptName, $startTime, "Authentication", "You don't have an account on RUBiS!<br>You have to register first.<br>\n");
        exit();	
      }
    }

    printHTMLheader("RUBiS available categories");

    begin($link);
    $result = mysql_query("SELECT * FROM categories", $link) or die("ERROR: Query failed");
    commit($link);
    if (mysql_num_rows($result) == 0)
      print("<h2>Sorry, but there is no category available at this time. Database table is empty</h2><br>\n");
    else
      print("<h2>Currently available categories</h2><br>\n");

    while ($row = mysql_fetch_array($result))
    {
      if ($region != NULL)
        print("<a href=\"/PHP/SearchItemsByRegion.php?category=".$row["id"]."&categoryName=".urlencode($row["name"])."&region=$region\">".$row["name"]."</a><br>\n");
      else if ($userId != -1)
        print("<a href=\"/PHP/SellItemForm.php?category=".$row["id"]."&user=$userId\">".$row["name"]."</a><br>\n");
      else
        print("<a href=\"/PHP/SearchItemsByCategory.php?category=".$row["id"]."&categoryName=".urlencode($row["name"])."\">".$row["name"]."</a><br>\n");
    }
    mysql_free_result($result);
    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
