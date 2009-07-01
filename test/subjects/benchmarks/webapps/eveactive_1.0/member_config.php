<?php
include "server.php";
// get Data from Config DB
$sql = "SELECT
                welcome
            FROM
                config";
    $result = mysql_query($sql) OR die(mysql_error());

    while($row = mysql_fetch_assoc($result)) {
$welcome = $row['welcome'];


echo "<html><body>";
echo "<form action=\"member.php\" method=\"post\" target=\"_self\">";

        echo "<input type=\"submit\" value=\" Update Config \"><br>";
        echo "<textarea name=\"new_welcome\" cols=\"60\" rows=\"4\">//Harcoded\nDear {Username}!! \n\n} My Name is {autoinsertname}...\n//Hardcoded </textarea><br>";
        echo "<textarea name=\"new_welcome\" cols=\"60\" rows=\"20\">".$welcome."</textarea><br>";


        echo "</form>";
}
        echo "</body></html>";
