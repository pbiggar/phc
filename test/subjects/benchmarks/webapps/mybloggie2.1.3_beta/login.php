<?

// Blog Script - File Name : login.php
// Copyright (C) myBloggie Sean
// http://www.mywebland.com , http://mybloggie.mywebland.com

// You are requested to retain this copyright notice in order to use
// this software.

//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

define('IN_MYBLOGGIE', true);

$mybloggie_root_path = './';

include_once('./config.php');
include_once('./includes/db.php');
include_once('./includes/template.php');
include_once('./includes/function.php');
include_once('./language/lang_eng.php');

$tabcolor='#efefef';


if (isset($_GET['mode'])) {
$mode =  htmlspecialchars($_GET['mode']) ; }

// Security precaution - sean 07 Oct 2005
if (isset($_POST['username'])) {
$username=$_POST['username'];
} else $username="";


if (isset($_POST['passwd'])) {
$passwd = $_POST['passwd'];
} else  $passwd = "";

$username = htmlspecialchars(rtrim(trim($username), "\\"));
$username = substr(str_replace("\\'", "'", $username), 0, 25);
$username = str_replace("'", "\\'", $username);

if( isset( $mode ) )
{
  if( $mode == "login" )
   {
      $username = trim( $username );
      $passwd = md5(trim( $passwd ));

      if( $username == "" ) message( $lang['Error'] , $lang['Msg_enter_name'] );
      if( $passwd == "" ) message($lang['Error'], $lang['Msg_enter_pass'] );
        $result = mysql_query( "SELECT user FROM ".USER_TBL." WHERE user='$username'
                  AND password='$passwd'" ) or error( mysql_error() );
       if( mysql_num_rows( $result ) != 1 ) {
?>
<head>
<title>myBloggie - Adminstrator Log In</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link rel="stylesheet" title="<? echo $style ?>" href="templates/<? echo $style ?>/<? echo $style ?>" type="text/css" />
</head>
<body bgcolor="#FFFFFF" topmargin="5" leftmargin="5" marginheight="5" marginwidth="5" ><center>
<?  message($lang['Error'],$lang['Msg_invalid_pass']) ;  ?>
</body></html>
<?    }
         else
      {
        session_start();

        $_SESSION['username'] = $username;
        $_SESSION['passwd'] = $passwd;
        header( "Location: ./admin.php" );
      }
    }

}
else
{

?>
<head>
<title>myBloggie - Adminstrator Log In</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>
<body bgcolor="#FFFFFF" topmargin="5" leftmargin="5" marginheight="5" marginwidth="5" ><center>
<!-- login.html ACTTIONFILE   -->
<style>
.tdloginheader { font-family: Verdana, Arial, Helvetica, sans-serif;
                  font-weight: bold;
                  font-size: 10pt;
                  letter-spacing: 0.09em;
                  color: #000000;
                  text-align: center;
                  line-height: 24px;
                  vertical-align: middle;
                  height: 20px;
}

.formfont {       font-family: Verdana, Arial, Helvetica, sans-serif;
                  font-weight: bold;
                  font-size: 11px;

}
input,textarea,select {
  font-size: 11px;
  font-family: Verdana;
  height: 22px;
  border-style: solid;
  border-width: 1px;
  border-color: #aaaaaa;
  background: #f0f0f0;
  border-width: 1px;
  margin: 2px;
}

</style>
<br /><br /><center>

<table id="Table_01" width="400"  border="0" cellpadding="0" cellspacing="0">
    <tr>
        <td>
            <img src="templates/<? echo $style ?>/images/login_01.gif" width="24" height="37" alt=""></td>
        <td>
            <img src="templates/<? echo $style ?>/images/login_02.gif" width="351" height="37" alt=""></td>
        <td>
            <img src="templates/<? echo $style ?>/images/login_03.gif" width="25" height="37" alt=""></td>
    </tr>
    <tr>
        <td background="templates/<? echo $style ?>/images/login_04.gif" width="24" height="300">
            </td>
        <td>
<center>
<table width="300" cellppacing="0" cellpadding="3" border="0">
        <tr><td colspan="2" class="tdloginheader">Log In</td></tr>
 <tr><td colspan=2></td></tr>
 <tr><td colspan=2></td></tr>
<form method="post" action="<? echo $_SERVER['PHP_SELF'] ?>?mode=login">
<tr>
<td width='100' height='25' class="formfont">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; User Name</td>
<td height='25'><input type='text' name='username'  size='20' maxlength='50'></td>
</tr>
<tr>
<td width='100' height='25' class="formfont">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Password</td>
<td height='25'><input type='password' name='passwd' size='20' maxlength='32'></td>
</tr>
<tr>
<td width='100' height='25'></td>
<td height='25'><input type=submit value='Log In' name=submit></td>
</tr>
 <tr><td colspan=2></td></tr>
</form>
</table
</center>
</td>
        <td background="templates/<? echo $style ?>/images/login_06.gif" width="25" height="300">
            </td>
    </tr>
    <tr>
        <td>
            <img src="templates/<? echo $style ?>/images/login_07.gif" width="24" height="37" alt=""></td>
        <td>
            <a href="http://mywebland.com"><img src="templates/<? echo $style ?>/images/login_08.gif" width="351" height="37" alt="" border="0"></a></td>
        <td>
            <img src="templates/<? echo $style ?>/images/login_09.gif" width="25" height="37" alt=""></td>
    </tr>
</table>

</center></body></html>
<?
}
?>
