<?

// Blog Script - File Name : archives.php
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

$sql= "SELECT DISTINCT DATE_FORMAT( FROM_UNIXTIME( `timestamp` ) , '%m' ) AS m,
DATE_FORMAT( FROM_UNIXTIME( `timestamp` ) , '%Y' ) AS y,   COUNT( 'm' ) as t
FROM ".POST_TBL."
WHERE ".POST_TBL.".timestamp<='".$timestamp."'
GROUP BY m
ORDER BY   y DESC, DATE_FORMAT( FROM_UNIXTIME( `timestamp` ) , '%m' ) DESC
LIMIT 0 , ".$archivelimit;

$result = $db->sql_query($sql) ;

$template->set_filenames(array(
        'archive' => 'archive.tpl',
        ));
$template->assign_vars(array(
     'ARCHIVE'  => $lang['Archives'],
));
while ($archive = $db->sql_fetchrow($result)) {

   switch ($archive['m'])
     {
     case 1: $mthfulltext = $lang['January']; break;
     case 2: $mthfulltext = $lang['February']; break;
     case 3: $mthfulltext = $lang['March']; break;
     case 4: $mthfulltext = $lang['April']; break;
     case 5: $mthfulltext = $lang['May']; break;
     case 6: $mthfulltext = $lang['June']; break;
     case 7: $mthfulltext = $lang['July']; break;
     case 8: $mthfulltext = $lang['August']; break;
     case 9: $mthfulltext = $lang['September']; break;
     case 10: $mthfulltext = $lang['October']; break;
     case 11: $mthfulltext = $lang['November']; break;
     case 12: $mthfulltext = $lang['December']; break;
     } 

   $template->assign_block_vars('archive', array(
   'MTH'   => $mthfulltext." ".$archive['y'],
   'POSTS'   => $archive['t'],
   'U_ARCHIVE'  => $_SERVER['PHP_SELF']."?mode=viewmonth&amp;month_no=".$archive['m']."&amp;year=".$archive['y'] ,
    )
    );
}

$template->pparse('archive');

?>