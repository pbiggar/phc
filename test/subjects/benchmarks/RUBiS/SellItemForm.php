<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "SellItemForm.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();
    
    $category = $HTTP_POST_VARS['category'];
    if ($category == null)
    {
      $category = $HTTP_GET_VARS['category'];
      if ($category == null)
      {
         printError($scriptName, $startTime, "SellItemForm", "You must provide a category identifier!<br>");
         exit();
      }
    }      

    $user = $HTTP_POST_VARS['user'];
    if ($user == null)
    {
      $user = $HTTP_GET_VARS['user'];
      if ($user == null)
      {
         printError($scriptName, $startTime, "SellItemForm", "You must provide a user identifier!<br>");
         exit();
      }
    }      

    printHTMLheader("RUBiS: Sell your item");
    include("sellItemForm.html");
    print("<input type=hidden name=\"userId\" value=\"$user\">");
    print("<input type=hidden name=\"categoryId\" value=\"$category\">");

    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
