
<?php
/*  
 * DVD Store Purchase PHP Page - dspurchase.php
 *
 * Copyright (C) 2005 Dell, Inc. <dave_jaffe@dell.com> and <todd_muirhead@dell.com>
 *
 * Handles purchase of DVDs for MySQL DVD Store database
 * Checks inventories, adds records to ORDERS and ORDERLINES tables transactionally
 *
 * Last Updated 6/7/05
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/ 

include("dscommon.inc");

ds_html_header("DVD Store Purchase Page");

$confirmpurchase = $_REQUEST["confirmpurchase"];
$item = $_REQUEST["item"];
$quan = $_REQUEST["quan"];
$drop = $_REQUEST["drop"];
$customerid = $_REQUEST["customerid"];

if (empty($confirmpurchase))
  {
  echo "<H2>Selected Items: specify quantity desired; click Purchase when finished</H2>\n";
  echo "<BR>\n";
  echo "<FORM ACTION='./dspurchase.php' METHOD='GET'>\n";
  echo "<TABLE border=2>\n";
  echo "<TR>\n";
  echo "<TH>Item</TH>\n";
  echo "<TH>Quantity</TH>\n";
  echo "<TH>Title</TH>\n";
  echo "<TH>Actor</TH>\n";
  echo "<TH>Price</TH>\n";
  echo "<TH>Remove From Order?</TH>\n";
  echo "</TR>\n";

  if (!($link_id = mysqli_connect())) die(mysqli_connect_error());

  $j = 0;
  for ($i=0; $i<count($item); $i++)
    {
    if (empty($drop) || !in_array($i, $drop))
      {
      ++$j;
      $purchase_query = "select PROD_ID, TITLE, ACTOR, PRICE from DS2.PRODUCTS where PROD_ID=$item[$i]";
      mysqli_real_query($link_id, $purchase_query);
      $purchase_result = mysqli_store_result($link_id);
      $purchase_result_row = mysqli_fetch_row($purchase_result);
      mysqli_free_result($purchase_result);
      echo " <TR>";
      echo "<TD ALIGN=CENTER>$j</TD>";
      echo "<INPUT NAME='item[]' TYPE='HIDDEN' VALUE='$purchase_result_row[0]'>";
      echo "<TD><INPUT NAME='quan[]' TYPE='TEXT' SIZE=10 VALUE=" . max(1,$quan[$i]) . "></TD>";
      echo "<TD>$purchase_result_row[1]</TD>";
      echo "<TD>$purchase_result_row[2]</TD>";
      $amt = sprintf("$%.2f", $purchase_result_row[3]);
      echo "<TD ALIGN=RIGHT>$amt</TD>";
      echo "<TD ALIGN=CENTER><INPUT NAME='drop[]' TYPE=CHECKBOX VALUE=$i></TD>";
      echo "</TR>\n";
      $netamount = $netamount + max(1,$quan[$i])*$purchase_result_row[3];
      }
    }      

  $taxpct = 8.25;
  $taxamount = $netamount * $taxpct/100.0;
  $totalamount = $taxamount + $netamount;
  $amt = sprintf("$%.2f", $netamount);
  echo "<TR><TD></TD><TD></TD><TD></TD><TD>Subtotal</TD><TD ALIGN=RIGHT>$amt</TD></TR>\n";
  $amt = sprintf("$%.2f", $taxamount);
  echo "<TR><TD></TD><TD></TD><TD></TD><TD>Tax ($taxpct%)</TD><TD ALIGN=RIGHT>$amt</TD></TR>\n";
  $amt = sprintf("$%.2f", $totalamount);
  echo "<TR><TD></TD><TD></TD><TD></TD><TD>Total</TD><TD ALIGN=RIGHT>$amt</TD></TR>\n";
  echo "</TABLE><BR>\n";
    
  echo "<INPUT TYPE=HIDDEN NAME=customerid VALUE='$customerid'>\n";

  echo "<INPUT TYPE=SUBMIT VALUE='Update and Recalculate Total'>\n";
  echo "</FORM><BR>\n";

  echo "<FORM ACTION='./dspurchase.php' METHOD='GET'>\n";
  echo "<INPUT TYPE=HIDDEN NAME=confirmpurchase VALUE='yes'>\n";
  echo "<INPUT TYPE=HIDDEN NAME=customerid VALUE='$customerid'>\n";
  for ($i=0; $i<count($item); $i++)
    {
    if (empty($drop) || !in_array($i, $drop))
      {
      echo "<INPUT NAME='item[]' TYPE='HIDDEN' VALUE='$item[$i]'>";
      echo "<INPUT NAME='quan[]' TYPE='HIDDEN' VALUE='$quan[$i]'>\n";
      }
    }      
  echo "<INPUT TYPE=SUBMIT VALUE='Purchase'>\n";
  }
else  // confirmpurchase=yes  => update ORDERS, ORDERLINES, INVENTORY and CUST_HIST table
  {
  if (!($link_id = mysqli_connect())) die(mysqli_connect_error());
 
  echo "<H2>Purchase complete</H2>\n";
  echo "<TABLE border=2>";
  echo "<TR>";
  echo "<TH>Item</TH>";
  echo "<TH>Quantity</TH>";
  echo "<TH>Title</TH>";
  echo "<TH>Actor</TH>";
  echo "<TH>Price</TH>";
  echo "</TR>\n";

  for ($i=0; $i<count($item); $i++)
    {
    $j = $i + 1;
    $quan[$i] = max(1,$quan[$i]);
    $purchase_query = "select PROD_ID, TITLE, ACTOR, PRICE from DS2.PRODUCTS where PROD_ID=$item[$i]";
    mysqli_real_query($link_id, $purchase_query);
    $purchase_result = mysqli_store_result($link_id);
    $purchase_result_row = mysqli_fetch_row($purchase_result);
    mysqli_free_result($purchase_result);
    echo " <TR>";
    echo "<TD ALIGN=CENTER>$j</TD>";
    echo "<INPUT NAME='item[]' TYPE=HIDDEN VALUE='$purchase_result_row[0]'>";
    echo "<TD><INPUT NAME='quan[]' TYPE=TEXT SIZE=10 VALUE=$quan[$i]></TD>";
    echo "<TD>$purchase_result_row[1]</TD>";
    echo "<TD>$purchase_result_row[2]</TD>";
    $amt = sprintf("$%.2f", $purchase_result_row[3]);
    echo "<TD ALIGN=RIGHT>$amt</TD>";
    echo "</TR>\n";
    $netamount = $netamount + $quan[$i]*$purchase_result_row[3];
    }

  $taxpct = 8.25;
  $taxamount = $netamount * $taxpct/100.0;
  $totalamount = $taxamount + $netamount;
  $netamount_fmt = sprintf("%.2f", $netamount);
  echo "<TR><TD></TD><TD></TD><TD></TD><TD>Subtotal</TD><TD ALIGN=RIGHT>$" . $netamount_fmt . "</TD></TR>\n";
  $taxamount_fmt = sprintf("%.2f", $taxamount);
  echo "<TR><TD></TD><TD></TD><TD></TD><TD>Tax ($taxpct%)</TD><TD ALIGN=RIGHT>$" . $taxamount_fmt . "</TD></TR>\n";
  $totalamount_fmt = sprintf("%.2f", $totalamount);
  echo "<TR><TD></TD><TD></TD><TD></TD><TD>Total</TD><TD ALIGN=RIGHT>$" . $totalamount_fmt . "</TD></TR>\n";
  echo "</TABLE><BR>\n";

  $currentdate = date("Y-m-d");

  // Start transaction - open separate connection for inserts that belong to transaction
  if (!($link_id_trans = mysqli_connect())) die(mysqli_connect_error());
  $command_result = mysqli_autocommit($link_id_trans, FALSE);
  $purchase_insertorder_query = "INSERT into DS2.ORDERS (ORDERDATE, CUSTOMERID, NETAMOUNT, TAX, TOTALAMOUNT)" .
    " VALUES ( '$currentdate',$customerid,$netamount_fmt,$taxamount_fmt,$totalamount_fmt);";
  $purchase_insertorder_result = mysqli_real_query($link_id_trans, $purchase_insertorder_query);
  $orderid = mysqli_insert_id($link_id_trans);

  // To do: check $orderid and handle error if = 0

  // loop through items to be purchased, check inventory,  and make inserts into ORDERLINES and CUST_HIST tables     

    $success = true;
    $orderlines_insert = "INSERT into DS2.ORDERLINES (ORDERLINEID, ORDERID, PROD_ID, QUANTITY, ORDERDATE) VALUES "; 
    $cust_hist_insert= "INSERT into DS2.CUST_HIST (CUSTOMERID, ORDERID, PROD_ID) VALUES ";
    for ($i=0; $i < count($item); $i++)
      {
      $j = $i+1;
      $query = "SELECT QUAN_IN_STOCK, SALES FROM DS2.INVENTORY WHERE PROD_ID=$item[$i]";
      mysqli_real_query($link_id, $query);
      $result = mysqli_store_result($link_id);
      $result_row = mysqli_fetch_row($result);
      mysqli_free_result($result);
      $curr_quan = $result_row[0];
      $curr_sales = $result_row[1];
      $new_quan = $curr_quan - $quan[$i];
      $new_sales = $curr_sales + $quan[$i];
      if ($new_quan < 0)
        {
        echo "Insufficient quantity for prod $item[$i]\n";
        $success = false;
        }
      else   
        {
        $query = "UPDATE DS2.INVENTORY SET QUAN_IN_STOCK=$new_quan, SALES=$new_sales WHERE PROD_ID=$item[$i];";
        $result = mysqli_real_query($link_id_trans, $query);
        }

      $orderlines_insert = $orderlines_insert . "($j, $orderid, $item[$i], $quan[$i], '$currentdate'),";
      $cust_hist_insert = $cust_hist_insert . "($customerid, $orderid, $item[$i]),";
      } // End of for $i < count($item)

    $orderlines_insert[strlen($orderlines_insert)-1] = ";";
    $cust_hist_insert[strlen($cust_hist_insert)-1] = ";";

    if (!mysqli_real_query($link_id_trans, $orderlines_insert))
      {
      echo "Insert into ORDERLINES table failed:  query= $orderlines_insert\n";
      $success = false;
      }

    if ($success) mysqli_commit($link_id_trans);
    else  mysqli_rollback($link_id_trans);
    mysqli_close($link_id_trans);

    // Do CUST_HIST insert outside of transaction for performance
    mysqli_real_query($link_id, $cust_hist_insert);

    if ($success)
      {
      // To Do: verify credit card purchase against a second database
      $cctypes = array("MasterCard", "Visa", "Discover", "Amex", "Dell Preferred");

      $cc_query = "select CREDITCARDTYPE, CREDITCARD, CREDITCARDEXPIRATION from DS2.CUSTOMERS where CUSTOMERID=$customerid";
      mysqli_real_query($link_id, $cc_query);
      $cc_result = mysqli_store_result($link_id);
      $cc_result_row = mysqli_fetch_row($cc_result);
      mysqli_free_result($cc_result);
      echo "<H3>$" . $totalamount_fmt . " charged to credit card $cc_result_row[1] " .
        "(" .  $cctypes[$cc_result_row[0]-1] . "), expiration $cc_result_row[2]</H3><BR>\n";
      echo "<H2>Order Completed Successfully --- ORDER NUMBER:  $orderid</H2><BR>\n";
      }
    else
      {
      echo "<H3>Insufficient stock - order not processed</H3>\n";
      }
  } 

ds_html_footer();
mysqli_close($link_id);
?>
