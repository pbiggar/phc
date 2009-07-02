<?

if ( !defined('IN_MYBLOGGIE') )
  {
    die("You are not allowed to access this page directly !");
  }


if ((isset($_GET['month_no']) || isset($_GET['year'])) && (!preg_match('/^[0-9]+$/', $_GET['year']) || !preg_match('/^[0-9]+$/',$_GET['month_no']) ))
{
echo "<meta http-equiv=\"Refresh\" content=\"3;url=".self_url()."/oops.php\" />";
}

if (isset($_GET['month_no']))
{ $month_no = intval($_GET['month_no']);
}
else
{ $month_no=gmtdate('n', time(), $timezone ); }


if (isset($_GET['year']))
{ $year = intval($_GET['year']);
}
else
{ $year = gmtdate('Y', time(), $timezone ); }


$monthfulltext = date('F', mktime(0, 0, 0, $month_no, 1, $year));
$monthshorttext = date('M', mktime(0, 0, 0, $month_no, 1, $year));

$day_in_mth = date('t', mktime(0, 0, 0, $month_no, 1, $year)) ;
$day_text = date('D', mktime(0, 0, 0, $month_no, 1, $year));


?>
<table border="0" cellpadding="0" cellspacing="1" width="95%">
<tr>
  <td class="tdheading">
  <? $monthchange = $month_no-1; $yearchange=$year;
     if ($monthchange==0){ $monthchange=12; $yearchange=$year-1;} else { $yearchange=$year; }

  ?>
  <a class="std" href="<? echo $_SERVER['PHP_SELF']."?month_no=".$monthchange."&amp;year=".$yearchange ?>">
  <img src="templates/<? echo $style ?>/images/leftarrow.gif" border="0" alt="<? echo date('M', mktime(0, 0, 0, $monthchange, 1, $yearchange))." ".$yearchange ?>"></img>
  </a></td>
  <td class="tdheading" colspan="5"><? echo $lang["$monthfulltext"]." ".$year ?></td>
  <td class="tdheading">
  <? $monthchange = $month_no+1;

     if ($monthchange==13){ $monthchange=1; $yearchange=$year+1;} else { $yearchange=$year; }
  ?>
  <a class="std" href="<? echo $_SERVER['PHP_SELF']."?month_no=".$monthchange."&amp;year=".$yearchange ?>">
  <img src="templates/<? echo $style ?>/images/rightarrow.gif" border="0" alt="<? echo date('M', mktime(0, 0, 0, $monthchange, 1, $yearchange))." ".$yearchange ?>"></img></a>


  </td></tr>
<tr>
  <td class="tdsunday"><? echo $lang["shortsunday"] ?>
  </td><td class="tdday"><? echo $lang["shortmonday"] ?>
  </td><td class="tdday"><? echo $lang["shorttuesday"] ?>
  </td><td class="tdday"><? echo $lang["shortwednesday"] ?>
  </td><td class="tdday"><? echo $lang["shortthursday"] ?>
  </td><td class="tdday"><? echo $lang["shortfriday"] ?>
  </td><td class="tdday"><? echo $lang["shortsaturday"] ?>
  </td>
</tr>
<tr>
<?

$day_of_wk = date('w', mktime(0, 0, 0, $month_no, 1, $year));

if ($day_of_wk <> 0){
   for ($i=0; $i<$day_of_wk; $i++)
   { ?>
   <td class="tddate">&nbsp;</td>
   <?
   }
}

for ($date_of_mth = 1; $date_of_mth <= $day_in_mth; $date_of_mth++) {

    $date_no = date('j', mktime(0, 0, 0, $month_no, $date_of_mth, $year));
    $day_of_wk = date('w', mktime(0, 0, 0, $month_no, $date_of_mth, $year));

   $sql = "SELECT  * FROM ".POST_TBL." WHERE

           DATE_FORMAT(FROM_UNIXTIME(timestamp) , '%e') = $date_no  AND
           DATE_FORMAT(FROM_UNIXTIME(timestamp) , '%Y') = $year AND
           DATE_FORMAT(FROM_UNIXTIME(timestamp) , '%c') = $month_no
           AND ".POST_TBL.".timestamp<='".$timestamp."'";

   $result = $db->sql_query($sql) ;
   $row = $db->sql_numrows($result);

   if ( $date_no ==  gmtdate('j', time(), $timezone ) &&  $month_no == gmtdate('n', time(), $timezone ) ){
     if ($row > 0 ){ $linkdate ="<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=viewdate&amp;date_no=".$date_no."&amp;month_no=".$month_no."&amp;year=".$year."\">".$date_no."</a>"; }
   else { $linkdate  = $date_no ; }

    ?>
     <td class="tdtoday"><? echo $linkdate ?></td>
     <? }
   else{
   if ($row > 0 ){ $linkdate ="<a class=\"std\" href=\"".$_SERVER['PHP_SELF']."?mode=viewdate&amp;date_no=".$date_no."&amp;month_no=".$month_no."&amp;year=".$year."\">".$date_no."</a>"; }
  else { $linkdate  = $date_no ; }

   ?>
   <td class="tddate"><? echo $linkdate ?></td>
   <?  }


   If ( $day_of_wk == 6 ) {  ?></tr><tr><? }
   If ( $day_of_wk < 6 && $date_of_mth == $day_in_mth ) {
   for ( $i = $day_of_wk ; $i < 6; $i++ ) {
     ?><td class="tddate">&nbsp;</td><? }
      ?></tr><?
      }
 }
?>
</table>