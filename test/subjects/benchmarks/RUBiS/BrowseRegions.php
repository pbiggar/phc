<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "BrowseRegions.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();

    printHTMLheader("RUBiS available regions");
    
    getDatabaseLink($link);
    begin($link);
    $result = mysql_query("SELECT * FROM regions", $link) or die("ERROR: Query failed");
    commit($link);
    if (mysql_num_rows($result) == 0)
      print("<h2>Sorry, but there is no region available at this time. Database table is empty</h2><br>");
    else
      print("<h2>Currently available regions</h2><br>");

    while ($row = mysql_fetch_array($result))
    {
      print("<a href=\"/PHP/BrowseCategories.php?region=".$row["id"]."\">".$row["name"]."</a><br>\n");
    }
    mysql_free_result($result);
    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
