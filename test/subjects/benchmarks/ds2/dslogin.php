
<?php
/*  
 * DVD Store Login PHP Page - dslogin.php
 *
 * Copyright (C) 2005 Dell, Inc. <dave_jaffe@dell.com> and <todd_muirhead@dell.com>
 *
 * Login to MySQL DVD store 
 *
 * Last Updated 7/3/05
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

ds_html_header("DVD Store Login Page");

$username = $_REQUEST["username"];
$password = $_REQUEST["password"];

if (!(empty($username)))
  {
  if (!($link_id = mysqli_connect())) die(mysqli_connect_error());
  $query = "select CUSTOMERID FROM DS2.CUSTOMERS where USERNAME='$username' and PASSWORD='$password';";
  $result = mysqli_query($link_id, $query);
  if (mysqli_num_rows($result) > 0)
    {
    $row = mysqli_fetch_row($result);
    $customerid = $row[0];
    mysqli_free_result($result);
    echo "<H2>Welcome to the DVD Store - Click below to begin shopping</H2>\n";
    $query = "SELECT DS2.PRODUCTS.TITLE, DS2.PRODUCTS.ACTOR, DS2.PRODUCTS.COMMON_PROD_ID" .
             " FROM DS2.CUST_HIST INNER JOIN DS2.PRODUCTS ON DS2.CUST_HIST.PROD_ID = DS2.PRODUCTS.PROD_ID" .
             " WHERE DS2.CUST_HIST.CUSTOMERID =" . $customerid . " ORDER BY ORDERID DESC, TITLE ASC LIMIT 10;";
    mysqli_real_query($link_id, $query);
    $result = mysqli_store_result($link_id);

    if (mysqli_num_rows($result) > 0)
      {
      echo "<H3>Your previous purchases:</H3>\n";
      echo "<TABLE border=2>\n";
      echo "<TR>\n";
      echo "<TH>Title</TH>\n";
      echo "<TH>Actor</TH>\n";
      echo "<TH>People who liked this DVD also liked</TH>\n";
      echo "</TR>\n";

      while ($result_row = mysqli_fetch_row($result))
        {
        $query2 = "select TITLE from DS2.PRODUCTS where PROD_ID =" . $result_row[2] . ";";
        mysqli_real_query($link_id, $query2);
        $result2 = mysqli_store_result($link_id);
        $row2 = mysqli_fetch_row($result2);
        echo " <TR>\n";
        echo "<TD>$result_row[0]</TD>";
        echo "<TD>$result_row[1]</TD>";
        echo "<TD>$row2[0]</TD>";
        echo "</TR>\n";
        }
      echo "</TABLE>\n";
      echo "<BR>\n";
      }
    
    echo "<FORM ACTION=\"./dsbrowse.php\" METHOD=GET>\n";
    echo "<INPUT TYPE=HIDDEN NAME=customerid VALUE=$customerid>\n";
    echo "<INPUT TYPE=SUBMIT VALUE=\"Start Shopping\">\n";
    mysqli_free_result($result);
    }
  else 
    {
    echo "<H2>Username/password incorrect. Please re-enter your username and password</H2>\n";
    echo "<FORM  ACTION=\"./dslogin.php\" METHOD=GET>\n";
    echo "Username <INPUT TYPE=TEXT NAME=\"username\" VALUE=$username SIZE=16 MAXLENGTH=24>\n";
    echo <<<EOT
Password <INPUT TYPE=PASSWORD NAME="password" SIZE=16 MAXLENGTH=24>
<INPUT TYPE=SUBMIT VALUE="Login"> 
</FORM>
<H2>New customer? Please click New Customer</H2>
<FORM  ACTION="./dsnewcustomer.php" METHOD=GET >
<INPUT TYPE=SUBMIT VALUE="New Customer"> 
</FORM>
EOT;
    }
  }
else
  {
  echo <<<EOT
<H2>Returning customer? Please enter your username and password</H2>
<FORM  ACTION="./dslogin.php" METHOD=GET >
Username <INPUT TYPE=TEXT NAME="username" SIZE=16 MAXLENGTH=24>
Password <INPUT TYPE=PASSWORD NAME="password" SIZE=16 MAXLENGTH=24>
<INPUT TYPE=SUBMIT VALUE="Login"> 
</FORM>
<H2>New customer? Please click New Customer</H2>
<FORM  ACTION="./dsnewcustomer.php" METHOD=GET >
<INPUT TYPE=SUBMIT VALUE="New Customer"> 
</FORM>
EOT;
  }
ds_html_footer();
?>
