<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "BuyNowAuth.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();
    
    $itemId = $HTTP_POST_VARS['itemId'];
    if ($itemId == null)
    {
      $itemId = $HTTP_GET_VARS['itemId'];
      if ($itemId == null)
      {
         printError($scriptName, $startTime, "Authentification for buying an item", "You must provide an item identifier!<br>");
         exit();
      }
    }      

    printHTMLheader("RUBiS: User authentification for buying an item");
    include("buy_now_auth_header.html");
    print("<input type=hidden name=\"itemId\" value=\"$itemId\">");
    include("auth_footer.html");

    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
