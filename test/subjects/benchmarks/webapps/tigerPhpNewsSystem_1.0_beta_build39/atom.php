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
$tzdate=preg_replace("#([-+])([0-9])([0-9])([0-9])([0-9])#","$1$2$3:$4$5",strftime("%z",$news['0']['date']));
$date=strftime("%Y-%m-%dT%T",$news['0']['date']).$tzdate;


header('Content-type: application/xml ; charset=iso-8859-15');
print "<?xml version='1.0' encoding='iso-8859-15'?>\n";
print "<?xml-stylesheet href=\"http://$_SERVER[HTTP_HOST]/$stylesheet\" type=\"text/css\"?>";
print "<feed xml:lang=\"en\" xmlns=\"http://www.w3.org/2005/Atom\">\n";
print "<title type=\"text\">$sitetitle</title>\n";

print "
<updated>$date</updated>
<id>tag:$_SERVER[HTTP_HOST],2006:0</id>

<link rel=\"alternate\" type=\"text/html\" hreflang=\"en\" href=\"http://$_SERVER[HTTP_HOST]\"/>
<link rel=\"self\" type=\"application/atom+xml\" href=\"http://$_SERVER[HTTP_HOST]$_SERVER[SCRIPT_NAME]\"/>
<rights>Copyright (c) 2006, $sitetitle</rights>
<generator uri=\"http://tpns.sourceforge.net\" version=\"1.0\">TPNS</generator>

";
foreach( $news as $text )
{	
    print "<entry>\n<title>$text[headline]</title>\n";
    print "<link rel=\"alternate\" type=\"text/html\" href=\"http://$_SERVER[HTTP_HOST]/?page=viewnews&amp;id=$text[id]\" />\n";
    print "<id>tag:$_SERVER[HTTP_HOST],2006:$text[id]</id>\n";
    $date=strftime("%Y-%m-%dT%T",$text['date']).$tzdate;
    print "<published>$date</published>\n";
    print "<updated>$date</updated>\n";
    print "<author><name>$text[name]</name></author>\n";
    
    print "<content type=\"xhtml\"  xml:lang=\"en\">\n<div xmlns=\"http://www.w3.org/1999/xhtml\">\n$text[data]\n</div>\n</content>\n";
    print "</entry>\n\n";
}

print "</feed>\n";
//print $main->sqlstatments."\n";
//}}}
?>
