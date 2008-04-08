<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "AcceptStory.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();

    $storyId = $HTTP_POST_VARS['storyId'];
    if ($storyId == null)
    {
      $storyId = $HTTP_GET_VARS['storyId'];
      if ($storyId == null)
      {
         printError($scriptName, $startTime, "AcceptStory", "<h3>You must provide a story identifier !<br></h3>");
         exit();
      }
    }

    getDatabaseLink($link);

    printHTMLheader("RUBBoS: Story submission result");

    print("<center><h2>Story submission result:</h2></center><p>\n");

    $result = mysql_query("SELECT * FROM submissions WHERE id=$storyId") or die("ERROR: Query failed");
    if (mysql_num_rows($result) == 0)
      die("<h3>ERROR: Sorry, but this story does not exist.</h3><br>\n");
    $row = mysql_fetch_array($result);

    // Add story to database
    $result = mysql_query("INSERT INTO stories VALUES (NULL, \"".$row["title"]."\", \"".$row["body"]."\", '".$row["date"]."', ".$row["writer"].", ".$row["category"].")", $link) or die("ERROR: Failed to insert new story in database.");
    mysql_query("DELETE FROM submissions WHERE id=$storyId", $link); 

    print("The story has been successfully moved from the submission to the stories database table<br>\n");
    
    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
