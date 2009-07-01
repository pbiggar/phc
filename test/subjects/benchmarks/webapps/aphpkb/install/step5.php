<?php //install step 5- Write Configuration File

$page_title = 'Aphpkb : Installation';
$title = 'Step 5 - Write Configuration File';

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
<i>Step 2 - KB Details</i><br />
<i>Step 3 - Plugins</i><br />
<i>Step 4 - Admin Auth</i><br />
<u>Step 5 - Write Config</u><br />
<br /></p>

</div>
<div class="content">

<?php
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


if($_POST[submit]){
	   
// unless we've come from somewhere else

$default_dbuser = stripslashes($_POST['install_dbuser']);
$default_dbpassword = stripslashes($_POST['install_dbpassword']);
$default_dbhost = stripslashes($_POST['install_dbhost']);
$default_dbname = stripslashes($_POST['install_dbname']);
$default_dbmaxrec = stripslashes($_POST['install_dbmaxrec']);
$default_kbinstall = stripslashes($_POST['install_kbinstall']); 
$default_kbname = stripslashes($_POST['install_kbname']);   
$default_kburl = stripslashes($_POST['install_kburl']);       
$default_kbhomeurl = stripslashes($_POST['install_kbhomeurl']);    
$default_pluginhtml = stripslashes($_POST['install_pluginhtml']);   
$default_pluginpdf = stripslashes($_POST['install_pluginpdf']); 
$default_pluginrss = stripslashes($_POST['install_pluginrss']);   
$default_prodlev = stripslashes($_POST['install_prodlev']);	   
$fn = stripslashes($_POST['install_first_name']);
$ln = stripslashes($_POST['install_last_name']);
$e = stripslashes($_POST['install_email']);
$p1= stripslashes($_POST['install_password1']);
$p2 = stripslashes($_POST['install_password2']);


}
echo '<p>The config.php file will now be written, if any errors are shown you may need to re-check ownership and file permissions</p>';

// let's write out the dbsettings.php file	 	 
$output = <<<_CONFIGFILE
<?php // config.php
define ('KBINSTALL' ,'1');
define ('KBNAME' , '$default_kbname');
define ('KBURL' ,'$default_kburl/');
define ('KBHOMEURL', '$default_kbhomeurl');
define ('DB_USER', '$default_dbuser');
define ('DB_PASSWORD', '$default_dbpassword');
define ('DB_HOST', '$default_dbhost');
define ('DB_NAME', '$default_dbname');
define ('DB_MAX_REC', '$default_dbmaxrec');
define ('PLUGINHTML' , '$default_pluginhtml');
define ('PLUGINPDF' , '$default_pluginpdf');
define ('PLUGINRSS' , '$default_pluginrss');
define ('PRODLEV' , '$default_prodlev');         
?>
_CONFIGFILE;
	
	$file = '../config/config.php';
	$fh = fopen($file, "w");
	$status = fwrite($fh, $output);
	fclose($fh);
echo "
DB_USER = $default_dbuser<br />
DB_PASSWORD = $default_dbpassword <br />
DB_HOST = $default_dbhost <br />
DB_NAME = $default_dbname<br />
DB_MAX_REC = $default_dbmaxrec<br />
KB_NAME = $default_kbname<br />   
KB_URL = $default_kburl<br />   
KB_HOME_URL = $default_kbhomeurl<br />   
PLUGINHTML = $default_pluginhtml<br /> 
PLUGINPDF = $default_pluginpdf<br />
PLUGIN_RSS = $default_pluginrss<br /> 
PRODLEV = $default_prodlev<br />
<br /><hr />
Admin First/Last Name = $fn $ln<br />
Admin Email Address = $e<br />
Admin Password = $p1<br />

";?>

<p>To proceed we will register the admin user for the knowledgebase, please note that the database is required to be setup before the admin user can be registered:</p>

<p>The steps to setup the database are:</p>

<pre>
# mysql -u [database user]
 mysql> create database akb;
 mysql> use akb;
 mysql> exit
# mysql -u [database user] akb < /path-to-aphpkb/docs/akb.sql
</pre>

<p>Where "akb" is the database name.</p>

<form name="register" action="index.php" method="get">
<input type="hidden" name="install_first_name" value="<?php echo $fn; ?>" />
<input type="hidden" name="install_last_name" value="<?php echo $ln; ?>" />
<input type="hidden" name="install_email" value="<?php echo $e; ?>" />
<input type="hidden" name="install_password1" value="<?php echo $p1; ?>" />
<input type="hidden" name="install_password2" value="<?php echo $p2; ?>" />
<input type="submit" name="submit" value="Register to Complete">
</form>



<form name="step5" action="step1.php" method="post">
<input type="hidden" name="install_dbuser" value="<?php echo $default_dbuser; ?>" />
<input type="hidden" name="install_dbpassword" value="<?php echo $default_dbpassword; ?>" />
<input type="hidden" name="install_dbhost" value="<?php echo $default_dbhost; ?>" />
<input type="hidden" name="install_dbname" value="<?php echo $default_dbname; ?>" />
<input type="hidden" name="install_dbmaxrec" value="<?php echo $default_dbmaxrec; ?>" />
<input type="hidden" name="install_kbinstall" value="<?php echo $default_kbinstall;?>" />
<input type="hidden" name="install_kbname" value="<?php echo $default_kbname;?>" />
<input type="hidden" name="install_kburl" value="<?php echo $default_kburl;?>" />
<input type="hidden" name="install_kbhomeurl" value="<?php echo $default_kbhomeurl;?>" />
<input type="hidden" name="install_pluginhtml" value="<?php echo $default_pluginhtml;?>" />
<input type="hidden" name="install_pluginpdf" value="<?php echo $default_pluginpdf;?>" />
<input type="hidden" name="install_pluginrss" value="<?php echo $default_pluginrss;?>" />
<input type="hidden" name="install_prodlev" value="<?php echo $default_prodlev;?>" />
<br />
<input type="submit" name="submit" value="Return to Step 1">
</form>


</div>
<? install_foot_page();?>