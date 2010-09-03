ds2_mysql_web_php5_readme.txt

php5 interface to the MySQL DVD Store database
Requires php5/MySQL5
Files:

dscommon.inc
dspurchase.php
dsnewcustomer.php      - new customer page with stored procedure call
dsnewcustomer.php.sp   - new customer page with stored procedure call
dsnewcustomer.php.nosp - new customer page without stored procedure call
dsbrowse.php
dslogin.php

The driver programs expect these files in a virtual directory "ds2".
In your web server you either need to create a virtual directory that points
to this directory or copy these files to the appropriate directory (eg /var/www/html/ds2)

Note: to use previous versions of MySQL (that don't support stored
procedures), copy file

dsnewcustomer.php.nosp  

to dsnewcustomer.php


<dave_jaffe@dell.com> and <todd_muirhead@dell.com>  7/13/05
