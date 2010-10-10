<?php

  // This example is intended to show an array use
  // inside a loop that it is processed more than once
  // by the same wpa iteraction.
  //
  // The patch that fixed the bug of having the same name for
  // multiple storage nodes (rev 3316) introduced a bug leading
  // phc to  never converge when a basic block is processed more
  // than once on the same wpa iteraction. This new bug has
  // been fixed by revision 3383.

  // This is not supposed to be a real sql query, since its
  // missing the mysql_connect.
  $getCol = mysql_query("SELECT * FROM db");

  // Print the rows.
  while ($row = mysql_fetch_row($getCol))
    echo $row;

?>
