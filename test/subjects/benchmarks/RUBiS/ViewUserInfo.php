<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "ViewUserInfo.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();
    
    $userId = $HTTP_POST_VARS['userId'];
    if ($userId == null)
    {
      $userId = $HTTP_GET_VARS['userId'];
      if ($userId == null)
      {
         printError($scriptName, $startTime, "Viewing user information", "You must provide an item identifier!<br>");
         exit();
      }
    }
      
    getDatabaseLink($link);
    begin($link);
    $userResult = mysql_query("SELECT * FROM users WHERE users.id=$userId", $link) or die("ERROR: Query failed");
    if (mysql_num_rows($userResult) == 0)
    {
      commit($link);
      die("<h3>ERROR: Sorry, but this user does not exist.</h3><br>\n");
    }

    printHTMLheader("RUBiS: View user information");

      // Get general information about the user
    $userRow = mysql_fetch_array($userResult);
    $firstname = $userRow["firstname"];
    $lastname = $userRow["lastname"];
    $nickname = $userRow["nickname"];
    $email = $userRow["email"];
    $creationDate = $userRow["creation_date"];
    $rating = $userRow["rating"];

    print("<h2>Information about ".$nickname."<br></h2>");
    print("Real life name : ".$firstname." ".$lastname."<br>");
    print("Email address  : ".$email."<br>");
    print("User since     : ".$creationDate."<br>");
    print("Current rating : <b>".$rating."</b><br>");

      // Get the comments about the user
    $commentsResult = mysql_query("SELECT * FROM comments WHERE comments.to_user_id=$userId", $link) or die("ERROR: Query failed for the list of comments.");
    if (mysql_num_rows($commentsResult) == 0)
      print("<h2>There is no comment for this user.</h2><br>\n");
    else
    {
	print("<DL>\n");
	while ($commentsRow = mysql_fetch_array($commentsResult))
	{
	    $authorId = $commentsRow["from_user_id"];
	    $authorResult = mysql_query("SELECT nickname FROM users WHERE users.id=$authorId", $link) or die("ERROR: Query failed for the comment author.");
	    if (mysql_num_rows($authorResult) == 0)
		die("ERROR: This author does not exist.<br>\n");
	    else
	    {
		$authorRow = mysql_fetch_array($authorResult);
		$authorName = $authorRow["nickname"];
	    }
	    $date = $commentsRow["date"];
	    $comment = $commentsRow["comment"];
	    print("<DT><b><BIG><a href=\"/PHP/ViewUserInfo.php?userId=".$authorId."\">$authorName</a></BIG></b>"." wrote the ".$date."<DD><i>".$comment."</i><p>\n");
	    mysql_free_result($authorResult);
	}
	print("</DL>\n");

    }
    commit($link);
    mysql_free_result($userResult);
    mysql_free_result($commentsResult);
    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
