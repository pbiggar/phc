<?php

// use output buffering to use http manipulation
// POST Data from other modules
include "config.php";
$division = $_POST["division"];
$name = $_POST["name"];
$rankcorp = $_POST["rankcorp"];
$editor = $_POST["editor"];
$action = $_POST["action"];
$comment = $_POST["comment"];
$vacation = $_POST["vacation"];
$memberid = $_POST["id"];
$deleted = $_POST["deleted"];
$deldisp = $_GET["deldisp"];
$new_welcome = $_POST["new_welcome"];
$vacation = $_POST["vacation"];
$markactive = $_POST["markactive"];
$remail = $_GET["remail"];
$nname = $_GET["nname"];



if ($_POST["vacation"] == ""){
    $vacation = "0";
}
if ($_POST["deleted"] == ""){
    $deleted = "0";


}

// echo "<tr><td>".((time() - strtotime($row['DateJoined']))/(60*60*24))."</td><td>".$row['Name']."</td></tr>";




function member($p_rankcorp, $p_division, $p_lastupdate, $p_vacation, $p_canedit, $p_id, $p_name, $p_datejoined, $p_viewdata, $p_mydivision) {

    $Div = array("Null","Recruiting","Chaos Marines","Mining","Production","POS","Unassigned");
    $RankCorp = array("null","CEO","Vice CEO","Director","Officer","Pilot","Cadet");

// Coloring with sequence... next if overwrites previous... so priority is going bottom up
if($p_canedit){
$m_name = "<a href=\"edit.php?id=".$p_id."\">".$p_name."</a>";
} else {
$m_name = "<b>".$p_name."</b>";
}




$f_color = "#FFFFFF";
$m_tag = "Active";

if($p_division == $p_mydivision)
   $f_color = "#33FF66";
if($p_name == $_SERVER["HTTP_EVE_CHARNAME"])
   $f_color = "#F5B800";

if($p_division == "6" AND floor(((time() - strtotime($p_datejoined))/(60*60*24)) > 13))
   $f_color = "#CCFF00";

if(floor(((time() - strtotime($p_lastupdate))/(60*60*24)) > 9 AND $p_vacation == "0")){
   $f_color = "#CC0000";
   $m_tag = "AWOL";
}

if($p_vacation == "1")
   $m_tag = "Vacation";


$final = "<font color=\"".$f_color."\"><tr><td>".$p_datejoined."</td><td>".$m_tag."</td><td>".$m_name."</td><td>".$RankCorp[$p_rankcorp]."</td><td>".$Div[$p_division]."</td><td>".$m_ppp."</td><td>".$m_shares."</td></tr></font>";
echo "<font color=\"".$f_color."\"><tr><td>".$p_datejoined."</td><td>".$m_tag."</td><td>".$m_name."</td><td>".$RankCorp[$p_rankcorp]."</td><td>".$Div[$p_division]."</td></tr></font>";
return 1;
}

// connect to Server
include "server.php";

// get Data from Config DB
$sql = "SELECT
                welcome
            FROM
                config";
    $result = mysql_query($sql) OR die(mysql_error());

    while($row = mysql_fetch_assoc($result)) {
$welcome = $row['welcome'];
     }


// check if any data was send to index.php
if($remail !=""){
echo "<font color=\"#00FF00\">User <a href=\"evemail:".$nname."::Welcome to ".$corp."! Please read this carefully...::Dear ".$nname."!!\n\nMy Name is ".$_SERVER["HTTP_EVE_CHARNAME"]." ".$welcome."\n".$_SERVER["HTTP_EVE_CHARNAME"]."\n-".$corp." Recruiting Division (Division One) \">".$nname."</a> can now be mailed to</font><br>";
}

//config update
if ($_POST["new_welcome"] != "") {

$sql = "UPDATE
                 config
          SET
             welcome = '".$_POST["new_welcome"]."'";
              $result = mysql_query($sql) OR die(mysql_error());
}


//auf
if($name != "") {

//auf
if($action == "add"){

$sql = "SELECT
                Name
            FROM
                MembersMain
            ORDER BY
                Name ASC;";
    $exists = 0;
    $result = mysql_query($sql) OR die(mysql_error());

    while($row = mysql_fetch_assoc($result)) {
    if($row['Name'] == $name){
                    $exists++;
     }
     }
//zu
//auf
    if($exists < 1) {

    $sql = "INSERT INTO MembersMain
    (Name,Division,RankCorp,DateJoined,Comment)
     VALUES
    ('$name','$division','$rankcorp',Now(),'$comment');";
    echo "<font color=\"#00FF00\">User <a href=\"evemail:".$name."::Welcome to ".$corp."! Please read this carefully...::Dear ".$name."!!\n\nMy Name is ".$_SERVER["HTTP_EVE_CHARNAME"]." ".$welcome."\n".$_SERVER["HTTP_EVE_CHARNAME"]."\n-".$corp." Recruiting Division (Division One) \">".$name."</a> successfully added to DB</font><br>";

    } else {
    $sql = "SELECT
                Name
            FROM
                MembersMain
            ORDER BY
                Name ASC;";
    echo "<font color=\"#FF0000\">User already exists in DB, cannot add user to DB<br></font>";
    }
//zu
}
//zu

if($action == ""){

if($markactive == ""){
  $sql = "UPDATE
                 MembersMain
          SET
              Name = '".$name."',
              Division = '".$division."',
              RankCorp = '".$rankcorp."',
              Vacation = '".$vacation."',
              Comment = '".$comment."',
              Deleted = '".$deleted."'
          WHERE
              MemberID = '".$memberid."'";
   } else {
			  $sql = "UPDATE
                 MembersMain
          SET
              Name = '".$name."',
              Division = '".$division."',
              RankCorp = '".$rankcorp."',
              Vacation = '".$vacation."',
              Comment = '".$comment."',
              LastUpdate = Now(),
              Deleted = '".$deleted."'
          WHERE
              MemberID = '".$memberid."'";

				}
}
              $result = mysql_query($sql) OR die(mysql_error());
}





echo("<HTML><BODY>");

//echo $_SERVER["SERVER_NAME"].$_SERVER['REQUEST_URI']."<br>";
// for further use....
// TRUST CHECK
    function Check2()
	{
		$returnValue = false;
		$pattern = "/^EVE-minibrowser.*\/([0-9]+\.[0-9]+).*$/";
		if (preg_match($pattern, $_SERVER['HTTP_USER_AGENT'], $matchs))
			if ($matchs[1] >= 2.0)
				$returnValue = true;

		if (!$returnValue){
			echo "This page is IGB only and requires ".$corpURL." to be in the trusted websites in order to show all content. If you do not have this site on trusted, some content will not be displayed correctly";
     }
		return $returnValue;
}


    function get_trust() {
      global $ingame, $trusted, $pilotname;
      $browser = $_SERVER["HTTP_USER_AGENT"];


        if (Check2()) {

         // check for trust
           if ($_SERVER["HTTP_EVE_TRUSTED"]=='no') {
            // request trust from client through headers


              header("eve.trustMe:".$corpURL."::This page requires ".$corpURL." to be in the trusted websites in order to show all content. If you do not have this site on trusted, some content will not be displayed correctly!");
              $trusted = false;
           } else {





              $trusted = true;
            // Is in Chaos Faction?
if($_SERVER["HTTP_EVE_corp"] != $corp){
                                 echo "This Data is restricted to members of ".$corp;
                                 } else {

// Identify User
$sql = "SELECT
                MemberID,
                Name,
                Division,
                RankCorp
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
}





if($myname == "") {
 echo "<b><center>You have not been added to the DB yet, please contact a Division 1 Officer!</center></b>";
} else {

// Start the table and create the array with Corprelated stuff....
if($myrankcorp < "3")
{
$canedit = true;
echo "<form action=\"add.php\" method=\"post\" target=\"_self\">";
echo "<input type=\"submit\" value=\" Add new Person to DB \"></form>";
echo "<form action=\"member.php?deldisp=only\" method=\"post\" target=\"_self\">";
echo "<input type=\"submit\" value=\" Deleted Only \"></form>";
echo "<form action=\"member.php?deldisp=no\" method=\"post\" target=\"_self\">";
echo "<input type=\"submit\" value=\" Active Only \"></form>";
echo "<form action=\"member.php?deldisp=merge\" method=\"post\" target=\"_self\">";
echo "<input type=\"submit\" value=\" Merged Display \"></form><br>";
} else {
if($mydivision == "1" AND $myrankcorp < "5")
{
$canedit = true;
echo "<form action=\"add.php\" method=\"post\" target=\"_self\">";
echo "<input type=\"submit\" value=\" Add new Person to DB \"></form>";
echo "<form action=\"member.php?deldisp=only\" method=\"post\" target=\"_self\">";
echo "<input type=\"submit\" value=\" Deleted Only \"></form>";
echo "<form action=\"member.php?deldisp=no\" method=\"post\" target=\"_self\">";
echo "<input type=\"submit\" value=\" Active Only \"></form>";
echo "<form action=\"member.php?deldisp=merge\" method=\"post\" target=\"_self\">";
echo "<input type=\"submit\" value=\" Merged Display \"></form><br>";
}
}


echo "<table width=\"100%\">";
echo "<colgroup>";
echo "<col width=\"9%\">";
echo "<col width=\"7%\">";
echo "<col width=\"15%\">";
echo "<col width=\"7%\">";
echo "<col width=\"10%\">";
echo "<col width=\"*\">";
echo "</colgroup>";

//Initiate Header Row
echo "<tr><td><a href=\"member.php?sort=DateJoined\">Date Joined</a></td><td><a href=\"member.php?sort=Vacation\">FLAG</a></td><td><b><a href=\"member.php?sort=Name\">Name</a></b></td><td><a href=\"member.php?sort=RankCorp\">RankCorp</a></td><td><a href=\"member.php?sort=Division\">Division</a></td></tr>";



//auf

if($_GET["deldisp"] != "") {

if($_GET["deldisp"] == "only") {

//sort
if($_GET["sort"] == ""){
$sql = "SELECT
                MemberID,
                Name,
                Division,
                LastUpdate,
                DateJoined,
                Vacation,
                RankCorp,
                Deleted
            FROM
                MembersMain
            WHERE
                Deleted = '1'
            ORDER BY
                Name ASC;";
} else {
$sql = "SELECT
                MemberID,
                Name,
                Division,
                LastUpdate,
                DateJoined,
                Vacation,
                RankCorp,
                Deleted
            FROM
                MembersMain
            WHERE
                Deleted = '1'
            ORDER BY
                ".$_GET["sort"]." ASC,
                Name ASC;";
}

}

if($_GET["deldisp"] == "merge") {
if($_GET["sort"] == ""){
$sql = "SELECT
                MemberID,
                Name,
                Division,
                DateJoined,
                LastUpdate,
                Vacation,
                RankCorp,
                Deleted
            FROM
                MembersMain
            ORDER BY
                Name ASC;";
} else {
$sql = "SELECT
                MemberID,
                Name,
                Division,
                LastUpdate,
                DateJoined,
                Vacation,
                RankCorp,
                Deleted
            FROM
                MembersMain
            ORDER BY
                ".$_GET["sort"]." ASC,
                Name ASC;";
}

}

if($_GET["deldisp"] == "no") {
if($_GET["sort"] == ""){
$sql = "SELECT
                MemberID,
                Name,
                Division,
                LastUpdate,
                DateJoined,
                Vacation,
                RankCorp,
                Deleted
            FROM
                MembersMain
            WHERE
                Deleted = '0'
            ORDER BY
                Name ASC;";
} else {
$sql = "SELECT
                MemberID,
                Name,
                Division,
                DateJoined,
                Vacation,
                RankCorp,
                Deleted,
                LastUpdate
            FROM
                MembersMain
            WHERE
                Deleted = '0'
            ORDER BY
                ".$_GET["sort"]." ASC,
                Name ASC;";
}

}

} else {

if($_GET["sort"] == ""){
$sql = "SELECT
                MemberID,
                Name,
                Division,
                DateJoined,
                LastUpdate,
                Vacation,
                RankCorp,
                Deleted
            FROM
                MembersMain
            WHERE
                Deleted = '0'
            ORDER BY
                Name ASC;";
} else {
$sql = "SELECT
                MemberID,
                Name,
                Division,
                DateJoined,
                Vacation,
                RankCorp,
                Deleted,
                LastUpdate
            FROM
                MembersMain
            WHERE
                Deleted = '0'
            ORDER BY
                ".$_GET["sort"]." ASC,
                Name ASC;";

}

}
$Div = array("Null","Recruiting","Chaos Marines","Mining","Production","POS","Unassigned");
$RankCorp = array("null","CEO","Vice CEO","Director","Officer","Pilot","Cadet");
$statMemberCount = 0;
// This is where the part starts where the data is filtered and displayed according to roles and flags...

    $result = mysql_query($sql) OR die(mysql_error());
    while($row = mysql_fetch_assoc($result)) {

//Statistics

$statMemberCount = $statMemberCount + 1;

if($myrankcorp < "4"){
 $viewdata = true;
 } else {
 if($mydivision == $row['Division'] and $myrankcorp == "4") {
 $viewdata = true;
 } else {
 $viewdata = false;
 }
 }

member($row['RankCorp'], $row['Division'], $row['LastUpdate'], $row['Vacation'], $canedit, $row['MemberID'], $row['Name'], $row['DateJoined'],$viewdata, $mydivision);
//Display

}

        echo "</table><br>Total Members: ".$statMemberCount."<br><hr>Legend:";
        echo "<br><font color=\"#F5B800\">Self</font><br><font color=\"#33FF66\">My Division</font><br><font color=\"#CCFF00\">Unassigned after 14Days</font><br><font color=\"#CC0000\">Inactive for 10Days</font><hr>";
}
}
}
}
}

 get_trust();
 echo "<br><br><center><font size=\"4\"> Member Infopage ©2006 SentryRaven. DataBase by Adunh Slavy.</font><br><b><a href=\"features.html\" target=\"_parent\">Version v1.6 STABLE</a></b></center>";
 echo("</BODY></HTML>");






// and flush out the buffer content
ob_end_flush();
?>
