<?php
$member = $_GET['id'];
echo("<HTML><BODY>");

include "server.php";
        echo "<table>";
$Div = array("Null","Recruiting","Security","Mining","Production","POS","Unassigned");
$RankCorp = array("null","CEO","Vice CEO","Director","Officer","Pilot","Cadet");
$sql = "SELECT
                MemberID,
                Name,
                Division,
                DateJoined,
                RankCorp,
                Vacation,
                Comment,
                Deleted
            FROM
                MembersMain
            WHERE
                MemberID='".$member."'";

    // Das am Anfang immer ein paar Leerzeichen stehen
    // ist für MySQL uninteressant.
    // Hier würde sich sogar die Heredoc schreibweise
    // eignen

    //echo "<tr><td>Joined</td><td><b>Name</b></td><td>Division</td></tr>";
    $result = mysql_query($sql) OR die(mysql_error());
    while($row = mysql_fetch_assoc($result)) {

        echo "<form action=\"member.php\" method=\"post\" target=\"_self\">";
        echo "<input type=\"submit\" value=\" Update Member Details \"><br>";
        echo "<input name=\"id\" type=\"hidden\" value=\"".$row['MemberID']."\"><br>";
        //Name
        if($row['Vacation'] == "0") {
           echo "<select size=\"1\"><option>Vacation?</option></select><input type=\"checkbox\" name=\"vacation\" value=\"1\"><br>";
        } else {
           echo "<select size=\"1\"><option>Vacation?</option></select><input type=\"checkbox\" checked name=\"vacation\" value=\"1\"><br>";
        }
        echo "<select size=\"1\"><option>Mark as Active?</option></select><input type=\"checkbox\" name=\"markactive\" value=\"1\"><br>";
        echo "<select size=\"1\"><option>Name</option></select><input name=\"name\" type=\"text\" size=\"18\" maxlength=\"60\" value=\"".$row['Name']."\"><br><br>";

        //RankCorp
        echo "<select name=\"rankcorp\" size=\"6\">";
    for($count=1;$count<7;$count++) {
    if ($count == $row['RankCorp']) {
                                     echo "<option value=\"".$count."\" selected>".$RankCorp[$count]."</option>";
                                  }
                                  else
                                  {
                                     echo "<option value=\"".$count."\">".$RankCorp[$count]."</option>";
                                  }
                                  }
     echo "</select>";

    //Division
    echo "<select name=\"division\" size=\"6\">";
        for($count=1;$count<7;$count++) {
    if ($Div[$count] != "Null") {
    if ($count == $row['Division'] ) {
                                     echo "<option value=\"".$count."\" selected>".$Div[$count]."</option>";
                                  }
                                  else
                                  {
                                     echo "<option value=\"".$count."\">".$Div[$count]."</option>";
                                  }
                                  }
                                  }
        echo "</select><br>";
        echo "<textarea name=\"comment\" cols=\"25\" rows=\"10\">".$row['Comment']."</textarea><br>";

        if($row['Deleted'] != 0) {
        echo "<input type=\"checkbox\" name=\"deleted\" value=\"1\" checked>";
        echo "<select size=\"1\"><option>Delete Member?</option></select><br>";
        }else{
        echo "<input type=\"checkbox\" name=\"deleted\" value=\"1\">";
        echo "<select size=\"1\"><option>Delete Member?</option></select><br>";
        }
        echo "</form>";
    }
        echo "</table>";
        echo "</body></html>";
?>
