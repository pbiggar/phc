<?php //install Step 3 - Plugins

$page_title = 'Aphpkb : Installation';
$title = 'Step 3 - Plugins';

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
<u>Step 3 - Plugins</u><br />
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

<form name="step3" action="step4.php" method="post">

<fieldset><legend>Plugin Details</legend>
<p><input type="checkbox" name="install_pluginhtml" value="1" <?php if($default_pluginhtml=='1') {echo 'checked';}?> />HTML Editor Plugin<br />
<input type="checkbox" name="install_pluginpdf" value="1" <?php if($default_pluginpdf=='1') {echo 'checked';}?> />Article PDF Plugin<br />
<input type="checkbox" name="install_pluginrss" value="1" <?php if($default_pluginrss=='1') {echo 'checked';}?> /> RSS Plugin<br /></p>

</fieldset>
<br /><br />
<fieldset><legend>Error Handling</legend>
<p>Production Level:<br />
<select name="install_prodlev">
<option value="0" <?php if(PRODLEV==0){ echo 'selected';}?>>Development</option>
<option value="1"  <?php if(PRODLEV==1){ echo 'selected';}?>>Production</option>
</select>
</p>

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

<br />
<input type="submit" name="submit" value="Continue">


</form></div>
<?php

install_foot_page();
?>