<?php
$page = $_GET['page'];



include "config.php";

include "server.php";
include "config.php";

function getName($ID){

$sql = "SELECT
                MemberID,
                Name
            FROM
                MembersMain
            WHERE
                MemberID = '".$ID."'";
$result = mysql_query($sql) OR die(mysql_error());

while($row = mysql_fetch_assoc($result)) {
return $row['Name'];
}

}

echo("<HTML><title>".$corp." Member Pages</title><body>");

//echo $_SERVER["SERVER_NAME"].$_SERVER['REQUEST_URI']."<br>";
// for further use....
// TRUST CHECK

    function get_trust() {
      global $ingame, $trusted, $pilotname;
      $browser = $_SERVER["HTTP_USER_AGENT"];


        if (Check()) {

         // check for trust
           if ($_SERVER["HTTP_EVE_TRUSTED"]=='no') {
            // request trust from client through headers


              header("eve.trustMe:".$corpURL."::This page requires ".$corpURL." to be in the trusted websites in order to show all content. If you do not have this site on trusted, some content will not be displayed correctly!");
              $trusted = false;
           } else {

// Begin INGAME output

                                $trusted = true;
// Is in Chaos Faction?
   if($_SERVER["HTTP_EVE_CORPNAME"] != $corp){

// Public Content

include "user.php";



echo "</body>";
                                 } else {
// Corp Content Only

include "user.php";
echo "</body>";

}
// end corp check
}
// end trust check
}
// end if check()
}
// end Function GetTrust




get_trust();
echo("</HTML>");






// and flush out the buffer content
ob_end_flush();
?>
