<?php
echo("<HTML><BODY>");
$Div = array("Null","Recruiting","Security","Mining","Production","POS","Unassigned");
$RankCorp = array("null","CEO","Vice CEO","Director","Officer","Pilot","Cadet");

        echo "<form action=\"member.php\" method=\"post\" target=\"_self\">";
        echo "<input type=\"submit\" value=\" Add Member to DB \"><br>";
        echo "<input type=\"checkbox\" name=\"action\" type=\"hidden\" value=\"add\" checked>";
        //Name
        echo "<select size=\"1\"><option>Name</option></select><input name=\"name\" type=\"text\" size=\"15\" maxlength=\"60\" value=\"Insert Name\"><br>";

        //RankCorp
        echo "<select name=\"rankcorp\" size=\"6\">";
    for($count=1;$count<7;$count++) {
    if ($count == "6") {
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
    if ($count == "6" ) {
                                     echo "<option value=\"".$count."\" selected>".$Div[$count]."</option>";
                                  }
                                  else
                                  {
                                     echo "<option value=\"".$count."\">".$Div[$count]."</option>";
                                  }
                                  }
        echo "</select><br>";
        echo "<textarea name=\"comment\" cols=\"25\" rows=\"10\">Please insert Comments here</textarea><br>";
        echo "</form>";
        echo "</body></html>";
?>
