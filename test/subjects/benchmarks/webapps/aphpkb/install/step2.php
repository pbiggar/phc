<?php //install Step 2 - Knowledgebase Details

$page_title = 'Aphpkb : Installation';
$title = 'Step 2 - Knowledgebase Details';

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
<i>Step 1 - Database</i><br />
<u>Step 2 - KB Details</u><br />
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
$default_pluginhtml = PLUGINWHIZZYWIG;   
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

<form name="step2" action="step3.php" method="post">

<fieldset><legend>Knowledgebase Details</legend>
Knowledgebase Name:<br />
<i>This is the name you will give to your knowledgebase, such as 'ACME Widget' </i><br />
<input type="text" name="install_kbname" value="<?php echo $default_kbname; ?>" /><br /> 
<p>Knowledgebase URL:<br />
<i>This is the URL of your knowledgebase, e.g. http://domain.com/kb/ please include the http:// and the ending '/'</i><br />
<input type="text" name="install_kburl" value="<?php echo $default_kburl; ?>" /><br /> 
Knowledgebase Home Page:<br />
<i>This is the URL back to your company/organisation home page, such as http://acme.com/widget - please include the http://</i><br />
<input type="text" name="install_kbhomeurl" value="<?php echo $default_kbhomeurl; ?>" /><br />
</fieldset>

<input type="hidden" name="install_dbuser" value="<?php echo $default_dbuser; ?>" />
<input type="hidden" name="install_dbpassword" value="<?php echo $default_dbpassword; ?>" />
<input type="hidden" name="install_dbhost" value="<?php echo $default_dbhost; ?>" />
<input type="hidden" name="install_dbname" value="<?php echo $default_dbname; ?>" />
<input type="hidden" name="install_dbmaxrec" value="<?php echo $default_dbmaxrec; ?>" />
<input type="hidden" name="install_pluginhtml" value="<?php echo $default_pluginhtml; ?>" />
<input type="hidden" name="install_pluginpdf" value="<?php echo $default_pluginpdf; ?>" />
<input type="hidden" name="install_pluginrss" value="<?php echo $default_pluginrss; ?>" />
<input type="hidden" name="install_prodlev" value="<?php echo $default_prodlev; ?>" />

<br />
<input type="submit" name="submit" value="Continue">

</form></div><?php
install_foot_page();
?>