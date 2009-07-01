<?php //install step 1- Database Details

$page_title = 'Aphpkb : Installation';
$title = 'Step 1 - Database Details';

include('../config/config.php');
include('../functions.php');
include"../html/header.html";
?>
<div id="navAlpha">
<div class="title">
<p>
<img src="../imgs/logo.png" width="45" alt="Andy Grayndler">
<br /></div><b>Andy's PHP Knowledgebase</b></p>
<p><i>Release Notes</i><br />
<u>Step 1 - Database</u><br />
<i>Step 2 - KB Details</i><br />
<i>Step 3 - Plugins</i><br />
<i>Step 4 - Admin Auth</i><br />
<i>Step 5 - Write Config</i><br />
<br /></p>
</div>

<div class="content">

<?
// assign default values
$default_dbuser = DB_USER;
$default_dbpassword = DB_PASSWORD;
$default_dbhost = DB_HOST;
$default_dbname = DB_NAME;
$default_dbmaxrec = DB_MAX_REC;
$default_kbinstall = KBINSTALL; 
$default_kbname = KBNAME;   
$default_kburl = KBURL;       
$default_kbhomeurl = KBHOMEURL;    
$default_pluginhtml = PLUGINHTML;   
$default_pluginpdf = PLUGINPDF; 
$default_pluginrss = PLUGINRSS;   
$default_prodlev = PRODLEV;

// unless we've come from somewhere else

if($_POST[submit]){
$default_dbuser = $_POST['install_dbuser'];
$default_dbpassword = $_POST['install_dbpassword'];
$default_dbhost = $_POST['install_dbhost'];
$default_dbname = $_POST['install_dbname'];
$default_dbmaxrec = $_POST['install_dbmaxrec'];
$default_kbinstall = $_POST['install_kbinstall']; 
$default_kbname = $_POST['install_kbname'];   
$default_kburl = $_POST['install_kburl'];       
$default_kbhomeurl = $_POST['install_kbhomeurl'];    
$default_pluginhtml = $_POST['install_pluginhtml'];   
$default_pluginpdf = $_POST['install_pluginpdf']; 
$default_pluginrss = $_POST['install_pluginrss'];   
$default_prodlev = $_POST['install_prodlev'];	   
}
?>

<form name="step1" action="step2.php" method="post">
<fieldset><legend>Database Details</legend>
<p>Database User:<br />
<i>The database user that is used to authenticate with MySQL </i><br />
<input type="text" name="install_dbuser" value="<?php echo $default_dbuser; ?>" /><br />
</p>
<p>Database Password:<br />
<i>The password that is used to authenticate with MySQL (currently set to <b><?php if (strlen($default_dbpassword) > 0) { echo $default_dbpassword; } else {echo "''";} ?></b>)</i><br />
<input type="password" name="install_dbpassword" value="<?php echo $default_dbpassword;?>" />
</p>
<p>Database Host:<br />
<i>The hostname of the server that hosts the MySQL system you will access for the database </i><br />
<input type="text" name="install_dbhost" value="<?php echo $default_dbhost; ?>" />
</p>
<p>Database Name:<br />
<i>The name for your aphpkb database </i><br />
<input type="text" name="install_dbname" value="<?php echo $default_dbname; ?>" />
</p>

<p>Display Maximum Records:<br />
<i>The maximum number of records to display per page when displaying records and listings on the main page </i><br />
<input type="text" size="4" name="install_dbmaxrec" value="<?php echo $default_dbmaxrec; ?>" />
</p>




</fieldset>

<input type="hidden" name="install_kbinstall" value="<?php echo $default_kbinstall;?>" />
<input type="hidden" name="install_kbname" value="<?php echo $default_kbname;?>" />
<input type="hidden" name="install_kburl" value="<?php echo $default_kburl;?>" />
<input type="hidden" name="install_kbhomeurl" value="<?php echo $default_kbhomeurl;?>" />
<input type="hidden" name="install_pluginhtml" value="<?php echo $default_pluginhtml;?>" />
<input type="hidden" name="install_pluginpdf" value="<?php echo $default_pluginpdf;?>" />
<input type="hidden" name="install_pluginrss" value="<?php echo $default_pluginrss;?>" />
<input type="hidden" name="install_prodlev" value="<?php echo $default_prodlev;?>" />
<br />
<input type="submit" name="submit" value="Continue">

</form></div>

<?php
install_foot_page();
?>