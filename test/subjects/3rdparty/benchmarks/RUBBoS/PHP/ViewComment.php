<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php

// Display the nested comments
function display_follow_up($cid, $level, $display, $filter, $link, $comment_table, $separator)
{
  $follow = mysql_query("SELECT * FROM $comment_table WHERE parent=$cid AND rating>=$filter", $link) or die("ERROR: Query failed");
  while ($follow_row = mysql_fetch_array($follow))
  {
    if ($rating >= $filter)
      {
	if (!$separator)
	  {
	    print("<br><hr><br>");
	    $separator = true;
	  }
	if ($display == 1) // Preview nested comments
	  {
	    for ($i = 0 ; $i < $level ; $i++)
	      printf(" &nbsp &nbsp &nbsp ");
	    print("<a href=\"/PHP/ViewComment.php?comment_table=$comment_table&storyId=".$follow_row["story_id"]."&commentId=".$follow_row["id"]."&filter=$filter&display=$display\">".$follow_row["subject"]."</a> by ".getUserName($follow_row["writer"], $link)." on ".$follow_row["date"]."<br>\n");
	  }
	else
	  {
	    $username = getUserName($follow_row["writer"], $link);
	    print("<TABLE bgcolor=\"#CCCCFF\"><TR>");
	    for ($i = 0 ; $i < $level ; $i++)
	      printf("<TD>&nbsp&nbsp&nbsp");
	    print("<TD><FONT size=\"4\" color=\"#000000\"><B><a href=\"/PHP/ViewComment.php?comment_table=$comment_table&storyId=".$follow_row["story_id"]."&commentId=".$follow_row["id"]."&filter=$filter&display=$display\">".$follow_row["subject"]."</a></B>&nbsp</FONT> (Score:".$follow_row["rating"].")</TABLE>\n");
	    print("<TABLE>");
	    for ($i = 0 ; $i < $level ; $i++)
	      printf("<TD>&nbsp&nbsp&nbsp");
	    print("<TD><B>Posted by ".$username." on ".$follow_row["date"]."</B><p><TR>\n");
	    for ($i = 0 ; $i < $level ; $i++)
	      printf("<TD>&nbsp&nbsp&nbsp");
	    print("<TD>".$follow_row["comment"]."<TR>");
	    for ($i = 0 ; $i < $level ; $i++)
	      printf("<TD>&nbsp&nbsp&nbsp");
	    print("<TD><p>[ <a href=\"/PHP/PostComment.php?comment_table=$comment_table&storyId=".$follow_row["story_id"]."&parent=".$follow_row["id"]."\">Reply to this</a>".
		  "&nbsp|&nbsp<a href=\"/PHP/ViewComment.php?comment_table=$comment_table&storyId=".$follow_row["story_id"]."&commentId=".$follow_row["parent"].
		  "&filter=$filter&display=$display\">Parent</a>&nbsp|&nbsp<a href=\"/PHP/ModerateComment.php?comment_table=$comment_table&commentId=".
		  $follow_row["id"]."\">Moderate</a> ]</TABLE><br>");
	  }
      }
    if ($follow_row["childs"] > 0)
      display_follow_up($follow_row["id"], $level+1, $display, $filter, $link, $comment_table, $separator);
  }
}


    // Check parameters
    $scriptName = "ViewComment.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();
    
    $filter = $HTTP_POST_VARS['filter'];
    if ($filter == null)
    {
      $filter = $HTTP_GET_VARS['filter'];
      if ($filter == null)
        $filter = 0;
    }

    $display = $HTTP_POST_VARS['display'];
    if ($display == null)
    {
      $display = $HTTP_GET_VARS['display'];
      if ($display == null)
        $display = 0;
    }

    $storyId = $HTTP_POST_VARS['storyId'];
    if ($storyId == null)
    {
      $storyId = $HTTP_GET_VARS['storyId'];
      if ($storyId == null)
      {
         printError($scriptName, $startTime, "Viewing comment", "You must provide a story identifier!<br>");
         exit();
      }
    }
      
    $commentId = $HTTP_POST_VARS['commentId'];
    if ($commentId == null)
    {
      $commentId = $HTTP_GET_VARS['commentId'];
      if ($commentId == null)
      {
         printError($scriptName, $startTime, "Viewing comment", "You must provide a comment identifier!<br>");
         exit();
      }
    }

    $comment_table = $HTTP_POST_VARS['comment_table'];
    if ($comment_table == null)
    {
      $comment_table = $HTTP_GET_VARS['comment_table'];
      if ($comment_table == null)
      {
         printError($scriptName, $startTime, "Viewing comment", "You must provide a comment table!<br>");
         exit();
      }
    }

    getDatabaseLink($link);
    if ($commentId == 0)

      $parent = 0;
    else
    {
      $result = mysql_query("SELECT parent FROM $comment_table WHERE id=$commentId", $link) or die("ERROR: Query failed");
      if (mysql_num_rows($result) == 0)
        die("<h3>ERROR: Sorry, but this comment does not exist.</h3><br>\n");
      $row = mysql_fetch_array($result);
      $parent = $row["parent"];
    }

    printHTMLheader("RUBBoS: Viewing comments");

    // Display comment filter chooser
    print("<center><form action=\"/PHP/ViewComment.php\" method=POST>\n".
          "<input type=hidden name=commentId value=$commentId>\n".
          "<input type=hidden name=storyId value=$storyId>\n".
          "<input type=hidden name=comment_table value=$comment_table>\n".
          "<B>Filter :</B>&nbsp&nbsp<SELECT name=filter>\n");
    $count_result = mysql_query("SELECT rating, COUNT(rating) AS count FROM $comment_table WHERE story_id=$storyId GROUP BY rating ORDER BY rating", $link) or die("ERROR: Query failed");
    $i = -1;
    while ($count_row = mysql_fetch_array($count_result))
    {
      while (($i < 6) && ($count_row["rating"] != $i))
      {
        if ($i == $filter)
          print("<OPTION selected value=\"$i\">$i: 0 comment</OPTION>\n");
        else
          print("<OPTION value=\"$i\">$i: 0 comment</OPTION>\n");
        $i++;
      }
      if ($count_row["rating"] == $i)
      {
        if ($i == $filter)
          print("<OPTION selected value=\"$i\">$i: ".$count_row["count"]." comments</OPTION>\n");
        else
          print("<OPTION value=\"$i\">$i: ".$count_row["count"]." comments</OPTION>\n");
        $i++;
      }
    }
    while ($i < 6)
    {
      print("<OPTION value=\"$i\">$i: 0 comment</OPTION>\n");
      $i++;
    }

    print("</SELECT>&nbsp&nbsp&nbsp&nbsp<SELECT name=display>\n".
          "<OPTION value=\"0\">Main threads</OPTION>\n");
    if ($display == 1)
      print("<OPTION selected value=\"1\">Nested</OPTION>\n");
    else
      print("<OPTION value=\"1\">Nested</OPTION>\n");
    if ($display == 2)
      print("<OPTION selected value=\"2\">All comments</OPTION>\n");
    else
      print("<OPTION value=\"2\">All comments</OPTION>\n");
    print("</SELECT>&nbsp&nbsp&nbsp&nbsp<input type=submit value=\"Refresh display\"></center><p>\n");          

    // Display the comments
$comment = mysql_query("SELECT * FROM $comment_table WHERE story_id=$storyId AND parent=0", $link) or die("ERROR: Query failed");
    while ($comment_row = mysql_fetch_array($comment))
    {
      $separator=false;
      if ($rating>= $filter)
	{
	  $separator=true;
	  print("<br><hr><br>");
	  $username = getUserName($comment_row["writer"], $link);
	  print("<TABLE width=\"100%\" bgcolor=\"#CCCCFF\"><TR><TD><FONT size=\"4\" color=\"#000000\"><B><a href=\"/PHP/ViewComment.php?comment_table=$comment_table&storyId=$storyId&commentId=".$comment_row["id"]."&filter=$filter&display=$display\">".$comment_row["subject"]."</a></B>&nbsp</FONT> (Score:".$comment_row["rating"].")</TABLE>\n");
	  print("<TABLE><TR><TD><B>Posted by ".$username." on ".$comment_row["date"]."</B><p>\n");
	  print("<TR><TD>".$comment_row["comment"]);
	  print("<TR><TD><p>[ <a href=\"/PHP/PostComment.php?comment_table=$comment_table&storyId=$storyId&parent=".$comment_row["id"]."\">Reply to this</a>&nbsp|&nbsp".
		"<a href=\"/PHP/ViewComment.php?comment_table=$comment_table&storyId=$storyId&commentId=".$comment_row["parent"]."&filter=$filter&display=$display\">Parent</a>".
		"&nbsp|&nbsp<a href=\"/PHP/ModerateComment.php?comment_table=$comment_table&commentId=".$comment_row["id"]."\">Moderate</a> ]</TABLE>\n");
	}
      if (($display > 0) &&($comment_row["childs"] > 0))
        display_follow_up($comment_row["id"], 1, $display, $filter, $link, $comment_table, $separator);
    }

    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
