<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <body>
    <?php
    $scriptName = "ViewItem.php";
    include("PHPprinter.php");
    $startTime = getMicroTime();
    
    $itemId = $HTTP_POST_VARS['itemId'];
    if ($itemId == null)
    {
      $itemId = $HTTP_GET_VARS['itemId'];
      if ($itemId == null)
      {
         printError($scriptName, $startTime, "Viewing item", "You must provide an item identifier!<br>");
         exit();
      }
    }
      
    getDatabaseLink($link);
    begin($link);
    $result = mysql_query("SELECT * FROM items WHERE items.id=$itemId") or die("ERROR: Query failed");
    if (mysql_num_rows($result) == 0)
      $result = mysql_query("SELECT * FROM old_items WHERE old_items.id=$itemId") or die("ERROR: Query failed");
    if (mysql_num_rows($result) == 0)
    {
      commit($link);
      die("<h3>ERROR: Sorry, but this item does not exist.</h3><br>\n");
    }

    $row = mysql_fetch_array($result);
    $maxBidResult = mysql_query("SELECT MAX(bid) AS bid FROM bids WHERE item_id=".$row["id"], $link) or die("ERROR: Max bid query failed");
    $maxBidRow = mysql_fetch_array($maxBidResult);
    $maxBid = $maxBidRow["bid"];
    if ($maxBid == 0)
    {
      $maxBid = $row["initial_price"];
      $buyNow = $row["buy_now"];
      $firstBid = "none";
    }
    else
    {
      if ($row["quantity"] > 1)
      {
        $xRes = mysql_query("SELECT bid,qty FROM bids WHERE item_id=".$row["id"]." ORDER BY bid DESC LIMIT ".$row["quantity"], $link) or die("ERROR: Quantity query failed");
        $nb = 0;
        while ($xRow = mysql_fetch_array($xRes))
        {
          $nb = $nb + $xRow["qty"];
          if ($nb > $row["quantity"])
          {
            $maxBid = $row["bid"];
            break;
          }
        }
      }
      $firstBid = $maxBid;
      $nbOfBidsResult = mysql_query("SELECT COUNT(*) AS bid FROM bids WHERE item_id=".$row["id"], $link) or die("ERROR: Nb of bids query failed");
      $nbOfBidsRow = mysql_fetch_array($nbOfBidsResult);
      $nbOfBids = $nbOfBidsRow["bid"];
      mysql_free_result($nbOfBidsResult);
    }

    printHTMLheader("RUBiS: Viewing ".$row["name"]);
    printHTMLHighlighted($row["name"]);
    print("<TABLE>\n".
          "<TR><TD>Currently<TD><b><BIG>$maxBid</BIG></b>\n");    

    // Check if the reservePrice has been met (if any)
    $reservePrice = $row["reserve_price"];
    if ($reservePrice > 0)
    {
	if ($maxBid >= $reservePrice)
	{
	  print("(The reserve price has been met)\n");
	}
	else
	{
          print("(The reserve price has NOT been met)\n");
	}
    }

    $sellerNameResult = mysql_query("SELECT users.nickname FROM users WHERE id=".$row["seller"], $link) or die("ERROR: Seller name query failed");
    $sellerNameRow = mysql_fetch_array($sellerNameResult);
    $sellerName = $sellerNameRow["nickname"];
    mysql_free_result($sellerNameResult);

    print("<TR><TD>Quantity<TD><b><BIG>".$row["quantity"]."</BIG></b>\n");
    print("<TR><TD>First bid<TD><b><BIG>$firstBid</BIG></b>\n");
    print("<TR><TD># of bids<TD><b><BIG>$nbOfBids</BIG></b> (<a href=\"/PHP/ViewBidHistory.php?itemId=".$row["id"]."\">bid history</a>)\n");
    print("<TR><TD>Seller<TD><a href=\"/PHP/ViewUserInfo.php?userId=".$row["seller"]."\">$sellerName</a> (<a href=\"/PHP/PutCommentAuth.php?to=".$row["seller"]."&itemId=".$row["id"]."\">Leave a comment on this user</a>)\n");
    print("<TR><TD>Started<TD>".$row["start_date"]."\n");
    print("<TR><TD>Ends<TD>".$row["end_date"]."\n");
    print("</TABLE>\n");

    // Can the user by this item now ?
    if ($buyNow > 0)
	print("<p><a href=\"/PHP/BuyNowAuth.php?itemId=".$row["id"]."\">".
              "<IMG SRC=\"/PHP/buy_it_now.jpg\" height=22 width=150></a>".
              "  <BIG><b>You can buy this item right now for only \$$buyNow</b></BIG><br><p>\n");

    print("<a href=\"/PHP/PutBidAuth.php?itemId=".$row["id"]."\"><IMG SRC=\"/PHP/bid_now.jpg\" height=22 width=90> on this item</a>\n");

    printHTMLHighlighted("Item description");
    print($row["description"]);
    print("<br><p>\n");

    commit($link);
    mysql_free_result($maxBidResult);
    mysql_free_result($result);
    mysql_close($link);
    
    printHTMLfooter($scriptName, $startTime);
    ?>
  </body>
</html>
