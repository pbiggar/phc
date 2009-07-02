<?

define('IN_MYBLOGGIE', true);

$mybloggie_root_path = '../';

include_once('./config.php');
include_once('./includes/db.php');
include_once('./includes/function.php');
include_once('./language/lang_eng.php');

if(isset($_GET['install_step'])) $install_step = intval($_GET['install_step']);
else $install_step = 0;

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
if (!file_exists('../config.php'))
{
  $header = "Error : config.php is not found !<hr />";
  $message= "\"config.php\" needed for the installation was available. Unable to proceed further. <br /><br />
  <b>What do I need to do ?</b><br /><br />
  1. Create config.php manually before running the install.php.<br />
     &nbsp;&nbsp;&nbsp;- Please open config_temp.php ( myBloggie root directory ) & fill-up relevant info<br />
     &nbsp;&nbsp;&nbsp;- Save it as config.php.<br />
     &nbsp;&nbsp;&nbsp;- Run install.php again <br />
     <br />
     OR
     <br /><br />
  2. Run the wizard.php to guide you<br />

";
  die_msg($header, $message);
}
else
{
if ($install_step =="0") {
?>
<p>Admin Configuration<br /><br />
<p>Please enter administator's information</p><br /><br />

<form method="post"  action="install.php?install_step=1">
  <table>
    <tr>
      <td align="right">Administrator's User Name : </td>
      <td ><input type="text" name="admin_name" value="" /></td>
    </tr>
    <tr>
      <td align="right">Administrator's Password : </td>
      <td ><input type="password" name="admin_pass1" value='' /></td>
    </tr>
    <tr>
      <td align="right">Reenter Password : </td>
      <td ><input type="password" name="admin_pass2" value='' /></td>
    </tr>
    <tr>
      <td colspan="2" align="right">
      <input name="submit" type="submit" value="Submit" /></td>
    </tr>
  </table>

<?
}
if(isset($_GET['install_step'])) $install_step = intval($_GET['install_step']);
else $install_step = 0;
switch($install_step) {
  case 1:

$admin_name = ( !empty($HTTP_POST_VARS['admin_name']) ) ? $HTTP_POST_VARS['admin_name'] : "";
$admin_pass1 = ( !empty($HTTP_POST_VARS['admin_pass1']) ) ? $HTTP_POST_VARS['admin_pass1'] : "";
$admin_pass2 = ( !empty($HTTP_POST_VARS['admin_pass2']) ) ? $HTTP_POST_VARS['admin_pass2'] : "";

if  ($admin_pass1 != $admin_pass2) {
  $header = "Error : Password not match !<hr />";
  $message= "Password entered do not match, Please press back button or click on this link <a href=\"install.php\">Link</a> <br /><br />";
  die_msg($header, $message);
}

$sql = "SELECT * from " . POST_TBL . ";" ;

  if( mysql_query($sql) )
   {
    $header = "Error : Tables Already Exist !<hr />";
    $message= "myBloggie's tables detected, Looks like you have already installed myBloggie... <br /><br />
    If you would like to reinstall please remove your old tables from mySQL database<br /><br />";
  die_msg($header, $message);
  } else {

    $sql = "CREATE TABLE `".COMMENT_TBL."` (
  `comment_id` int(5) NOT NULL auto_increment,
  `post_id` int(5) NOT NULL default '0',
  `comment_subject` text NOT NULL,
  `com_tstamp` varchar(10) NOT NULL default '',
  `poster` varchar(64) NOT NULL default '',
  `email` varchar(128) NOT NULL default '',
  `home` varchar(128) NOT NULL default '',
  `comments` text NOT NULL,
  `comment_type` enum('comment','linkback','trackback','pingback') NOT NULL default 'comment',
  `ip` varchar(16) NOT NULL default '',
  PRIMARY KEY  (`comment_id`)
) TYPE=MyISAM";

  if( !($result = $db->sql_query($sql)) )
   {
     $sql_error = $db->sql_error();
    echo $sql_error['message'];
   }
//   $result = $db->sql_query($sql) ;

   $sql = "CREATE TABLE `".POST_TBL."` (
  `post_id` smallint(5) unsigned NOT NULL auto_increment,
  `user_id` varchar(4) NOT NULL default '',
  `subject` tinytext,
  `message` longtext,
  `timestamp` int(11) NOT NULL default '0',
  `cat_id` tinyint(2) NOT NULL default '0',
  `allow_tb` char(1) NOT NULL default '',
  PRIMARY KEY  (`post_id`)
) TYPE=MyISAM" ;

  if( !($result = $db->sql_query($sql)) )
   {
     $sql_error = $db->sql_error();
    echo $sql_error['message'];
   }
//   $result = $db->sql_query($sql) ;

   $sql =
   "CREATE TABLE `".USER_TBL."` (
  `user` varchar(64) NOT NULL default '',
  `id` tinyint(4) NOT NULL auto_increment,
  `password` varchar(32) NOT NULL default '',
  `level` tinyint(1) NOT NULL default '0',
  `session_time` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `id` (`id`)
) TYPE=MyISAM
  " ;

 if( !($result = $db->sql_query($sql)) )
 {
 $sql_error = $db->sql_error();
 echo $sql_error['message'];
 }

   $sql =
   "CREATE TABLE `".CAT_TBL."` (
  `cat_id` tinyint(2) NOT NULL auto_increment,
  `cat_desc` varchar(64) NOT NULL default '',
  PRIMARY KEY  (`cat_id`)
) TYPE=MyISAM";

 if( !($result = $db->sql_query($sql)) )
 {
 $sql_error = $db->sql_error();
 echo $sql_error['message'];
 }

$timestamp = time();
$admin_pass = md5($admin_pass1);

$sql = "INSERT INTO ".POST_TBL." SET user_id='1', subject='Testing Message for myBloggie', message='This is a test Message. You can delete this message after you logged in', timestamp='$timestamp', cat_id='1'";
if( !($result = $db->sql_query($sql)) )
{
   $sql_error = $db->sql_error();
   echo $sql_error['message'];
}

$sql = "INSERT INTO ".CAT_TBL." VALUES (1, 'General')";
if( !($result = $db->sql_query($sql)) )
{
   $sql_error = $db->sql_error();
   echo $sql_error['message'];
}
$sql = "INSERT INTO ".USER_TBL." SET user='$admin_name', password='$admin_pass', level='1'";
if( !($result = $db->sql_query($sql)) )
{
   $sql_error = $db->sql_error();
   echo $sql_error['message'];
}

?>
 <div class="status"><b>Create myBloggie's Tables</b><hr /><br /><br />
  myBloggie's Tables successfully created<br />
  myBloggie's Data successfully inserted<br />
  Installation completed...Easy right?<br /><br />
  Please delete the install folder before start blogging for security reason<br /><br />
 <br />
 <br />
 </div>
 <center><div class="border"><a href="../index.php" class="link">Now Lets Blog</a></div></center>
 <br />
<?
 echo $footer;
 break;
// End create table


  }

  } //end switch
}

?>
