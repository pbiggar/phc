<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "SubmitStory.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();

    getDatabaseLink($link);

    printHTMLheader("RUBBoS: Story submission");

    print("<center><h2>Submit your incredible story !</h2><br>\n");
    print("<form action=\"/PHP/StoreStory.php\" method=POST>\n".
          "<center><table>\n".
          "<tr><td><b>Nickname</b><td><input type=text size=20 name=nickname>\n".
          "<tr><td><b>Password</b><td><input type=text size=20 name=password>\n".
          "<tr><td><b>Story title</b><td><input type=text size=100 name=title>\n".
          "<tr><td><b>Category</b><td><SELECT name=category>\n");
    $result = mysql_query("SELECT * FROM categories", $link) or die("ERROR: Query failed");
    while ($row = mysql_fetch_array($result))
    {
      print("<OPTION value=\"".$row["id"]."\">".$row["name"]."</OPTION>\n");
    }
    print("</SELECT></table><p><br>\n".
          "<TEXTAREA rows=\"20\" cols=\"80\" name=\"body\">Write your story here</TEXTAREA><br><p>\n".
          "<input type=submit value=\"Submit this story now!\"></center><p>\n");

    mysql_free_result($result);
    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
