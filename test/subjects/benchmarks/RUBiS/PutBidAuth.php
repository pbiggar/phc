<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "PutBidAuth.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();
    
    $itemId = $HTTP_POST_VARS['itemId'];
    if ($itemId == null)
    {
      $itemId = $HTTP_GET_VARS['itemId'];
      if ($itemId == null)
      {
         printError($scriptName, $startTime, "Authentification for bidding", "You must provide an item identifier!<br>");
         exit();
      }
    }      

    printHTMLheader("RUBiS: User authentification for bidding");
    include("put_bid_auth_header.html");
    print("<input type=hidden name=\"itemId\" value=\"$itemId\">");
    include("auth_footer.html");

    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
