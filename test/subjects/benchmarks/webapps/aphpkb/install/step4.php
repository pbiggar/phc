<?php //install Step 4 - Admin Authentication

$page_title = 'Aphpkb : Installation';
$title = 'Step 4 - Admin Authentication';

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
<u>Step 4 - Admin Auth</u><br />
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

<form name="step4" action="step5.php" method="post">
<fieldset><legend>KB Admin Account Details</legend>
<p>First Name:<br /> <input type="text" name="install_first_name" size="15" maxlength="15" value=" " /></p>
<p>Last Name:<br /> <input type="text" name="install_last_name" size="30" maxlength="30" value="" /></p>
<p>Email Address:<br /> <input type="text" name="install_email" size="40" maxlength="40" value="" /> </p>
<p>Password:<br /><input type="password" name="install_password1" size="20" maxlength="20" /> <small>Use only letters and numbers. Must be between 4 and 20 characters long.</small></p>
<p>Confirm Password:<br /><input type="password" name="install_password2" size="20" maxlength="20" /></p>
</fieldset>

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
<input type="submit" name="submit" value="Continue">

</form></div>
<?php install_foot_page();?>