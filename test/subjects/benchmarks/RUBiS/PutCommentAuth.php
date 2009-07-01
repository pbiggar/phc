<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "PutCommentAuth.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();
    
    $itemId = $HTTP_POST_VARS['itemId'];
    if ($itemId == null)
    {
      $itemId = $HTTP_GET_VARS['itemId'];
      if ($itemId == null)
      {
         printError($scriptName, $startTime, "Authentification for comment", "You must provide an item identifier!<br>");
         exit();
      }
    }      

    $to = $HTTP_POST_VARS['to'];
    if ($to == null)
    {
      $to = $HTTP_GET_VARS['to'];
      if ($to == null)
      {
         printError($scriptName, $startTime, "Authentification for comment", "You must provide a user identifier!<br>");
         exit();
      }
    }      

    printHTMLheader("RUBiS: User authentification for comment");
    include("put_comment_auth_header.html");
    print("<input type=hidden name=\"to\" value=\"$to\">");
    print("<input type=hidden name=\"itemId\" value=\"$itemId\">");
    include("auth_footer.html");

    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
