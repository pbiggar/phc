<?

// Blog Script - File Name : userlist.php
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

if ( !defined('IN_MYBLOGGIE') )
{
    die("You are not allowed to access this page directly !");
}


if ( !defined('IN_MYBLOGGIE') )
{
    die("You are not allowed to access this page directly !");
}

$sql = "SELECT ".USER_TBL.".user, ".USER_TBL.".level,   ".USER_TBL.".id
FROM ".USER_TBL."
Order by ".USER_TBL.".id ASC ";

if( !($result = $db->sql_query($sql)) )
   {
    $sql_error = $db->sql_error();
    echo $sql_error['message'];
   }

$result = $db->sql_query($sql) ;
while ($row = $db->sql_fetchrow($result)) {

$id = $row['id'];
$name = $row['name'];
if ($row['level']==1) { $level = "Administrator" ;}
elseif ($row['level']==2) { $level = "Normal User" ;}

$template->assign_block_vars('listing', array(
          'NAME'        => $row['user'],
          'LEVEL'       => $level,
          'U_EDIT'      => "[<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=edituser&id=".$id."\">".$lang['Edit']."</a>]",
          'U_DELETE'    => "[<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=deluser&id=".$id."\">".$lang['Del']."</a>]" ,
 )
 );
}

$template->pparse('userlist');

?>