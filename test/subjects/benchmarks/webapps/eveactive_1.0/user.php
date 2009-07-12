<?php
// Set vacation
include "config.php";



$vacedit = $_POST['vacedit'];
if($_POST['vacedit'] != "") {
$sql = "UPDATE
              MembersMain
          SET
              Vacation = '".$vacedit."'
          WHERE
              Name = '".$_SERVER["HTTP_EVE_CHARNAME"]."'";
$result = mysql_query($sql) OR die(mysql_error());

$sql = "SELECT
                MemberID,
                Name,
                Division,
                RankCorp,
                Vacation
            FROM
                MembersMain
            WHERE
                Name = '".$_SERVER["HTTP_EVE_CHARNAME"]."'";
}

// Identify User
$sql = "SELECT
                MemberID,
                Name,
                Division,
                RankCorp,
                Vacation
            FROM
                MembersMain
            WHERE
                Name = '".$_SERVER["HTTP_EVE_CHARNAME"]."'";
$result = mysql_query($sql) OR die(mysql_error());

while($row = mysql_fetch_assoc($result)) {
$myname = $row['Name'];
$mydivision = $row['Division'];
$myrankcorp = $row['RankCorp'];
$myid = $row['MemberID'];
$myvacation = $row['Vacation'];
}


$Div = array("Null","Recruiting","Chaos Marines","Mining","Production","POS","Unassigned");
$RankCorp = array("null","CEO","Vice CEO","Director","Officer","Pilot","Cadet");

// Is in Chaos Faction?
   if($_SERVER["HTTP_EVE_CORPNAME"] != "Chaos Faction"){
// Public User
echo "<table border=\"0\" width=\"100%\">
  <tr>
    <td rowspan=\"3\"><IMG SRC=\"portrait:".$_SERVER["HTTP_EVE_CHARID"]."\" SIZE=\"64\"></td>
    <td width=\"50%\">".$_SERVER["HTTP_EVE_CHARNAME"]."</td>
  </tr>
  <tr>
    <td width=\"50%\">".$_SERVER["HTTP_EVE_CORPNAME"]."</td>
  </tr>
  <tr>
    <td width=\"50%\">&nbsp;</td>
  </tr>
</table><hr><br>";
// Basic Links
echo "<center><a href=\"index.php\">Index</a> | <a href=\"http://myeve.eve-online.com/mb/news.asp\">Eve-Online Latest News</a></center><br><hr>";

                                 } else {
// Corp Member

$sql = "UPDATE
                 MembersMain
          SET
              LastUpdate = Now()
          WHERE
              Name = '".$_SERVER["HTTP_EVE_CHARNAME"]."'";
$result = mysql_query($sql) OR die(mysql_error());
if($mydivision == "" and $myrankcorp == ""){
 $myrankcorp == "6";
 $mydivision == "6";
 }



echo "<table border=\"0\" width=\"100%\">
  <tr>
    <td rowspan=\"3\"><IMG SRC=\"portrait:".$_SERVER["HTTP_EVE_CHARID"]."\" SIZE=\"64\"></td>
    <td width=\"50%\">".$_SERVER["HTTP_EVE_CHARNAME"]."</td>
  </tr>
  <tr>
    <td width=\"50%\">".$_SERVER["HTTP_EVE_CORPNAME"]."</td>
  </tr>
  <tr>
    <td width=\"50%\">".$Div[$mydivision]." || ".$RankCorp[$myrankcorp]."</td>
  </tr>
</table><br>";
if($myid != "")
{
if($myvacation == "1"){
echo "<form action=\"index.php\" method=\"post\" target=\"_self\"><input name=\"vacedit\" type=\"hidden\" value=\"0\"><input type=\"submit\" value=\"RESET VACATION\"><br></form>";
} else {
echo "<form action=\"index.php\" method=\"post\" target=\"_self\"><input name=\"vacedit\" type=\"hidden\" value=\"1\"><input type=\"submit\" value=\"SET VACATION\"><br></form>";
}


}

echo "<hr><br>";
//Corp Output
echo "<center><a href=\"member.php\">Complete Memberlist</a> | <a href=\"http://eve.podzone.net\">Max Kentarii's Linklist</a></center><br>";

// Basic Links
echo "<center><a href=\"http://myeve.eve-online.com/mb/news.asp\">Eve-Online Latest News</a></center><br>";


}
// end corp check
?>
