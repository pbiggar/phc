<?php
define('MYBLOGGIE_INSTALL', true);
$version = "2.1.3";

$footer =
"<div id=\"credit\">
<a class=\"copyright\" href=\"http://mybloggie.mywebland.com/index.php?mode=doc\">Documentation</a> | <a href=\"http://mywebland.com/forums/\">Support Forums</a> | <a href=\"http://www.mywebland.com\">myWebland</a><br/>
Powered by <a href=\"http://mybloggie.mywebland.com\">myBloggie ".$version."</a> &copy; 2004 2005 </span></div>";

function die_msg($header, $message) {
global $version, $footer;
die("<div class=\"message\"><b>".$header."</b><br><br>$message</div>".$footer."</body>
</html>");
}

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>myBloggie <? echo $version ?> - Installation File Wizard</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<style type="text/css">
    <!--
  body {
    font-family: verdana, Times, serif;
    margin-left: 20px;
    margin-right: 20px;
    margin-top: 20px;
    margin-bottom: 20px;
  }

  .message {
    font-family: verdana, sans-serif; font-size: 11px; color: #006600;
    font-size : 11px;
    background-color: #fafafa; border: #D1D7DC; border-style: solid;
    border-left-width: 1px; border-top-width: 1px; border-right-width: 1px; border-bottom-width: 1px;
    padding-top : 15px;
    padding-right : 15px;
    padding-bottom : 15px;
    padding-left : 15px;
    margin-left: 20px;
    margin-right: 20px;
    margin-top: 20px;
    margin-bottom: 20px;
    text-align : left;
    }

  .status {
    font-family: new courier, courier ; font-size: 11px; color: #006600;
    font-size : 12px;
    background-color: #fafafa; border: #D1D7DC; border-style: solid;
    border-left-width: 1px; border-top-width: 1px; border-right-width: 1px; border-bottom-width: 1px;
    padding-top : 15px;
    padding-right : 15px;
    padding-bottom : 15px;
    padding-left : 15px;
    margin-left: 20px;
    margin-right: 20px;
    margin-top: 20px;
    margin-bottom: 20px;
    text-align : left;
    }

  #credit {
    text-align : center;
    font-family: verdana, sans-serif; font-size: 11px; color: #006600;
    font-size : 11px;
    color : #a0a0a0;
    }

p {
    font-family: verdana, sans-serif; font-size: 11px; color: #006600;
    font-size : 12px;
    color : #606060;
    }

td {
    font-family: verdana, sans-serif; font-size: 11px; color: #006600;
    font-size : 12px;
    color : #a0a0a0;
    }

  #header {
    margin: 0;
    padding: 0;
    background-image: url(http://mybloggie.mywebland.com/images/logo.gif);
    background-repeat: no-repeat;
    height: 60px;
    border-bottom: 2px solid #999;
  }
  #header a {
    display: block;
    height: 60px;
  }
  #header a span {
    display: none;
  }

.link     { font-size: 12px; font-family: Verdana, Arial, Helvetica, sans-serif; color: #006600;
             border-left-width: 1px; border-top-width: 1px; border-right-width: 1px; border-bottom-width: 1px;
             border: #D1D7DC; border-style: solid; padding : 3px;
}
a.link       { color: #006600; text-decoration: none;}
a.link:hover { color: #000000; text-decoration: underline;}

input,textarea,select {
  font-size: 12px;
  height : 18px;
  font-family: Verdana;
  border-style: solid;
  border-width: 1px;
  border-color: #aaaaaa;
  background: #efefef;
  border-width: 1px;
  margin: 2px;
}

    -->
  </style>
<!--script type="text/javascript" language="javascript"> </script-->
<!-- // hide from older browsers
  function open_preview(form)
  {
    // Stupid thing: having a field called action !
    var saved_action =  form.attributes.getNamedItem('action').value;
    form.attributes.getNamedItem('action').value = 'testdb.php';
    form.target = 'b2evo_preview';
    preview_window = window.open( '', 'b2evo_preview' );
    preview_window.focus();
    // submit after target window is created.
    form.submit();
    form.attributes.getNamedItem('action').value = saved_action;
    form.target = '_self';
  }
// -->

</head>
<body> 
<div id="header"><a href="http://mybloggie.mywebland.com"><span>myBloggie</span></a></div>

<?
if (file_exists('../config.php'))
{
  include ('../config.php') ;
  if (defined('INSTALLED')) {
  $header = "Error : config.php detected !<hr />";
  $message= "Unable to create 'config.php' as 'config.php' already exists. If you are planning to reinstall myBloggie, please delete it first or You can may to <a href='install.php'>install</a> now.";
  die_msg($header, $message);
  }
//}else
//if (!file_exists('../config_temp.php'))
//{
//  $header = "Error : config_temp.php is missing !<hr />";
//  $message= "Creation of 'config.php' require config_temp.php";
//  die_msg($header, $message);
} elseif (!is_writable('../')) {
  $header = "Error : File write/directory protected !<hr />";
  $message= "Unable write to the file/directory. Please change the permission of myBloggie file/directory";
}
//else { $config = file('../config_temp.php'); }

$install_step = 0;
if(isset($_GET['install_step'])) $install_step = intval($_GET['install_step']);


switch($install_step) {
  case 0:

?> 
<p><b>Thank you for using myBloggie</b>.</p>
<p>You about to experience a wonderful blogging adventure with myBloggie <? echo $version ?></p>

<div class="status"><b>myBloggie Pre-installation Checks</b><hr /><br /><br />
1. "config.php" file not present&nbsp -> status : OK<br />
2. Directory is writable&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;-> status : OK<br><br>
Pre-installation checks successfully completed you may proceed to the next step
<br />
<br />
</div>
<center><div class="border"><a href="wizard.php?install_step=1" class="link">Proceed to Step 1</a></div></center>
<br />
<?
echo $footer;
  break;

  case 1:
  ?>

<p>Installation Instruction for myBloggie <? echo $version ?><br /><br />
<b>Step 1 : Database Configuration</b><br /><br />
myBloggie is using mySQL database, as such to before the installation process, myBloggie requires mySQL database information in order to access to the database.</p>
<p>Below you should enter your database connection details. If you're not sure about these, contact your host. </p>
<form method="post"  action="wizard.php?install_step=2">
  <table>
    <tr>
      <td align="right">Database Host : </td>
      <td ><input type="text" name="db_host" value="localhost" /></td>
    </tr>
    <tr>
      <td align="right">Database Name : </td>
      <td ><input type="text" name="db_name" value="" /></td>
    </tr>
    <tr>
      <td align="right">Database user name : </td>
      <td ><input type="text" name="db_user" value='' /></td>
    </tr>
    <tr>
      <td align="right">Database Password : </td>
      <td ><input type="password" name="db_passwd" value='' /></td>
    </tr>
    <tr>
      <td align="right">Table_Prefix : </td>
      <td ><input type="text" name="table_prefix" value="<? echo (!empty($table_prefix)) ? $table_prefix : "mb_"; ?>" /></td>
    </tr>
    <tr>
    <tr>
      <td align="right">Time Zone (GMT) : </td>
      <td ><input type="text" name="timezone" value="" /></td>
    </tr>
    <tr>
      <td colspan="2" align="right">
      <input name="submit" type="submit" value="Submit" /></td>
    </tr>
  </table>
              <!--input type="submit" value="Preview" name="preview" />
              <input type="submit" value="Submit" name="submit" /-->

</form> 
<?
  break;
  
  case 2:
   $dbms = isset($HTTP_POST_VARS['dbms']) ? $HTTP_POST_VARS['dbms'] : 'mysql';
   $dbhost = (!empty($HTTP_POST_VARS['db_host'])) ? $HTTP_POST_VARS['db_host'] : 'localhost';
   $dbuser = (!empty($HTTP_POST_VARS['db_user'])) ? $HTTP_POST_VARS['db_user'] : '';
   $dbpasswd = (!empty($HTTP_POST_VARS['db_passwd'])) ? $HTTP_POST_VARS['db_passwd'] : '';
   $dbname = (!empty($HTTP_POST_VARS['db_name'])) ? $HTTP_POST_VARS['db_name'] : '';
   $timezone = (!empty($HTTP_POST_VARS['timezone'])) ? $HTTP_POST_VARS['timezone'] : '';
   $table_prefix = (!empty($HTTP_POST_VARS['table_prefix'])) ? $HTTP_POST_VARS['table_prefix'] :'';

  if (empty($prefix)) $prefix = 'mb_';

    $config_data = '<?php'."\n\n";
    $config_data .= "\n// myBloggie ".$version." config.php file\n// This file is auto generated , Please do not change anything in this file!\n\n";
    $config_data .= '$dbms = \'' . $dbms . '\';' . "\n\n";
    $config_data .= '$dbhost = \'' . $dbhost . '\';' . "\n";
    $config_data .= '$dbname = \'' . $dbname . '\';' . "\n";
    $config_data .= '$dbuser = \'' . $dbuser . '\';' . "\n";
    $config_data .= '$dbpasswd = \'' . $dbpasswd . '\';' . "\n\n";
    $config_data .= 'define(\'INSTALLED\',true );'."\n";
    $config_data .= '$table_prefix = \'' . $table_prefix . '\';' . "\n\n";
    $config_data .= '$timezone = \'' . $timezone . '\';' . "\n\n";
    $config_data .= 'define(\'POST_TBL\',"'.$table_prefix.'posts" );'."\n";
    $config_data .= 'define(\'USER_TBL\',"'.$table_prefix.'user" );'."\n";
    $config_data .= 'define(\'CAT_TBL\',"'.$table_prefix.'category" );'."\n";
    $config_data .= 'define(\'COMMENT_TBL\',"'.$table_prefix.'comment" );'."\n\n";
    $config_data .= 'include(\'setting.php\');'."\n\n";
    $config_data .= '?' . '>'; // Done this to prevent highlighting editors getting confused!

  // Test connection
  if (!@mysql_connect($dbhost,$dbuser,$dbpasswd))
  {
     $header = "Error : Database Connection Failure !<hr />";
     $message= "Unable connect to database. Information provided is not correct. Please hit the back to check your database connection details again";
     die_msg($header, $message);
  }
//  elseif ( ) {


//  }
  else
  {
     if (!($fp = @fopen('../config.php', 'w')))
     {
        $header = "Error : File write/directory write protected !<hr />";
        $message= "Unable write to the file/directory. Please check the permission of file/directory";
        die_msg($header, $message);
     }
     else
     {
       $result = @fputs($fp, $config_data, strlen($config_data));
       //fwrite($fp, $config_data);
       fclose($fp);
       //chmod('../config.php', 0666);
?>
<div class="status"><b>myBloggie - Create mySQL start-up file</b><hr /><br /><br />
1. Connection to mySQL&nbsp;&nbsp;&nbsp;&nbsp;-> status : OK<br>
2. Create config.php file -> status : OK<br><br>
Creation of config.php required for database connection successfully completed, You may proceed to the next step
<br />
<br />
</div>
<center><div class="border"><a href="install.php" class="link">Install now</a></div></center>
<br />

<?
     }
}
?>
<?php
  break;

}
?> 
</body>
</html>