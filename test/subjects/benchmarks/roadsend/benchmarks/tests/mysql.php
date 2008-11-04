<?php


function domysql () {
    
// Connecting, selecting database
    $link = mysql_connect("dbserver", "develUser", "d3v3lpa55")
        or die("Could not connect");
    
    print "Connected successfully\n";
    
    mysql_select_db("test") or die("Could not select database");
    
// Performing SQL query
    $query = "SELECT * FROM my_table";
    
    $result = mysql_query($query) or die("Query failed");
    
// Printing results in HTML
    print "<table>\n";
    
    while ($line = mysql_fetch_array($result, MYSQL_BOTH)) {
        print "\t<tr>\n";
        foreach ($line as $col_name => $col_value) {
            print "\t\t<td>$col_name => $col_value</td>\n";
        }
        print "\t</tr>\n";
    }
    print "</table>\n";
    
// Free resultset
    mysql_free_result($result);
    
// Closing connection
//I run out of sockets with this --tim
//    mysql_close($link);
}

for ($i=0; $i<1000; $i++) {
    domysql();
}

?>