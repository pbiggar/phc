<?
/*
 * This software is part of the Tiger php news system
 * http://tpns.sourceforge.net
 * 
 * This software comes with ABSOLUTELY NO WARRANTY. For details, see
 * the enclosed file COPYING for license information (GPL). If you
 * did not receive this file, see http://www.gnu.org/licenses/gpl.txt.
 * 
 */
//{{{ Init
require_once( 'Main.php' );
include ('config.php');
$main = new Main();
$_REQUEST = $main->clean_array( $_REQUEST );
$userid=0;
$role=0;
//}}}
//{{{Login
if ( isset($_REQUEST['user']) and isset($_REQUEST['passwd']) )
{
    $user="";if ( $_REQUEST['user'] != "" ){$user=$_REQUEST['user'];}
    $passwd="";if ( $_REQUEST['passwd'] != "" ){$passwd=$_REQUEST['passwd'];}
    $userdata=$main->login($user, $passwd, false );
    if ( $userdata->rows != 0)
    {
        $userid=$userdata->records[0]['id'];
        $role=$userdata->records[0]['role'];
    }
}
//}}}
//{{{ Print content

$nr="10";if ( isset($_REQUEST['nr']) ){$nr=$_REQUEST['nr'];}
$tnews = $main->getnewsrss( $role , 0 , $nr);
$news = $main->rss_array($tnews->records);
header('Content-type: text/xml ; charset=iso-8859-15');
print "<?xml version='1.0' encoding='iso-8859-15'?>\n";
print "<rss version='2.0'   
  xmlns:dc=\"http://purl.org/dc/elements/1.1/\"
  xmlns:content=\"http://purl.org/rss/1.0/modules/content/\"
  xmlns:admin=\"http://webns.net/mvcb/\"
  xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n";
print "<channel>\n";
print "<title>$sitetitle</title>\n";
print "<link>http://$_SERVER[HTTP_HOST]$_SERVER[SCRIPT_NAME]</link>\n";
print "<description>Latest news from $sitetitle</description>\n";

print "<dc:language>en-us</dc:language>";
print "<dc:creator>$sitetitle ($adminemail)</dc:creator>";
print "<dc:rights>Copyright 2005 $sitetitle</dc:rights>";

print "<admin:generatorAgent rdf:resource=\"http://tpns.sourceforge.net\" />";
print "<admin:errorReportsTo rdf:resource=\"mailto:$adminemail\"/>";

print "<ttl>30</ttl>\n";
foreach( $news as $text )
{	
    print "<item>\n<title>$text[headline]</title>\n";
    print "<link>http://$_SERVER[HTTP_HOST]/?page=viewnews&amp;id=$text[id]</link>\n";
    print "<description><![CDATA[$text[data]]]></description>\n";
    //print "<content:encoded><![CDATA[$text[data]]]></content:encoded>\n";
    $tzdate=preg_replace("#([-+])([0-9])([0-9])([0-9])([0-9])#","$1$2$3:$4$5",strftime("%z",$text['date']));
    $date=strftime("%Y-%m-%dT%T",$text['date']).$tzdate;
    print "<dc:date>$date</dc:date>\n";
    print "<guid isPermaLink='true'>http://$_SERVER[HTTP_HOST]/?page=viewnews&amp;id=$text[id]</guid>\n";
    print "<dc:creator>$text[name]</dc:creator>\n";
    print "<dc:subject>$text[headline]</dc:subject>";
    print "\n</item>\n";
}

print "</channel>\n</rss>\n";
//print $main->sqlstatments."\n";
//}}}
?>
