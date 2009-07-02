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

//{{{ PHP start
#start timer:
$stimer = explode( ' ', microtime() );
$stimer = $stimer[1] + $stimer[0];

$isbot=false;
if ( preg_match("/bot|spider|crawl|seek|search|slurp|checker|meta|validator/is",$_SERVER['HTTP_USER_AGENT'] ) )
{
    $isbot=true;
}

header("Content-Type: text/html; charset=ISO-8859-15");
require_once( 'Main.php' );
include( 'config.php' );
require_once( 'sessions.php' );
$confnr=$nr;

$main = new Main();
if ($usedbsessions)
{
    $session = new session();
    $session->setMain($main);
    session_set_save_handler(array(&$session,"open"), array(&$session,"close"), array(&$session,"read"), array(&$session,"write"), array(&$session,"destroy"), array(&$session,"gc")); 
}
session_start();
//{{{ LOG ANON COMMENTS
if (isset($_REQUEST['page']) and $logannoncomment)
{
    if ( !isset($_SESSION['role'])){$_SESSION['role']="0";}
    if ($_SESSION['role'] == "0" and $_REQUEST['page'] == "addnewscomment")
    {
        //open the file and append the contents
        $fp = fopen($annoncommentlogfile, "a+");

        // Write the request to the file
        fwrite($fp, "\n\nREMOTE_ADDR=".$_SERVER['REMOTE_ADDR']);
        fwrite($fp, "\nHTTP_HOST=".$_SERVER['HTTP_HOST']);
        fwrite($fp, "\nHTTP_USER_AGENT=".$_SERVER['HTTP_USER_AGENT']);
        fwrite($fp, "\nHTTP_ACCEPT=".$_SERVER['HTTP_ACCEPT']);
        fwrite($fp, "\nHTTP_ACCEPT_LANGUAGE=".$_SERVER['HTTP_ACCEPT_LANGUAGE']);
        fwrite($fp, "\nHTTP_ACCEPT_ENCODING=".$_SERVER['HTTP_ACCEPT_ENCODING']);
        fwrite($fp, "\nHTTP_ACCEPT_CHARSET=".$_SERVER['HTTP_ACCEPT_CHARSET']);
        foreach ($_GET as $key => $val) {fwrite($fp, "\n_GET: ".$key."=".$val);}
        foreach ($_POST as $key => $val) {fwrite($fp, "\n_POST: ".$key."=".$val);}
        foreach ($_SESSION as $key => $val) {fwrite($fp, "\n_SESSION: ".$key."=".$val);}
        foreach ($_COOKIE as $key => $val) { fwrite($fp, "\n_COOKIE: ".$key."=".$val);
			}
        fwrite($fp, "\n");
        // Close the file
        fclose($fp);
    }
}
//}}}
$havecookie=false;
if ( isset($_COOKIE['PHPSESSID']) and isset($_SESSION['reqid']) )
{
    $havecookie=true;
}

$main->isbot=$isbot;
$main->havecookie=$havecookie;
$upload_max_filesize = ini_get('upload_max_filesize');
$form_upload_max_filesize = preg_replace('/M/', '000000', $upload_max_filesize);
$text_upload_max_filesize = preg_replace('/M/', ' Megabyte(s)', $upload_max_filesize);

//$main->Main();
$_REQUEST = $main->clean_array( $_REQUEST, true );
$_SERVER = $main->clean_array( $_SERVER, false, false );
if ( isset($_SESSION['nr']) ){$nr=$_SESSION['nr'];}
if ( isset($_REQUEST['nr']) ){$nr=$_REQUEST['nr'];}
$count=0;
$plugins=array();
//Variables
$page="start";if ( $initpage == "true"){ $page="init";}if ($enablesplash){ $page="splash";}if ( isset($_REQUEST['page']) ){$page=$_REQUEST['page'];}
$bbcode="
<script type=\"text/javascript\">
//<!--
function showBBcodehelp()
{
        var bbcodetext = document.getElementById('bbcodehelp');
        var bbon = document.getElementById('bbon');
        bbcodetext.style.display = \"block\";
        bbon.style.display = \"none\";
}
function hideBBcodehelp()
{
        var bbcodetext = document.getElementById('bbcodehelp');
        var bbon = document.getElementById('bbon');
        bbcodetext.style.display = \"none\";
        bbon.style.display = \"block\";
}
//-->
</script>
<input type='button' value='bbcode' id='bbon' onclick=\"showBBcodehelp()\"  class='button'/>
<div id='bbcodehelp' style='display:none'>
<input type='button' value='bbcode' id='bboff' onclick=\"hideBBcodehelp()\"  class='button'/>
<p><small>[b]<b>B</b>[/b] [i]<i>i</i>[/i] [u]<span class='uline'>u</span>[/u] [s]<span class=\"small\">s</span>[/s] [sm]<small>small</small>[/sm] [big]<big>big</big>[/big] [strike]<span class='strike'>strike</span>[/strike]<br />
[color=#f00]<span style=\"color: #f00;\">#f00</span>[/color] [color=#f00000]<span style=\"color: #f00000;\">#f00000</span>[/color] [color=red]<span style=\"color: red;\">red</span>[/color]<br />
[table]<br />[tr][th][/th][/tr]<br />[tr][td][/td][/tr]<br />[/table]<br />
[list][list=1][list=a]<br />
[*] <br />
[/list]<br />
[bq]<br />
blockquote<br />
[/bq]<br />
[url=http://url]name[/url]<br />
[url=mailto:address]name[/url]<br />
[news=#]name[/news]<br />
[page=page]name[/page]<br />
[cat=#]name[/cat]<br />
</small></p></div>";
if ( $enablebbcode != "true" )
{
    $bbcode="";
}
$main->setBBcode($bbcode);
if (!isset($_SESSION['imgkey'])){$_SESSION['imgkey']=rand(1000, 9999);}
if (!isset($_REQUEST['imgkey'])){$_REQUEST['imgkey']=0;}
if (!isset($_SESSION['anonemail'])){$_SESSION['anonemail']="";}
if (!isset($_SESSION['anonname'])){$_SESSION['anonname']="";}
if (!isset($_SESSION['anonhomepage'])){$_SESSION['anonhomepage']="";}
$oldrequestid=rand(1000, 9999);if ( isset($_REQUEST['rid'])){$oldrequestid=$_REQUEST['rid'];}else{$_REQUEST['rid']=$oldrequestid;}
$requestid=rand(1000, 9999);;if ( isset($_SESSION['reqid']) ){$requestid=$_SESSION['reqid'];} 
//}}}
// {{{ Counter
if ( $enablecounter == "true"  )
{
    // Open the file for reading
    $fp = fopen("counterlog.txt", "r");

    // Get the existing count
    $count = fread($fp, 1024);

    // Close the file
    fclose($fp);
    if ($main->isPublicIp($_SERVER['REMOTE_ADDR']))
    {
        if ( !isset($_SESSION['counted']) and !$isbot and $havecookie )
        {
            $count=$count + 1;

            // Reopen the file and erase the contents
            $fp = fopen("counterlog.txt", "w");

            // Write the new count to the file
            fwrite($fp, $count);

            // Close the file
            fclose($fp);
            $_SESSION['counted'] = "1";
        }
    }
}
//}}} Counter
//{{{ Check referer
if ( isset($_SERVER['HTTP_REFERER']) )
{
    if (! preg_match ("/http:\/\/".$_SERVER['HTTP_HOST']."/i", $_SERVER['HTTP_REFERER'])) 
    {
        $main->addreferer( $_SERVER['HTTP_REFERER']  );
    }
}
///}}}
//{{{ browser statistics

    if ( !isset($_SESSION['bstat']))
    {
    $testbrowsercap=ini_get("browscap");
    if ( $testbrowsercap != "")
    {
        if ($main->isPublicIp($_SERVER['REMOTE_ADDR']))
        {
            $browserinfo = get_browser();
            $bstatplatform="";if (isset($browserinfo->platform)){$bstatplatform=$browserinfo->platform;}
            $bstatbrowser="";if (isset($browserinfo->browser)){$bstatbrowser=$browserinfo->browser;}
            $bstatversion="";if (isset($browserinfo->version)){$bstatversion=$browserinfo->version;}
            $bstatcrawler=0;if ("$browserinfo->crawler" == "1" ){$bstatcrawler=$browserinfo->crawler;}
            if ("$bstatplatform$bstatbrowser$bstatversion" != "" )
            {
                $main->updatebrowserstat($bstatplatform,$bstatbrowser,$bstatversion,$bstatcrawler);
            }
        }

    }
    $_SESSION['bstat']="loged";
    }
//}}}

//{{{Login
if ( $page == "login")
{
    if (!isset($_SERVER['HTTP_X_FORWARDED_FOR'])){$_SERVER['HTTP_X_FORWARDED_FOR']="";}
    if (!isset($_SERVER['HTTP_ACCEPT_CHARSET'])){$_SERVER['HTTP_ACCEPT_CHARSET']="";}
    $user="";if ( $_REQUEST['user'] != "" ){$user=$_REQUEST['user'];}
    $passwd="";if ( $_REQUEST['passwd'] != "" ){$passwd=$_REQUEST['passwd'];}
    $passwd=md5($passwd);
    $userdata=$main->login($user, $passwd , true );
    if ( isset($userdata->rows) and $userdata->rows == 1 )
    {
        $userid=$userdata->records[0]['id'];
        $role=$userdata->records[0]['role'];
        $_SESSION['name']=$userdata->records[0]['name'];
        $_SESSION['nr']=$userdata->records[0]['nr'];
        $_SESSION['userid']=$userid;
        $_SESSION['role']=$role;
        $_SESSION['user']=$userdata->records[0]['user'];
        $_SESSION['passwd']=$passwd;
        $_SESSION['email']=$userdata->records[0]['email'];
        $_SESSION['theme']=$userdata->records[0]['theme'];
        //$_SESSION['img']=$userdata->records[0]['img'];
        //$_SESSION['data']=$userdata->records[0]['data'];
        $_SESSION['ip']=$_SERVER['REMOTE_ADDR'];
        $_SESSION['agent']="$_SERVER[HTTP_USER_AGENT]$_SERVER[HTTP_X_FORWARDED_FOR]$_SERVER[HTTP_ACCEPT_LANGUAGE]$_SERVER[HTTP_ACCEPT_CHARSET]";
        $_SESSION['lang']=$userdata->records[0]['lang'];
    }
    else
    {
        print "login failed";
    }
    $page="start";if ( $initpage == "true"){ $page="init";}if ( isset($_REQUEST['nextpage']) ){$page=$_REQUEST['nextpage'];}elseif(isset($_SESSION['lastpage']) ){$page=$_SESSION['lastpage'];}
}
if ( isset($_SESSION['userid']) and $_SESSION['userid'] != 0 )
{
    if (!isset($_SERVER['HTTP_X_FORWARDED_FOR'])){$_SERVER['HTTP_X_FORWARDED_FOR']="";}
    if (!isset($_SERVER['HTTP_ACCEPT_CHARSET'])){$_SERVER['HTTP_ACCEPT_CHARSET']="";}
    if ($_SESSION['ip'] == $_SERVER['REMOTE_ADDR'] and $_SESSION['agent'] == "$_SERVER[HTTP_USER_AGENT]$_SERVER[HTTP_X_FORWARDED_FOR]$_SERVER[HTTP_ACCEPT_LANGUAGE]$_SERVER[HTTP_ACCEPT_CHARSET]" )
    {

        $userid=$_SESSION['userid'];
        $role=$_SESSION['role'];
    }
    else
    {
        $page="logout";
    }
}
//}}}
//{{{ Logout
if ( $page == "logout"  )
{
    $_SESSION['name']="";
    $_SESSION['userid']="0";
    $_SESSION['role']="0";
    $_SESSION['user']="";
    $_SESSION['nr']="$confnr";
    $_SESSION['passwd']="";
    $_SESSION['email']="";
    $_SESSION['img']="";
    $_SESSION['data']="";
    $userid=0;
    $role=0;
    $page="start";if ( $initpage == "true"){ $page="init";}if ( isset($_REQUEST['nextpage']) ){$page=$_REQUEST['nextpage'];}
}
//}}}
//{{{ Set Lang
include_once( "lang/en.php" );

$text=$main->clean_array( $text, false, true );
$main->settext($text);
//}}}


if ($usedbsessions){if (!isset($userid)){$userid=0;}$main->run_query("update sessions set user ='$userid', page = '$page', hits = hits + 1  where session_id = '".session_id()."'");}

//{{{ Download
if ( $page == "dload" )
{
    $id = $_REQUEST['id'];
    $fileinfo=$main->getfileinfo($id);
    if ($fileinfo->rows == "1")
    {
        if ( $fileinfo->records['0']['access'] > $role ){ header("HTTP/1.0 401 Unauthorized",true,401); die("401 Unauthorized");}
        $filename = $fileinfo->records['0']['filename'];
        $file = "$filepath/$id/$filename"; 
        //First, see if the file exists
        if (!is_file($file)) { header("HTTP/1.0 404 Not Found",true,404); die("404 File not found!"); }
        //Gather relevent info about file
        $len = $fileinfo->records['0']['size'];
        $ctype = $fileinfo->records['0']['type']; 
        //Begin writing headers
        header("Pragma: public");
        header("Expires: 0");
        header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
        header("Cache-Control: public");
        if ( !isset($_REQUEST['view']))
        {
            header("Content-Description: File Transfer");
            header("Content-Disposition: attachment; filename=$filename;");
        }
        if ( isset($_REQUEST['view']))
        {
            if ( $_REQUEST['view'] != "true" )
            {
                header("Content-Description: File Transfer");
                header("Content-Disposition: attachment; filename=$filename;");
            } 
        }
        //Use the switch-generated Content-Type
        header("Content-Type: $ctype");

        header("Content-Transfer-Encoding: binary");
        header("Content-Length: ".$len);
        @readfile($file) or die("File not found.");
        exit;
    }
    header("HTTP/1.0 404 Not Found",true,404);
    die("404 File not found.");
}
//}}}

//{{{start of request id limit
if ( "$oldrequestid" == "$requestid" and $havecookie  and !$isbot )
{
    //}}}
//{{{Password recovery
if ( $page == "pwdrec3" )
{
    if (!isset($_SERVER['HTTP_X_FORWARDED_FOR'])){$_SERVER['HTTP_X_FORWARDED_FOR']="";}
    if (!isset($_SERVER['HTTP_ACCEPT_CHARSET'])){$_SERVER['HTTP_ACCEPT_CHARSET']="";}
    if ( $_SESSION['pwdid'] == $_REQUEST['pwdinid'])
    {
        $userdata=$_SESSION['tempuserlogin'];
        $userid=$userdata['id'];
        $role=$userdata['role'];
        $_SESSION['name']=$userdata['name'];
        $_SESSION['nr']=$userdata['nr'];
        $_SESSION['userid']=$userid;
        $_SESSION['role']=$role;
        $_SESSION['user']=$userdata['user'];
        $_SESSION['passwd']=$userdata['passwd'];
        $_SESSION['email']=$userdata['email'];
        $_SESSION['theme']=$userdata['theme'];
        //$_SESSION['img']=$userdata->records[0]['img'];
        //$_SESSION['data']=$userdata->records[0]['data'];
        $_SESSION['ip']=$_SERVER['REMOTE_ADDR'];
        $_SESSION['agent']="$_SERVER[HTTP_USER_AGENT]$_SERVER[HTTP_X_FORWARDED_FOR]$_SERVER[HTTP_ACCEPT_LANGUAGE]$_SERVER[HTTP_ACCEPT_CHARSET]";
        $_SESSION['lang']=$userdata['lang'];
        $page="edituser";
        $_REQUEST['id']=$userid;
    }
    else
    {
        print "login failed";
        $page="pwdrec";
    }
}
//}}}
//{{{ Vote
if ( "$page" == "vote" )
{
    if ( ! isset($_SESSION['vote'][$_REQUEST['id']]) )
    {
        $_SESSION['vote'][$_REQUEST['id']]='v';
        if ( $_REQUEST['value'] < "6" and $_REQUEST['value'] > "0")
        {
            $main->vote($_REQUEST['id'],$_REQUEST['value']);
        }
    }
    $page="start";if ( $initpage == "true"){ $page="init";}if ( isset($_REQUEST['nextpage']) ){$page=$_REQUEST['nextpage'];}elseif(isset($_SESSION['lastpage'])){$page=$_SESSION['lastpage'];}

    if ( isset($_SESSION['lastnr']) and $_SESSION['lastnr'] != "" ){$_REQUEST['nr']=$_SESSION['lastnr'];}
    if ( isset($_SESSION['laststart']) and $_SESSION['laststart'] != "" ){$_REQUEST['start']=$_SESSION['laststart'];}
}
//}}}
//{{{ Start of imgkey sheck
if ( $role > 0 or $_SESSION['imgkey'] == $_REQUEST['imgkey'])
{
//}}}
//{{{ Save news
if ( "$page" == "savenews"  and "$role" > "0" )
{
    $addnews="true";
    $id="";if ( $_REQUEST['id'] != "" ){$id=$_REQUEST['id'];}
    $access="";if ( $_REQUEST['access'] != "" ){$access=$_REQUEST['access'];}else{$addnews="false";}
    $headline="";if ( $_REQUEST['header'] != "" ){$headline=$_REQUEST['header'];}else{$addnews="false";}
    $order="";if ( $_REQUEST['order'] != "" ){$order=$_REQUEST['order'];}else{$order="1";}
    $type="";if ( $_REQUEST['type'] != "" ){$type=$_REQUEST['type'];}else{$type="1";}
    $data="";if ( $_REQUEST['news'] != "" ){$data=$_REQUEST['news'];}else{$addnews="false";}
    $data2="";if ( $_REQUEST['extnews'] != "" ){$data2=$_REQUEST['extnews'];}
    $filename="";if ( isset($_REQUEST['delimg'])){$filename="del";}
    $category="1";
    if ( $_REQUEST['newcategory'] != "" )
    {
        $newcat=$main->addCategory($_REQUEST['newcategory']);
        if ( isset($newcat->lastid) and $newcat->lastid != 0)
        {
            $category=$newcat->lastid;
        }
    }
    elseif($_REQUEST['category'] != "" ){$category=$_REQUEST['category'];}
    else{$addnews="false";}

    if ( "$addnews" == "true" )
    {
        if    ( $type == "1" ){$page="start";}
        elseif( $type == "2" ){$page="newscat";$_REQUEST['catid']=$category;}
        elseif( $type == "3" ){$page="viewnews";}
        elseif( $type == "4" ){$page="init";$main->removeoldinit($access);}
        elseif( $type == "5" ){$page="myhome";$subpage="news";$_REQUEST['id']=$_SESSION['lastuid'];}
        elseif( $type == "6" ){$page="myhome";$subpage="private";}
        elseif( $type == "7" ){$page="admnews";}
        elseif( $type == "8" ){$page="remnews";}
        elseif( $type == "9" ){$page="myhome";$_REQUEST['subpage']="hidden";$_REQUEST['id']=$userid;}
        else                  {$page="start";}
        $_SESSION['lastpage']=$page;
        if ( $role >= "2" )
        {
            if ($filename == "del" or $_FILES['img']['size'] != "0" )
            {
                $thumbdir="./thumb/news/$id/";
                $smalldir="./small/news/$id/";
                $uploaddir="./img/news/$id/";
                if(is_dir($thumbdir))
                {
                    $main->rmdirr($thumbdir);
                }
                if(is_dir($smalldir))
                {
                    $main->rmdirr($smalldir);
                }
                if(is_dir($uploaddir))
                {
                    $main->rmdirr($uploaddir);
                }
            }
            if ($_FILES['img']['size'] != "0")
            {
                $filename=$main->uploadfile( $_FILES['img'] , "news", $id );
            }
        }
        $result = $main->savenews( $id, $access, $headline, $filename, $data, $data2, $order, $category, $type );
    }
    if ( isset($_SESSION['lastnr']) and $_SESSION['lastnr'] != "" ){$_REQUEST['nr']=$_SESSION['lastnr'];}
    if ( isset($_SESSION['laststart']) and $_SESSION['laststart'] != "" ){$_REQUEST['start']=$_SESSION['laststart'];}
}
//}}}
    //{{{ Add news
if ( "$page" == "addnews"  and "$role" != "0" )
{
    $addnews="true";
    $img="";
    $access="";if ( $_REQUEST['access'] != "" ){$access=$_REQUEST['access'];}else{$addnews="false";}
    $owner=$userid;
    $headline="";if ( $_REQUEST['header'] != "" ){$headline=$_REQUEST['header'];}else{$addnews="false";}
    $order="";if ( $_REQUEST['order'] != "" ){$order=$_REQUEST['order'];}else{$order="1";}
    $type="";if ( $_REQUEST['type'] != "" ){$type=$_REQUEST['type'];}else{$type="1";}
    $data="";if ( $_REQUEST['news'] != "" ){$data=$_REQUEST['news'];}else{$addnews="false";}
    $data2="";if ( $_REQUEST['extnews'] != "" ){$data2=$_REQUEST['extnews'];}
    $category="1";
    if ( $_REQUEST['newcategory'] != "" ){
        $newcat=$main->addCategory($_REQUEST['newcategory']);
        if ( isset($newcat->lastid) and $newcat->lastid != 0)
        {
            $category=$newcat->lastid;
        }
    }
    elseif($_REQUEST['category'] != "" ){$category=$_REQUEST['category'];}
    else{$addnews="false";}

    if ( "$addnews" == "true" )
    {
        if    ( $type == "1" ){$page="start";}
        elseif( $type == "2" ){$page="newscat";$_REQUEST['catid']=$category;}
        elseif( $type == "3" ){$page="viewnews";}
        elseif( $type == "4" ){$page="init";$main->removeoldinit($access);}
        elseif( $type == "5" ){$page="myhome";$subpage="news";$_REQUEST['id']=$_SESSION['lastuid'];}
        elseif( $type == "6" ){$page="myhome";$subpage="private";}
        elseif( $type == "7" ){$page="admnews";}
        elseif( $type == "8" ){$page="remnews";}
        elseif( $type == "9" ){$page="myhome";$_REQUEST['subpage']="hidden";$_REQUEST['id']=$userid;}
        else                  {$page="start";}
        $_SESSION['lastpage']=$page;
        
        $filename=str_replace(" ","_",basename($_FILES['img']['name']));
        $filename=str_replace("å","a",$filename);
        $filename=str_replace("ä","a",$filename);
        $filename=str_replace("ö","o",$filename);
        $filename=str_replace("Å","A",$filename);
        $filename=str_replace("Ä","A",$filename);
        $filename=str_replace("Ö","O",$filename);
        $filename=str_replace("(","_",$filename);
        $filename=str_replace(")","_",$filename);
        $filename=ereg_replace("[^a-z,A-Z,0-9,_,.]","_",$filename);

        $result = $main->addnews( $access, $owner, $headline, $filename, $data, $data2, $order, $category, $type );
        if ( $role >= "2" )
        {
            $filenam=$main->uploadfile( $_FILES['img'], "news", $result->lastid );
        }
    }
}
//}}}
//{{{ Remove news
if ( "$page" == "rmnews" and "$role" > "0" )
{
    $id="";if ( isset($_REQUEST['id']) ){$id=$_REQUEST['id'];}
    $main->rmnews( $id, $role );
    if ($_SESSION['lastpage'] == "myhome" ){$_REQUEST['id']=$_SESSION['lastuid'];}
    $page="start";if ( isset($_REQUEST['nextpage']) ){$page=$_REQUEST['nextpage'];}elseif(isset($_SESSION['lastpage']) ){$page=$_SESSION['lastpage'];}
    if ( "$page" == "myhome")
    {
        $_REQUEST['id']=$_SESSION['lastuid'];
        $_REQUEST['subpage']=$_SESSION['lastsubpage'];

    }
    if ( isset($_SESSION['lastnr']) and $_SESSION['lastnr'] != "" ){$_REQUEST['nr']=$_SESSION['lastnr'];}
    if ( isset($_SESSION['laststart']) and $_SESSION['laststart'] != "" ){$_REQUEST['start']=$_SESSION['laststart'];}
}
//}}}
//{{{ Delete news
if ( "$page" == "deletenews" and "$role" >= "3")
{
    $id="";if ( isset($_REQUEST['id']) ){$id=$_REQUEST['id'];}
    $main->delnews( $id, $role );
    $page="start";if ( isset($_REQUEST['nextpage']) ){$page=$_REQUEST['nextpage'];}elseif(isset($_SESSION['lastpage']) ){$page=$_SESSION['lastpage'];}
    if ($page=="viewnews"){$page="start";}
    if ( "$page" == "myhome")
    {
        $_REQUEST['id']=$_SESSION['lastuid'];
        $_REQUEST['subpage']=$_SESSION['lastsubpage'];

    }
    if ( isset($_SESSION['lastnr']) and $_SESSION['lastnr'] != "" ){$_REQUEST['nr']=$_SESSION['lastnr'];}
    if ( isset($_SESSION['laststart']) and $_SESSION['laststart'] != "" ){$_REQUEST['start']=$_SESSION['laststart'];}
}
//}}}
//{{{ Add comment to news
if ( "$page" == "addnewscomment" and ( $role >= 1 or $allowanonaddcomment == 'true' or ( $_SESSION['lastid'] == "-1" and $allowanonaddguestbook == "true" ) ) )
{
    $id="";if ( isset($_SESSION['lastid']) ){$id=$_SESSION['lastid'];}
    $headline="";if ( isset($_REQUEST['header']) ){$headline=$_REQUEST['header'];}
    $data="";if ( isset($_REQUEST['data']) ){$data=$_REQUEST['data'];}
    $anonname="";if ( isset($_REQUEST['name']) ){$anonname=$_REQUEST['name'];}
    $_SESSION['anonname']=$anonname;
    $anonemail="";if ( isset($_REQUEST['email']) ){$anonemail=$_REQUEST['email'];}
    $_SESSION['anonemail']=$anonemail;
    $homepage="";if ( isset($_REQUEST['homepage'])){$homepage=$_REQUEST['homepage'];}
    $_SESSION['anonhomepage']=preg_replace("#(\<a)(.*?)(\>)(.*?)(\</a\>)#is","$4",$homepage);
    if ( $data != "" ){$main->addcomment( $userid, 1, $id, $headline, $data, $anonname, $anonemail,$homepage );}
    $page=$_SESSION['lastpage'];
    if ( isset($_SESSION['lastnr']) and $_SESSION['lastnr'] != "" ){$_REQUEST['nr']=$_SESSION['lastnr'];}
    if ( isset($_SESSION['laststart']) and $_SESSION['laststart'] != "" ){$_REQUEST['start']=$_SESSION['laststart'];}
}
//}}}
//{{{Save comment
if ( "$page" == "savecomment"  and $role >= 1 )
{
    $page=$_SESSION['lastpage'];
    $id="";if ( isset($_REQUEST['id']) ){$id=$_REQUEST['id'];}
    $headline="";if ( isset($_REQUEST['header']) ){$headline=$_REQUEST['header'];}
    $data="";if ( isset($_REQUEST['data']) ){$data=$_REQUEST['data'];}
    $anonname="";if ( isset($_REQUEST['name']) ){$anonname=$_REQUEST['name'];}
    $anonemail="";if ( isset($_REQUEST['email']) ){$anonemail=$_REQUEST['email'];}
    $homepage="";if ( isset($_REQUEST['homepage']) ){$homepage=$_REQUEST['homepage'];}
    if ( $headline != "" and $data != "" ){$main->savecomment( $userid, $role, $id, $headline, $data, $anonname, $anonemail, $homepage);}
    $_REQUEST['id']=$_SESSION['lastid'];
    if ( isset($_SESSION['lastnr']) and $_SESSION['lastnr'] != "" ){$_REQUEST['nr']=$_SESSION['lastnr'];}
    if ( isset($_SESSION['laststart']) and $_SESSION['laststart'] != "" ){$_REQUEST['start']=$_SESSION['laststart'];}
}
//}}}
// {{{ Remove comments
if ( "$page" == "rmcomment"  and $role >= 1 )
{
    $page=$_SESSION['lastpage'];
    $id="";if ( isset($_REQUEST['id']) ){$id=$_REQUEST['id'];}
    if ( $id != "" )
    {
        $main->rmcomment( $userid, $role, $id);
    }
    $_REQUEST['id']=$_SESSION['lastid'];
    if ( isset($_SESSION['lastnr']) and $_SESSION['lastnr'] != "" ){$_REQUEST['nr']=$_SESSION['lastnr'];}
    if ( isset($_SESSION['laststart']) and $_SESSION['laststart'] != "" ){$_REQUEST['start']=$_SESSION['laststart'];}
}
//}}}
// {{{ Delete comment
if ( "$page" == "deletecomment" and $role == 4 )
{
    $page=$_SESSION['lastpage'];
    $id="";if ( isset($_REQUEST['id']) ){$id=$_REQUEST['id'];}
    if ( $id != "" )
    {
        $main->deletecomment( $id);
    }
    $_REQUEST['id']=$_SESSION['lastid'];
    if ( isset($_SESSION['lastnr']) and $_SESSION['lastnr'] != "" ){$_REQUEST['nr']=$_SESSION['lastnr'];}
    if ( isset($_SESSION['laststart']) and $_SESSION['laststart'] != "" ){$_REQUEST['start']=$_SESSION['laststart'];}
}
//}}}
//{{{ Add user
if ( "$page" == "adduser" and (("$role" == "0" and $allowregister == "true" ) or "$role" >= "3" ))
{
    $adduser="true";
    $img="";
    $newrole="";if ( $_REQUEST['role'] != "" ){$newrole=$_REQUEST['role'];}else{$adduser="false";}
    $newname="";if ( $_REQUEST['name'] != "" ){$newname=$_REQUEST['name'];}else{$adduser="false";}
    $newuser="";if ( $_REQUEST['nuser'] != "" ){$newuser=$_REQUEST['nuser'];}else{$adduser="false";}
    $newemail="";if ( $_REQUEST['email'] != "" ){$newemail=$_REQUEST['email'];}
    $newdata="";if ( $_REQUEST['data'] != "" ){$newdata=$_REQUEST['data'];}
    $newlang="";if ( $_REQUEST['lang'] != "" ){$newlang=$_REQUEST['lang'];}else{$adduser="false";}
    $newpwd1="";if ( $_REQUEST['pwd1'] != "" ){$newpwd1=$_REQUEST['pwd1'];}else{$adduser="false";}
    $newpwd2="";if ( $_REQUEST['pwd2'] != "" ){$newpwd2=$_REQUEST['pwd2'];}else{$adduser="false";}
    $homepage="";if ( $_REQUEST['homepage'] != "" ){$homepage=$_REQUEST['homepage'];}
    $usetheme="default";
    if ( $allowusertheme == "true" and $_REQUEST['usetheme'] != "" )
    {
        $usetheme=$_REQUEST['usetheme'];
        if ( !is_file("themes/$usetheme/site.css"))
        {
            $usetheme="default";
        }
    }
    if( $allowusertheme != "true"){$usetheme="default";}
    $nr=$confnr;if ( isset($_REQUEST['nr'])){$nr=$_REQUEST['nr'];}
    if ( "$adduser" == "true" and ( "$role" >= "$newrole" or "$newrole" == "1" )and "$newpwd1" == "$newpwd2" )
    {
        $filename="";
        if ( isset($_FILES['img']))
        {
            $filename=str_replace(" ","_",basename($_FILES['img']['name']));
            $filename=str_replace("å","a",$filename);
            $filename=str_replace("ä","a",$filename);
            $filename=str_replace("ö","o",$filename);
            $filename=str_replace("Å","A",$filename);
            $filename=str_replace("Ä","A",$filename);
            $filename=str_replace("Ö","O",$filename);
            $filename=str_replace("(","_",$filename);
            $filename=str_replace(")","_",$filename);
            $filename=ereg_replace("[^a-z,A-Z,0-9,_,.]","_",$filename);
        }
        $result = $main->adduser( $newrole,$nr,$usetheme,$newname,$newuser,$newemail,$newdata, md5($newpwd1), $filename, $newlang, $homepage  );
        $_REQUEST['id']=$result->lastid;
        $_REQUEST['nextpage']="myhome";
        if ($newusermailtoadmin)
        {
            $admins=$main->run_query("SELECT email FROM `user` where role=4;");
            foreach($admins->records as $adminemails )
            {
                $main->sendMail( "$adminemails[email]" , $main->decode("$sitetitle: $text[useradded]"), $main->decode("$text[name] $newname\n$text[email] $newemail\n$text[description]\n$newdata") , "$adminemail");
            }
        }
        if ( $role >= "2" and isset($_FILES['img']) )
        {
            $filename=$main->uploadfile( $_FILES['img'] , "user", $result->lastid  );
        }
    }
    $page="start";if ( isset($_REQUEST['nextpage']) ){$page=$_REQUEST['nextpage'];}elseif(isset($_SESSION['lastpage']) ){$page=$_SESSION['lastpage'];}
    
}
//}}}
//{{{ Save user
if ( "$page" == "saveuser" )
{
    $adduser="true";
    $newid="";if ( $_REQUEST['id'] != "" ){$newid=$_REQUEST['id'];}else{$adduser="false";}
    $newrole="";if ( $_REQUEST['role'] != "" ){$newrole=$_REQUEST['role'];}else{$adduser="false";}
    $newname="";if ( $_REQUEST['name'] != "" ){$newname=$_REQUEST['name'];}else{$adduser="false";}
    $newemail="";if ( $_REQUEST['email'] != "" ){$newemail=$_REQUEST['email'];}
    $newdata="";if ( $_REQUEST['data'] != "" ){$newdata=$_REQUEST['data'];}
    $newlang="";if ( $_REQUEST['lang'] != "" ){$newlang=$_REQUEST['lang'];}else{$adduser="false";}
    $newpwd1="";if ( $_REQUEST['pwd1'] != "" ){$newpwd1=$_REQUEST['pwd1'];}
    $newpwd2="";if ( $_REQUEST['pwd2'] != "" ){$newpwd2=$_REQUEST['pwd2'];}
    $homepage="";if ( $_REQUEST['homepage'] != "" ){$homepage=$_REQUEST['homepage'];}
    $filename="";if ( isset($_REQUEST['delimg'])){$filename="del";}
    $usetheme="default";
    if (  $allowusertheme == "true" and $_REQUEST['usetheme'] != "" )
    {
        $usetheme=$_REQUEST['usetheme'];
        if ( !is_file("themes/$usetheme/site.css"))
        {
            $usetheme="default";
        }
        elseif( $newid == $userid )
        {
            $_SESSION['theme']="$usetheme";
        }
    }
    $nr=$confnr;if ( isset($_REQUEST['nr'])){$nr=$_REQUEST['nr'];}
    if ( "$role" <= "2" )
    {
        $newrole=$role;
        $newid=$userid;
    }
    if ( "$adduser" == "true" and ( "$role" >= "$newrole" or "$newrole" == "1" ) and "$newpwd1" == "$newpwd2"  )
    {
        if ( $role >= "2" )
        {
            if ($filename == "del" or $_FILES['img']['size'] != "0" )
            {
                $thumbdir="./thumb/user/$newid/";
                $smalldir="./small/user/$newid/";
                $uploaddir="./img/user/$newid/";
                if(is_dir($thumbdir))
                {
                    $main->rmdirr($thumbdir);
                }
                if(is_dir($smalldir))
                {
                    $main->rmdirr($smalldir);
                }
                if(is_dir($uploaddir))
                {
                    $main->rmdirr($uploaddir);
                }
            }
            if ( $_FILES['img']['size'] != "0")
            {
                $filename=$main->uploadfile( $_FILES['img'] , "user", $newid );
            }
        }
        if ( "$newpwd1" != "" )
        {
            $main->saveuser( $newid, $newrole, $nr,$usetheme, $newname, $newemail,$newdata, md5($newpwd1), $filename, $newlang, $homepage  );
        }
        else
        {
            $main->saveuser( $newid, $newrole, $nr,$usetheme, $newname, $newemail,$newdata, "", $filename, $newlang, $homepage  );
        }
        if ( $userid == $newid )
        {
            $_SESSION['lang']=$newlang;
            $_SESSION['nr']=$nr;
            $_SESSION['name']=$newname;
            $_SESSION['email']=$newemail;
            include_once( "lang/en.php" );
            $text=$main->clean_array( $text, false, true );
            $main->settext($text);
        }
    }
    $page="start";if ( isset($_REQUEST['nextpage']) ){$page=$_REQUEST['nextpage'];}elseif(isset($_SESSION['lastpage']) ){$page=$_SESSION['lastpage'];}
}
//}}}
//{{{ Remove user
if ( "$page" == "rmuser" and "$role" >= "3"  )
{
    $id="";if ( $_REQUEST['id'] != "" ){$id=$_REQUEST['id'];}
    $main->rmuser( $id );
    $page="start";if ( isset($_REQUEST['nextpage']) ){$page=$_REQUEST['nextpage'];}elseif(isset($_SESSION['lastpage']) ){$page=$_SESSION['lastpage'];}
    if ( $page == "userhome"){$page="start";if ( $initpage == "true"){ $page="init";}}
}
//}}}
//{{{Edit abbr
if ( $page == "editabbr" and $role >= "3"  )
{
    if (isset($_REQUEST['deleteid']))
    {
        $main->delabbr($_REQUEST['deleteid']);
    }
    if (isset($_REQUEST['do']))
    {
        if ($_REQUEST['do'] == "save")
        {
            $main->saveabbr($_REQUEST['id'], $_REQUEST['type'], $_REQUEST['word'] , $_REQUEST['title'], $_REQUEST['abbrdata']);
        }
        elseif ($_REQUEST['do'] == "add")
        {
            $main->addabbr( $_REQUEST['type'], $_REQUEST['word'] , $_REQUEST['title'], $_REQUEST['abbrdata'] );
        }
    }
}
//}}}
//{{{ Delete user
if ( "$page" == "deluser" and "$role" >= "4" )
{
    $id="";if ( $_REQUEST['id'] != "" ){$id=$_REQUEST['id'];}
    $main->deluser( $id );
    $page="start";if ( isset($_REQUEST['nextpage']) ){$page=$_REQUEST['nextpage'];}elseif(isset($_SESSION['lastpage']) ){$page=$_SESSION['lastpage'];}
    if ( isset($_SESSION['lastnr']) and $_SESSION['lastnr'] != "" ){$_REQUEST['nr']=$_SESSION['lastnr'];}
    if ( isset($_SESSION['laststart']) and $_SESSION['laststart'] != "" ){$_REQUEST['start']=$_SESSION['laststart'];}
    if ( $page == "userhome" or $page == "myhome" ){$page="start";if ( $initpage == "true"){ $page="init";}}
}
//}}}
//{{{end of request id limit
}
}
//}}}
//{{{ Update request id
$requestid=rand(1000, 9999);
$_SESSION['reqid']=$requestid;

//}}}

//{{{ HTML header
/*print "<?xml version=\"1.0\" encoding=\"ISO-8859-15\"?>\n";*/
print "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n\n";
//print "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"\n   \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n";
print "<html  xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n<title>$sitetitle</title>\n<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-15' />\n";
if ( $page == "changetheme" and $allowusertheme == "true")
{
    $_SESSION['theme']=$_REQUEST['theme'];
    $page="start";if ( isset($_REQUEST['nextpage']) ){$page=$_REQUEST['nextpage'];}elseif(isset($_SESSION['lastpage'])){$page=$_SESSION['lastpage'];}
    if ( isset($_SESSION['lastnr']) and $_SESSION['lastnr'] != "" ){$_REQUEST['nr']=$_SESSION['lastnr'];}
    if ( isset($_SESSION['laststart']) and $_SESSION['laststart'] != "" ){$_REQUEST['start']=$_SESSION['laststart'];}
}

if ( isset($_SESSION['theme']))
{
    if ($_SESSION['theme'] != "default")
    {
        $stylesheet="themes/$_SESSION[theme]/site.css";
    }
}
print "<link rel='stylesheet' href='$stylesheet' type='text/css'></link>\n";
print "<meta content='$keywords' name='keywords'></meta>\n";
print "<meta content='$description' name='description'></meta>\n";
if ( "$enablerss" == "true" )
{
    if ( "$role" != "0" ){print "<link rel='alternate' type='text/xml' title='RSS' href='rss.php?user=$_SESSION[user]&amp;passwd=$_SESSION[passwd]'></link>\n";}
    else {print "<link rel='alternate' type='text/xml' title='RSS' href='rss.php'></link>\n";}
}
if ( $enablesplash and ($page=="" or $page=="splash" ))
{
    $page2="start";if ( $initpage == "true"){ $page2="init";}
    if ($splashtimer!=0)
    {
        print "<meta http-equiv='refresh' content='$splashtimer;url=?page=$page2' />";
    }
}
    
print "</head>\n";
$bodyclass="gray";
if ( !isset($_REQUEST['textsize']) and isset($_SESSION['textsize']) )
{
    $_REQUEST['textsize']=$_SESSION['textsize'];
}
if (isset($_REQUEST['textsize']))
{
    if( $_REQUEST['textsize'] == "s" )
    {
        $bodyclass="graysmall";
    }
    if( $_REQUEST['textsize'] == "n" )
    {
        $bodyclass="gray";
    }
    if( $_REQUEST['textsize'] == "l" )
    {
        $bodyclass="graylarge";
    }
    $_SESSION['textsize']=$_REQUEST['textsize'];
    
}
print "<body class='$bodyclass'>\n";
print "<table class='main' summary='main table'><tr><td class='tls'></td><td class='ts'></td><td class='trs'></td></tr><tr><td class='ls'></td>";
if ($page=="splash"){print "<td valign='middle' align='center'>\n";}else{print "<td valign='top'>\n";}
//}}}
//{{{ splach
if ( $enablesplash and ($page=="" or $page=="splash" ))
{
    $page2="start";if ( $initpage == "true"){ $page2="init";}
    print "<a href='?page=$page2'><img src='$splashimage' alt='$sitetitle' /></a>";
}
//}}}
//{{{ Top part
//start splash check
if ($page!="splash")
{
print "<table summary='Main table'>\n";
print "<tr><td><img src='$logo' alt='LOGO' width='$logowidth' /></td><td align='right' class='headerbottom'><p>&nbsp;</p>\n";
if ( $enablesearch == 'true' )
{
    $searchvalue="";
    $search="";if ( isset($_REQUEST['search']) ){$search=$_REQUEST['search'];}
    if ( $search == "" and $page == "search" and $_SESSION['lastpage']=="search" and isset($_SESSION['searchstr']) ){$search=$_SESSION['searchstr'];}
    if ( $search != "" ){$searchvalue="value='$search'";}
    print "<form enctype='multipart/form-data' action='?page=search' method='post'><p><input type='hidden' name='rid' value='$requestid' />";
    print "<label for='search'>$text[search]: </label><input name='search' type='text' id='search' alt='search' $searchvalue />&nbsp;";
    print "<input type='submit' value='$text[search]' id='searchbuttom' class='button'/>&nbsp;<input type='reset' value='$text[reset]' class='button'/></p></form>";
}
print "</td><td align='right' class='headermiddle'>\n";
print "<table summary='information table'>";
foreach ($siteheader as $headerline)
{
    print "<tr><td align='right' class='menusmall'><b>$headerline[1]</b></td>";
    print "<td align='left' class='menusmall'>$headerline[2]</td></tr>";
}
print "</table>";
print "</td></tr></table><table summary='Main table'>\n";
//}}}
//{{{ Menu
print "<tr><td valign='top' class='menu'>\n";

if ( $initpage == "true" )
{
    print "<a href='?page=init'>$text[home]</a>&nbsp;<br />\n";	
}

$menu = $main->getmenu( $role, $userid );
$lastaccess=0;
foreach( $menu->records as $item )
{
    $curaccess=$item['access'];
    if ( "$lastaccess" != "$curaccess" )
    {
        print "<br />\n";
    }
    $lastaccess=$curaccess;
    $menuitem="";
    if (isset($text[ $item['data'] ])){$menuitem=str_replace(" ","&nbsp;",$text[ $item['data'] ]);}
    if ($menuitem == ""){$menuitem=$item['data'];}
    print "<a href='?page=$item[data]'>$menuitem</a>&nbsp;<br />\n";
}
$newslinks=$main->getmenunewslist($role);
if ($newslinks->rows != "0" )
{
    print "<br />\n";
    foreach( $newslinks->records as $item )
    {
        $menuitem=str_replace(" ","&nbsp;",$item['headline']);
        print "<a href='?page=viewnews&amp;id=$item[id]'>$menuitem</a>&nbsp;<br />\n";
    }
}
$category = $main->getCategories($role);
if ($category->rows != "0" )
{
    print "<br />$text[category]<br />\n";
    foreach( $category->records as $item )
    {
        $menuitem=str_replace(" ","&nbsp;",$item['name']);
        //if ( isset($text[$item['name']])){$menuitem=str_replace(" ","&nbsp;",$text[$item['name']]);}
        print "<a href='?page=newscat&amp;catid=$item[id]'>$menuitem</a>&nbsp;<br />\n";
    }
}

if ( $enablerss == "true" and "$userid" != "0" )
{
    print "<br /><a href='rss.php?user=$_SESSION[user]&amp;passwd=$_SESSION[passwd]'><img src='images/rss.gif' alt='$text[rss]'/></a>&nbsp;<br />\n";
    print "<a href='atom.php?user=$_SESSION[user]&amp;passwd=$_SESSION[passwd]'><img src='images/atom.gif' alt='$text[atom]'/></a>&nbsp;<br />\n";
}
elseif ( $enablerss == "true" )
{
    print "<br /><a href='rss.php'><img src='images/rss.gif' alt='$text[rss]'/></a>&nbsp;<br />\n";
    print "<a href='atom.php'><img src='images/atom.gif' alt='$text[atom]'/></a>&nbsp;<br />\n";
}

if ( $allowusertheme == "true" and "$userid" == "0")
{
    print "<br /><form action='?'><p><select onchange=\"location=this.options[this.selectedIndex].value;\">\n";
    $d=dir("themes");
    $curtheme="";
    if ( isset($_SESSION['theme']))
    {
        $curtheme=$_SESSION['theme'];
    }
    print "<option value='?page=changetheme&amp;theme=default'>$text[default]</option>\n";
    while($entry = $d->read()) 
    {
        $entry=str_replace(".php","" ,$entry);
        if( is_dir("themes/$entry") and $entry != "." and $entry != ".." and is_file("themes/$entry/site.css"))
        {
            $selected="";
            if ($entry == $curtheme ){$selected="selected=selected";}
            print "<option value='?page=changetheme&amp;theme=$entry' $selected>$entry</option>\n";
        }
    }
    print "</select></p></form>\n";
}
else
{
    print "<br />\n";
}
$textsizeurl="";
if(isset($_REQUEST['nr'])){$textsizeurl.="&amp;nr=$_REQUEST[nr]";}
if(isset($_REQUEST['start'])){$textsizeurl.="&amp;start=$_REQUEST[start]";}
if(isset($_REQUEST['id'])){$textsizeurl.="&amp;id=$_REQUEST[id]";}
print "<a href='?page=$page&amp;textsize=s&amp;rid=$requestid$textsizeurl' class='small' rel='nofollow'>A</a>";
print "<a href='?page=$page&amp;textsize=n&amp;rid=$requestid$textsizeurl' class='normal' rel='nofollow'>A</a>";
print "<a href='?page=$page&amp;textsize=l&amp;rid=$requestid$textsizeurl' class='large' rel='nofollow'>A</a>";
print "<br />\n";
if ( "$userid" == "0" and $showlogin == "true")
{
    print "<br /><hr /><form action='?page=login' method='post'><p><input type='hidden' name='rid' value='$requestid' />\n";
    print "<label for='user'>$text[user]</label><br /><input type='text' alt='user' id='user' name='user' size='10'/><br />\n";
    print "<label for='passwd'>$text[passwd]</label><br /><input type='password' alt='password' id='passwd' name='passwd' size='10'/><br />\n";
    print "<input type='submit' value='$text[login]' id='login' class='button' /><br />\n";
    if ( $allowregister == "true" )
    {
        print "<a href='?page=newuser' rel='nofollow'>$text[register]</a>&nbsp;\n";
    }
    print "</p></form><a href='?page=pwdrec&amp;rid=$requestid' rel='nofollow'>".str_replace(" ","&nbsp;",$text['pwdrecovery'])."</a><hr />\n";
    
}
elseif ( "$userid" != "0")
{
    print "<br /><hr />$text[logedinas]<br /><a href='?page=myhome&amp;rid=$requestid'>$_SESSION[name]</a>&nbsp;\n";
    print "<br />".$text["access$role"]."\n";
    print "<br /><a href='?page=logout&amp;rid=$requestid'>$text[logout]</a>&nbsp;<hr />\n";
}
if ( $cookieinfo == "true" )
{
   print "<br /><a href='?page=cookie'>".str_replace(" ","&nbsp;",$text['cookieheader'])."</a><br /><br />";
}
print "</td><td valign='top' colspan='2' rowspan='2'>\n";
//if ( isset($_SESSION['nr'])){$_SESSION['lastnr']=$_SESSION['nr'];}
//elseif( $page != "editnews" and $page != "savenews" ){$_SESSION['lastnr']="";}

if ( isset($_REQUEST['start'])){$_SESSION['laststart']=$_REQUEST['start'];}
elseif( $page != "editnews" and $page != "savenews" ){$_SESSION['laststart']="";}
//End splash shech
}
//}}}
//{{{ Init page
if ("$page" == "init" or ("$page" == "" and $initpage == "true" ) )
{
    $_SESSION['lastpage']=$page;
    $news = $main->getinitnews($role);
    $main->incresenewsviews($news->records['0']['id']);
    $main->printnews( $news,1,$role,$userid,"-1","-1",$page,"" );	
}
//}}}
//{{{Start page
if ( "$page" == "start" or ("$page" == "" and $initpage != "true" ) )
{
    $_SESSION['lastpage']=$page;
    $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
    $news = $main->getnews( $role , 1 , $start , $nr);
    $nrofnews = $main->getnrnews( $role, 1);
    $nrofnews = $nrofnews->records[0]['nr'];
    $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"" );
}
//}}}
//{{{Search page
if ( "$page" == "search" )
{
    $_SESSION['lastpage']=$page;
    $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
    $search="";if ( isset($_REQUEST['search']) ){$search=$_REQUEST['search'];$_SESSION['searchstr']=$search;}elseif ( isset($_SESSION['searchstr']) ){$search=$_SESSION['searchstr'];}
    $news = $main->search( $search, $role , $start , $nr);
    $nrofnews = $main->searchnr( $search, $role );
    $nrofnews = $nrofnews->records[0]['nr'];
    $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"" );	
}
//}}}
//{{{ Toplist page
if ( "$page" == "top" )
{
    $_SESSION['lastpage']=$page;
    $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
    $news = $main->gettopnews( $role , $start , $nr);
    $nrofnews = $main->getnrtopnews( $role);
    $nrofnews = $nrofnews->records[0]['nr'];
    $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"" );	
}
//}}}
//{{{ Toplist view page
if ( "$page" == "topview" )
{
    $_SESSION['lastpage']=$page;
    $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
    $news = $main->gettopviewnews( $role , $start , $nr);
    $nrofnews = $main->getnrtopnews( $role);
    $nrofnews = $nrofnews->records[0]['nr'];
    $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"" );	
}
//}}}
//{{{Top comments page
if ( "$page" == "topcomment" )
{
    $_SESSION['lastpage']=$page;
    $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
    $news = $main->gettopcommentnews( $role, $start, $nr);
    $nrofnews = $main->getnrtopnews( $role);
    $nrofnews = $nrofnews->records[0]['nr'];
    $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"" );	
}
//}}}
//{{{ Category page
if ( "$page" == "newscat" )
{
    $_SESSION['lastpage']=$page;
    $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
    $cat="1";if ( isset($_REQUEST['catid']) ){$cat=$_REQUEST['catid'];}elseif ( isset($_SESSION['catid']) ){$cat=$_SESSION['catid'];}
    $_SESSION['catid']=$cat;
    $news = $main->getcatnews( $role, $start , $nr, $cat);
    $nrofnews = $main->getcatnrnews( $role, $cat);
    $nrofnews = $nrofnews->records[0]['nr'];
    $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"" );  
}
//}}}
//{{{ Guestbook
if ( "$page" == "guestbook" )
{ 
    $_SESSION['lastpage']=$page;
    $cstart=0;if ( isset($_REQUEST['cstart']) ){$cstart=$_REQUEST['cstart'];}
    $cnr=$nr;if ( isset($_REQUEST['cnr']) ){$cnr=$_REQUEST['cnr'];}
    $main->printcomments( "0", $role,$userid,$cstart,$cnr,$page,-1);
    $_SESSION['lastid']="0";
}
//}}}
//{{{ Removed comments
if ( "$page" == "removedcomments" and $role >= 3)
{ 
    $_SESSION['lastpage']=$page;
    $cstart=0;if ( isset($_REQUEST['cstart']) ){$cstart=$_REQUEST['cstart'];}
    $cnr=$nr;if ( isset($_REQUEST['cnr']) ){$cnr=$_REQUEST['cnr'];}
    $main->printcomments( "-1", $role,$userid,$cstart,$cnr,$page,-1);
    $_SESSION['lastid']="-1";
}
//}}}
//{{{ Edit comment
if ( $page == "editcomment" and $role >= 1)
{
    print "<script type='text/javascript'>
        function validate(form)
        {
            error=\"\";
            if ( form.header.value == \"\" )
            {
                error=\"".str_replace(":",","," ".$main->edit_array( $text['header'])." ")."\";
            }

            if ( form.data.value == \"\" )
            {
                error=error+\"".str_replace(":",""," ".$main->edit_array( $text['comment'])." ")."\";
            }
            if (error != '' )
            {
                error=error.replace(\":\", \",\");
                alert('".$main->edit_array( $text['missingfields'])."'+' '+error);
                return;
            }
            else
            {
                form.submit();
            }
        }
    </script>";
    $id="";if ( isset($_REQUEST['id']) ){$id=$_REQUEST['id'];}
    $comment=$main->edit_array($main->getcomment( $userid, $role, $id ));
    print "<form enctype='multipart/form-data' action='?page=savecomment' method='post'><p><input type='hidden' name='rid' value='$requestid' /></p>\n";
    print "<table summary='$text[editcomment]'><tr><td colspan='2'><hr></td></tr>\n";
    if ( $comment['records']['0']['role'] == 0  )
    {
        print "<tr><td>$text[name]</td><td><input name='name' type='text' id='name' value='" . $comment['records']['0']['anonname'] . "'/></td></tr>\n";
        print "<tr><td>$text[email]</td><td><input name='email' type='text' id='email' value='" . $comment['records']['0']['anonemail'] . "'/></td></tr>\n";
        print "<tr><td>$text[homepageheader]</td><td><input name='homepage' type='text' id='email' value='" . $comment['records']['0']['anonhomepage'] . "'/></td></tr>\n";
    }
    print "<tr><td>$text[header]</td><td><input name='header' type='text' id='header' value='" . $comment['records']['0']['headline'] . "'/></td></tr>\n";
    print "<tr><td colspan='2'>$text[comment]</td></tr>\n";
    print "<tr><td colspan='2'><input type='hidden' name='id' value='" . $comment['records']['0']['id'] . "'><textarea name='data' rows='5' cols='60'>" . $comment['records']['0']['data'] . "</textarea></td></tr>\n";
    print "<tr><td colspan='2'><input type='button' value='$text[savecomment]' id='savecomment' onclick=\"validate(this.form)\"  class='button'/> <input type='reset' value='$text[reset]' class='button' /></td></tr>\n";
    print "</table></form>\n";
    print "$bbcode";

}
//}}}
//{{{ Remnews
if ( "$page" == "remnews"  and "$role" >= "3" )
{
    $_SESSION['lastpage']=$page;
    $start="0";if ( isset($_REQUEST['start'])){$start=$_REQUEST['start'];}
    $news = $main->getnews( 4 , 8 , $start , $nr);
    $nrofnews = $main->getnrnews( 4, 8);
    $nrofnews = $nrofnews->records[0]['nr'];
    $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"" );	
}
//}}}
//{{{ Downloads
if ( $page == "downloads")
{
    print "<span class=\"headline\"><b>$text[downloads]</b></span><br />";
    $dir="/";if( isset($_REQUEST['dir'])){$dir=$_REQUEST['dir'];}
    if ( !isset($_REQUEST['do']) )
    {
        $_REQUEST['do']="";
    }
    if ( $role >= 3 or $role >= $uploadfileaccess )
    {
        if($_REQUEST['do'] == "upload" and isset($_FILES['file']['name']))
        {
            $filename=str_replace(" ","_",basename($_FILES['file']['name']));
            $filename=str_replace("å","a",$filename);
            $filename=str_replace("ä","a",$filename);
            $filename=str_replace("ö","o",$filename);
            $filename=str_replace("Å","A",$filename);
            $filename=str_replace("Ä","A",$filename);
            $filename=str_replace("Ö","O",$filename);
            $filename=str_replace("(","_",$filename);
            $filename=str_replace(")","_",$filename);
            $filename=ereg_replace("[^a-z,A-Z,0-9,_,.]","_",$filename);

            $fname=$_REQUEST['fname'];
            $access=$_REQUEST['access'];

            $dir=$_REQUEST['dir'];
            $subdir=$_REQUEST['subdir'];
            $parrentdir=$_REQUEST['parentdir'];
            if ( $subdir != "" )
            {
                $parrentdir=$dir;
                $dir=$subdir;
            }

            $type=$_FILES['file']['type'];
            $owner=$userid; 
            $size=$_FILES['file']['size'];

            $newid=$main->addfile($filename,$fname,$access,$dir,$parrentdir,$type,$owner,$size);
            if ( ! $main->uploadanyfile($_FILES['file'],"$filepath/$newid/"))
            {
                $main->deletefile($newid);
            }
        }
        
        if($_REQUEST['do'] == "save" and isset($_REQUEST['id']))
        {
            $access=$_REQUEST['access'];

            $dir=$_REQUEST['dir'];
            $subdir=$_REQUEST['subdir'];
            $parrentdir=$_REQUEST['parentdir'];
            $fname=$_REQUEST['fname'];
            if ( $subdir != "" )
            {
                $parrentdir=$dir;
                $dir=$subdir;
            }
            $newid=$_REQUEST['id'];
            $main->savefile($access, $dir, $parrentdir,$fname,$newid);
        }
        if ($_REQUEST['do'] == "delete" and isset($_REQUEST['id']))
        {
            if ($_REQUEST['id'] > 0 )
            {
                $main->deletefile($_REQUEST['id']);
            }
        }
        if ($_REQUEST['do'] == "edit" and isset($_REQUEST['id']))
        {
        $fileinfo=$main->getfileedit($_REQUEST['id']);
        print "<script type='text/javascript'>
            function savevalidate(form)
            {
                error=\"\";
                if ( form.fname.value == \"\" )
                {
                    error=\"".str_replace(":",","," ".$main->edit_array( $text['fname'])." ")."\";
                }
                if (error != '' )
                {
                    error=error.replace(\":\", \",\");
                    alert('".$main->edit_array( $text['missingfields'])."'+' '+error);
                    return;
                }
                else
                {
                    form.submit();
                }
            }
        </script>";
        print "<br /><br /><form enctype='multipart/form-data' action='?page=downloads' method='post'>
            <table><tr><td>
            <input type='hidden' name='rid' value='$requestid' />
            <input type='hidden' name='id' value='$_REQUEST[id]' />
            <input type='hidden' name='do' value='save' />
            <input type='hidden' name='parentdir' value='".$fileinfo->records['0']['parrentdir']."' />
            <input type='hidden' name='dir' value='$dir' />
            $text[filename]</td><td>".$fileinfo->records['0']['filename']."</td></tr>
            <tr><td>$text[size]</td><td>".$fileinfo->records['0']['size']."</td></tr>
            <tr><td>$text[uploaded]</td><td>".$fileinfo->records['0']['date']."</td></tr>
            \n";
        print "<tr><td><label for='fname'>$text[fname]</label></td><td><input name='fname' type='text' id='fname' value='".$fileinfo->records['0']['name']."'/></td></tr>";
        print "<tr><td><label for='subdir'>$text[subdir]</label></td><td><input name='subdir' type='text' id='subdir' value='".$fileinfo->records['0']['dir']."'/></td></tr>";
        print "<tr><td><label for='access'>$text[access]</label></td><td><select name='access'>";
        $editedfileaccess=$fileinfo->records['0']['access'];
        $selected="";
        if ( $editedfileaccess == 0 ){$selected="selected=selected";}else{$selected="";}
        print "<option value='0' $selected>$text[noaccess]</option>\n";
        if ( $editedfileaccess == 1 ){$selected="selected=selected";}else{$selected="";}
        print "<option value='1' $selected>$text[limiteduser]</option>\n";
        if ( $editedfileaccess == 2 ){$selected="selected=selected";}else{$selected="";}
        print "<option value='2' $selected>$text[normaluser]</option>\n";
        if ( $editedfileaccess == 3 ){$selected="selected=selected";}else{$selected="";}
        print "<option value='3' $selected>$text[moderator]</option>\n";
        if ( $editedfileaccess == 4 ){$selected="selected=selected";}else{$selected="";}
        if ( "$editedfileaccess" == "0" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" or ($allowuserstoaddannonnews and $role >= "1" ) ){print "<option $selected value='0'>$text[access0]</option>\n";}
        if ( "$editedfileaccess" == "1" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" or ($allowuserstoaddannonnews and $role >= "1" ) ){print "<option $selected value='1'>$text[access1]</option>\n";}
        if ( "$editedfileaccess" == "2" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "2" ){print "<option $selected value='2'>$text[access2]</option>\n";}
        if ( "$editedfileaccess" == "3" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" ){print "<option $selected value='3'>$text[access3]</option>\n";}
        if ( "$editedfileaccess" == "4" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "4" ){print "<option $selected value='4'>$text[access4]</option>\n";}
        print "<option value='4' $selected>$text[admin]</option>\n";
        print "</select></td></tr>";
        print "<tr><td colspan='2'><input type='button' value='$text[savefile]' id='uploadefile' onclick=\"savevalidate(this.form)\"  class='button'/></td></tr></table></form>";
        }
    }
    $parentdir="/";
    $files=$main->getdownloads($role,$dir);
    $subdirs=$main->getsubdirs($role,$dir);

    if ($files->rows > "0" )
    {
        $parentdir=$files->records['0']['parrentdir'];
    }
    if ( $dir != "/" )
    {
        if ( "$parentdir" == "/" )
        {
            print "<b><a href='?page=downloads&amp;rid=$requestid'>..</a>&nbsp;&nbsp;</b>";
        }
        else
        {
            print "<b><a href='?page=downloads&amp;dir=$parentdir&amp;rid=$requestid'>..</a>&nbsp;&nbsp;</b>";
        }
    }
    print "<b>$dir</b>";
    $togler=0;
    $class="class='titlesmall'";
    print "<table><tr>";
    print "<th $class>$text[fname]</th>";
    print "<th $class>$text[size]</th>";
    print "<th $class>$text[uploaded]</th>";
    print "<th $class>$text[owner]</th>";
    if ($role >= 3 )
    {
        print "<th $class>$text[bbcode]</th>";
    }
    print "<th $class >$text[nrdownloads]</th>";
    if ( $role >= 3 or $role >= $uploadfileaccess )
    {
        print "<th $class >$text[actions]</th>";
    }
    print "</tr>";
    foreach( $subdirs->records as $sdir )
    {   
        $class="class='small'";
        if ( $togler % 2  == 1 )
        {
            $class="class='lightsmall'";
        }
        $togler++;
        print "<tr><td $class>$text[dir]</td><td $class colspan='5'><a $class href='?page=downloads&amp;dir=$sdir[dir]'>$sdir[dir]</a></td></tr>";

    }
    foreach( $files->records as $fileinfo )
    {   
        $class="class='small'";
        if ( $togler % 2  == 1 )
        {
            $class="class='lightsmall'";
        }
        $togler++;
        print "<tr>";
        print "<td $class><a href='?page=dload&amp;id=$fileinfo[id]' $class>$fileinfo[name]</a></td>";
        print "<td $class>$fileinfo[size]</td>";
        print "<td $class>$fileinfo[date]</td>";
        print "<td $class>";
        if ( $fileinfo['uname'] != "" and ($role != "0" or ($allowanonuserhome == "true" and $showuser == "true" )))
        {   
            print "<a $class href='?page=userhome&amp;id=$fileinfo[owner]'>$fileinfo[uname]</a>\n";
        }
        else
        {
            print "$fileinfo[uname]</td>";
        }
        if ($role >= 3 )
        {
            print "<td $class>[file=$fileinfo[id]][/file]</td>";
        }
        print "<td $class>$fileinfo[hits]</td>";

        if ($role >= 3 or ( $role >= $uploadfileaccess and $fileinfo['owner'] == $userid ) )
        {
            print "<td $class><a $class href='?page=downloads&amp;do=delete&amp;id=$fileinfo[id]&amp;rid=$requestid'>$text[delete]</a>";
            print "&nbsp;<a $class href='?page=downloads&amp;do=edit&amp;id=$fileinfo[id]&amp;rid=$requestid'>$text[edit]</a></td>";
        }
        print "</tr>";
    }
    print "</table>";
    if ( $role >= $uploadfileaccess and $_REQUEST['do'] != "edit" )
    {
        print "<script type='text/javascript'>
            function validate(form)
            {
                error=\"\";
                if ( form.fname.value == \"\" )
                {
                    error=\"".str_replace(":",","," ".$main->edit_array( $text['fname'])." ")."\";
                }

                if ( form.file.value == \"\" )
                {
                    error=error+\"".str_replace(":",""," ".$main->edit_array( $text['file'])." ")."\";
                }
                if (error != '' )
                {
                    error=error.replace(\":\", \",\");
                    alert('".$main->edit_array( $text['missingfields'])."'+' '+error);
                    return;
                }
                else
                {
                    form.submit();
                }
            }
        </script>";
        print "<br /><br /><form enctype='multipart/form-data' action='?page=downloads' method='post'>
            <table><tr><td>
            <input type='hidden' name='rid' value='$requestid' />
            <input type='hidden' name='do' value='upload' />
            <input type='hidden' name='parentdir' value='$parentdir' />
            <input type='hidden' name='dir' value='$dir' />\n";
        print "<tr><td><label for='fname'>$text[fname]</label></td><td><input name='fname' type='text' id='fname'/></td></tr>";
        print "<tr><td><label for='subdir'>$text[subdir]</label></td><td><input name='subdir' type='text' id='subdir'/></td></tr>";
        print "<tr><td><label for='file'>$text[file]</label></td><td><input type='file' id='file' name='file'/> $text[maxfilesize] $text_upload_max_filesize<input type='hidden' name='MAX_FILE_SIZE' value='$form_upload_max_filesize' /></td></tr>";
        print "<tr><td><label for='access'>$text[access]</label></td><td><select name='access'>";
        if ( "$defaultnewsaccess" == "0" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" or ($allowuserstoaddannonnews and $role >= "1" ) ){print "<option $selected value='0'>$text[access0]</option>\n";}
        if ( "$defaultnewsaccess" == "1" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" or ($allowuserstoaddannonnews and $role >= "1" ) ){print "<option $selected value='1'>$text[access1]</option>\n";}
        if ( "$defaultnewsaccess" == "2" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "2" ){print "<option $selected value='2'>$text[access2]</option>\n";}
        if ( "$defaultnewsaccess" == "3" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" ){print "<option $selected value='3'>$text[access3]</option>\n";}
        if ( "$defaultnewsaccess" == "4" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "4" ){print "<option $selected value='4'>$text[access4]</option>\n";}
        print "</select></td></tr>";
        print "<tr><td colspan='2'><input type='button' value='$text[uploadfile]' id='uploadefile' onclick=\"validate(this.form)\"  class='button'/></td></tr></table></form>";
    }
}
//}}}
//{{{Admin news
if ( "$page" == "admnews" and "$role" >= "3" )
{
    $_SESSION['lastpage']=$page;
    $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
    $news = $main->getnews( $role , 7 , $start , $nr);
    $nrofnews = $main->getnrnews( $role, 7);
    $nrofnews = $nrofnews->records[0]['nr'];
    $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"" );	
}
//}}}
//{{{Admin news
if ( "$page" == "admhiddennews" and "$role" >= "3" )
{
    $_SESSION['lastpage']=$page;
    $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
    $news = $main->getnews( $role , 9 , $start , $nr);
    $nrofnews = $main->getnrnews( $role, 9);
    $nrofnews = $nrofnews->records[0]['nr'];
    $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"" );	
}
//}}}
//{{{ Myhome
if ( ("$page" == "myhome" or "$page" == "userhome") and ( "$role" >= "1" or "$allowanonuserhome" ))
{
    $myhomeid=$userid;if ( isset($_REQUEST['id'])){$myhomeid=$_REQUEST['id'];}
    $usertable = $main->getuser($myhomeid);
    $uuser=$usertable->records[0];
    if ( !isset($subpage)){$subpage="";if ( isset($_REQUEST['subpage'])){$subpage=$_REQUEST['subpage'];}}
    $_SESSION['lastpage']=$page;
    $_SESSION['lastsubpage']=$subpage;
    $_SESSION['lastuid']=$myhomeid;

    if ( $myhomeid != 0 )
    {
        print "<b>$uuser[name]</b><br /><a href='?page=myhome&amp;id=$myhomeid&amp;rid=$requestid'>$text[userhome]</a>\n";
        print " | <a href='?page=myhome&amp;subpage=news&amp;id=$myhomeid&amp;rid=$requestid'>$text[usernews]</a>\n";
    }
    else
    {
        print "<b>$uuser[name]</b>\n";
    }
    
    if ( $myhomeid == $userid and $role > "0" )
    {
        print " | <a href='?page=myhome&amp;subpage=private&amp;id=$myhomeid&amp;rid=$requestid'>$text[privatenews]</a>\n";
        print " | <a href='?page=myhome&amp;subpage=hidden&amp;id=$myhomeid&amp;rid=$requestid'>$text[admhiddennews]</a>\n";
    }

    if ( "$subpage" == "" )
    {
        print "<table width='100%' summary='user details'><tr><td colspan='2'><hr /></td></tr>\n";
        if ( $role >= "3" and $myhomeid != $userid)
        {
            print "<tr><td colspan='2'><a href='?page=edituser&amp;id=$uuser[id]&amp;rid=$requestid'>$text[edit]</a> | <a href='?page=rmuser&amp;id=$uuser[id]&amp;rid=$requestid'>$text[remove]</a> | <a href='?page=deluser&amp;id=$uuser[id]&amp;rid=$requestid'>$text[delete]</a></td></tr>\n";
        }
        elseif ( $myhomeid == $userid and $role > "0" )
        {
            print "<tr><td colspan='2'><a href='?page=edituser&amp;id=$uuser[id]&amp;rid=$requestid'>$text[edit]</a></td></tr>\n";
        }
        print "<tr><td>$text[name]</td><td>$uuser[name]</td></tr>\n";
        $uuser['homepage']=str_replace("class=\"title\"", "",$uuser['homepage']);
        print "<tr><td>$text[homepageheader]</td><td>$uuser[homepage]</td></tr>\n";
        if ( $myhomeid != 0 )
        {
            print "<tr><td>$text[role]</td><td>".$text["access$uuser[role]"]."</td></tr>\n";
        }
        if ( $role >= "2" or ( $myhomeid == $userid and $role > "0") )
        {
            print "<tr><td>$text[email]</td><td>$uuser[email]</td></tr>\n";
            print "<tr><td>$text[nrofnews]</td><td>$uuser[nr]</td></tr>\n";
            print "<tr><td>$text[nrlogins]</td><td>$uuser[nrlogins]</td></tr>\n";
            if ( ($myhomeid == $userid and $role != "0") or $role  >= "3" )
            {
                print "<tr><td>$text[curip]</td><td>$uuser[ip]</td></tr>\n";
                print "<tr><td>$text[curlogin]</td><td>$uuser[login]</td></tr>\n";
                print "<tr><td>$text[lastip]</td><td>$uuser[lastip]</td></tr>\n";
                print "<tr><td>$text[lastlogin]</td><td>$uuser[lastlogin]</td></tr>\n";
            }
            else
            {
                print "<tr><td>$text[lastip]</td><td>$uuser[ip]</td></tr>\n";
                print "<tr><td>$text[lastlogin]</td><td>$uuser[login]</td></tr>\n";
            }
        }
        $lang="lang$uuser[lang]";
        print "<tr><td>$text[lang]</td><td>$text[$lang]</td></tr>\n";
        print "<tr><td>$text[description]</td><td>$uuser[data]</td></tr>\n";
        if( isset($uuser['img']) and $uuser['img'] != "" )
        {
            print "<tr><td>$text[image]</td><td><a class='title' href='img/user/$uuser[id]/$uuser[img]' onclick='window.open(this.href);return false;'><img src='thumb/user/$uuser[id]/$uuser[img]' alt='$uuser[name]'/></a></td></tr>\n";
        }
        print "</table>\n";
    }
    if ( "$subpage" == "news")
    {
        $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
        $news = $main->getusernews( $myhomeid , $role, 5 , $start , $nr);
        $nrofnews = $main->getnrusernews( $myhomeid, $role, 5 );
        $nrofnews = $nrofnews->records[0]['nr'];
        $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"news" );	
    }
    if ( "$subpage" == "hidden" and $myhomeid == $userid )
    {
        $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
        $news = $main->getusernews( $myhomeid , $role, 9 , $start , $nr);
        $nrofnews = $main->getnrusernews( $myhomeid, $role, 9 );
        $nrofnews = $nrofnews->records[0]['nr'];
        $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"news" );	
    }
    if ( "$subpage" == "private" and $myhomeid == $userid)
    {
        $start="0";if ( isset($_REQUEST['start'])){$start=$_REQUEST['start'];}
        $news = $main->getusernews( $myhomeid , $role, 6 , $start , $nr);
        $nrofnews = $main->getnrusernews( $myhomeid, $role, 6);
        $nrofnews = $nrofnews->records[0]['nr'];
        $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"private" );	
    }
}
//}}}
//{{{New news
if ( "$page" == "newnews"  and "$role" >= "1"  )
{
    print "<script type='text/javascript'>
        function validate(form)
        {
            error=\"\";
            if ( form.header.value == \"\" )
            {
                error=\"".str_replace(":",","," ".$main->edit_array( $text['header'])." ")."\";
            }

            if ( form.news.value == \"\" )
            {
                error=error+\"".str_replace(":",""," ".$main->edit_array( $text['newstext'])." ")."\";
            }
            if (error != '' )
            {
                error=error.replace(\":\", \",\");
                alert('".$main->edit_array( $text['missingfields'])."'+' '+error);
                return;
            }
            else
            {
                form.submit();
            }
        }
    </script>";

    print "<form enctype='multipart/form-data' action='?page=addnews' method='post'><p><input type='hidden' name='rid' value='$requestid' /></p>\n";
    print "<table summary='New news'>\n";
    print "<tr><td colspan='3'><span class=\"headline\"><b>$text[newnews]</b></span></td></tr>\n";
    print "<tr><td>$text[access]</td><td> <select name='access'>\n";
    if ( "$defaultnewsaccess" == "0" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" or ($allowuserstoaddannonnews and $role >= "1" ) ){print "<option $selected value='0'>$text[access0]</option>\n";}
    if ( "$defaultnewsaccess" == "1" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" or ($allowuserstoaddannonnews and $role >= "1" ) ){print "<option $selected value='1'>$text[access1]</option>\n";}
    if ( "$defaultnewsaccess" == "2" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "2" ){print "<option $selected value='2'>$text[access2]</option>\n";}
    if ( "$defaultnewsaccess" == "3" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" ){print "<option $selected value='3'>$text[access3]</option>\n";}
    if ( "$defaultnewsaccess" == "4" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "4" ){print "<option $selected value='4'>$text[access4]</option>\n";}
    print "</select></td></tr>\n";
    if ( "$role" >= "3" )
    {
        print "<tr><td>$text[sticky]</td><td> <select name='order'>\n";
        print "<option value='1'>$text[sticky1]</option>\n";
        print "<option value='0'>$text[sticky0]</option>\n";
        print "</select></td></tr>\n";
    }
    print "<tr><td>$text[newstype]</td><td> <select name='type'>\n";
    if ( $role >= "2" ){print "<option value='1'>$text[type1]</option>\n";}
    if ( $role >= "2" ){print "<option value='2'>$text[type2]</option>\n";}
    if ( $role >= "3" ){print "<option value='3'>$text[type3]</option>\n";}
    if ( $role >= "3" and $initpage == "true" ){print "<option value='4'>$text[type4]</option>\n";}
    if ( $role >= "1" ){print "<option value='5'>$text[type5]</option>\n";}
    if ( $role >= "1" ){print "<option value='6'>$text[type6]</option>\n";}
    if ( $role >= "3" ){print "<option value='7'>$text[type7]</option>\n";}
    if ( $role >= "3" ){print "<option value='8'>$text[type8]</option>\n";}
    if ( $role >= "2" ){print "<option value='9'>$text[type9]</option>\n";}
    
    print "</select></td></tr>\n";
    $category = $main->getAllCategories();
    print "<tr><td>$text[category]</td><td> <select name='category'>\n";
    foreach( $category->records as $item )
    {
        $catitem=str_replace(" ","&nbsp;",$item['name']);
        if ( isset($text[$item['name']])){$catitem=str_replace(" ","&nbsp;",$text[$item['name']]);}
        print "<option value='$item[id]'>$catitem</option>\n";
    }
    print "</select><input name='newcategory' type='text' id='newcategory'/></td></tr>\n";
    if ( $role >= "2" ){print "<tr><td>$text[image]</td><td> <input type='file' id='img' name='img'/> $text[maxfilesize] $text_upload_max_filesize<input type='hidden' name='MAX_FILE_SIZE' value='$form_upload_max_filesize' /></td></tr>\n";}
    print "<tr><td>$text[header]</td><td><input name='header' type='text' id='header'/></td></tr>\n";
    print "<tr><td colspan='2'>$text[newstext]</td></tr>\n";
    print "<tr><td colspan='2'><textarea name='news' rows='20' cols='60'>$defaultnewstext</textarea></td></tr>\n";
    print "<tr><td colspan='2'>$text[extnewstext]</td></tr>\n";
    print "<tr><td colspan='2'><textarea name='extnews' rows='20' cols='60'></textarea></td></tr>\n";
    print "<tr><td colspan='2'><input type='button' value='$text[addnews]' id='addnews' onclick=\"validate(this.form)\"  class='button'/> <input type='reset' value='$text[reset]' class='button'/></td></tr>\n";
    print "</table></form>\n";
    print "$bbcode";
}
//}}}
//{{{New user 
if ( "$page" == "newuser" and ( "$role" == "0" or "$role" >= "3" ))
{
    print "<script type='text/javascript'>
        function validate(form)
        {
            error=\"\";
            if ( form.name.value == \"\" )
            {  error=\"".str_replace(":",","," ".$main->edit_array( $text['name'])." ")."\";
            }

            if ( form.nuser.value == \"\" )
            {  error=error+\"".str_replace(":",","," ".$main->edit_array( $text['username'])." ")."\";
            }

            if ( form.pwd1.value == \"\" )
            {  error=error+\"".str_replace(":",","," ".$main->edit_array( $text['passwd'])." ")."\";
            }
            if ( form.pwd2.value == \"\" )
            {  error=error+\"".str_replace(":",","," ".$main->edit_array( $text['verify'])." ")."\";
            }
            if ( form.email.value == \"\" )
            {  error=error+\"".str_replace(":",","," ".$main->edit_array( $text['email'])." ")."\";
            }
            ";
            if ("$role" == "0")
            {
                print "
                if ( form.imgkey.value == \"\" )
                {
                    error=error+\"".str_replace(":",","," ".$main->edit_array( $text['imgkey'])." ")."\";
                }";
            }
            print "if (error != '' )
            {
                error=error.replace(\":\", \",\");
                alert('".$main->edit_array( $text['missingfields'])."'+' '+error);
                return;
            }
            else
            {
                form.submit();
            }
        }
    </script>";
    print "<form enctype='multipart/form-data' action='?page=adduser' method='post'><p><input type='hidden' name='rid' value='$requestid' />\n";
    if ( "$role" < "3"  )
    {
        print "<input type='hidden' name='role' value='1' />\n";
    }
    print "</p><table summary='add user'><tr><td colspan='3'><span class=\"headline\"><b>$text[newuser]</b></span></td></tr>\n";
    if( "$role" >= "3"  )
    {
        print "<tr><td>$text[role]</td><td>\n";
        print "<select name='role'>\n";
        print "<option value='1'>$text[limiteduser]</option>\n";
        print "<option value='2'>$text[normaluser]</option>\n";
        print "<option value='3'>$text[moderator]</option>\n";
        if( "$role" == "4" ){print "<option value='4'>$text[admin]</option>\n";}
        print "</select></td></tr>\n";
    }
    print "<tr><td>$text[name]</td><td><input name='name' type='text' id='name'/></td></tr>\n";
    print "<tr><td>$text[username]</td><td><input name='nuser' type='text' id='nuser'/></td></tr>\n";
    print "<tr><td>$text[passwd]</td><td><input name='pwd1' type='password' id='pwd1'/>$text[verify]<input name='pwd2' type='password' id='pwd2'/></td></tr>\n";
    print "<tr><td>$text[email]</td><td><input name='email' type='text' id='email'/></td></tr>\n";
    print "<tr><td>$text[homepageheader]</td><td><input name='homepage' type='text' id='homepage'/></td></tr>\n";
    print "<tr><td>$text[lang]</td><td>\n";
    print "<select name='lang'>\n";
    $d=dir("lang");
    while($entry = $d->read()) 
    {
        $entry_path = "lang/$entry";
        if( is_file("lang/$entry") and substr_count($entry, 'mod_') == 0 )
        {
            $entry=str_replace(".php","",$entry);
            $selected="";
            if ( $lang == $entry ){$selected=" selected='selected'";}
            if ( $text["lang$entry"] != "" )
            {
                print "<option value='$entry'$selected>".$text["lang$entry"]."</option>\n";
            }
            else
            {
                print "<option value='$entry'$selected>$entry</option>\n";
            }
        }

    }
    print "</select></td></tr>\n";
    if ("$role" == "0")
    {
        print "<tr><td>$text[imgkey]&nbsp;<span class='smaller'>$text[imgkeyhelp]</span></td><td><input name='imgkey' type='text' id='imgkey' value='' /><img src='randimg.php?rid=$requestid' alt='$text[imgkey]'/></td></tr>\n";
    }
    print "<tr><td>$text[nrofnews]</td><td>\n";
    print "<select name='nr'>";
    $selected="";$nrselect=$newscol * 5;if ( $nr == $nrselect ){$selected=" selected='selected'";};print "<option value='$nrselect'$selected>$nrselect</option>\n";
    $selected="";$nrselect=$newscol * 10;if ( $nr == $nrselect ){$selected=" selected='selected'";};print "<option value='$nrselect'$selected>$nrselect</option>\n";
    $selected="";$nrselect=$newscol * 20;if ( $nr == $nrselect ){$selected=" selected='selected'";};print "<option value='$nrselect'$selected>$nrselect</option>\n";
    $selected="";$nrselect=$newscol * 40;if ( $nr == $nrselect ){$selected=" selected='selected'";};print "<option value='$nrselect'$selected>$nrselect</option>\n";
    $selected="";$nrselect=$newscol * 80;if ( $nr == $nrselect ){$selected=" selected='selected'";};print "<option value='$nrselect'$selected>$nrselect</option>\n";
    print "</select></td></tr>\n";
    if ( $allowusertheme == "true" )
    {
        print "<tr><td>$text[theme]</td><td><select name='usetheme'>\n";
        $d=dir("themes");
        $curtheme="";
        if (isset($_SESSION['theme'])){$curtheme=$_SESSION['theme'];}
        print "<option value='default'>$text[default]</option>\n";
        while($entry = $d->read()) 
        {
            $entry=str_replace(".php","" ,$entry);
            if( is_dir("themes/$entry") and $entry != "." and $entry != ".." and is_file("themes/$entry/site.css"))
            {
                print "<option value='$entry'>$entry</option>\n";
            }

        }
        print "</select></td></tr>\n";
    }
    if ( $role >= "2" ){print "<tr><td>$text[image]</td><td> <input type='file' id='img' name='img'/> $text[maxfilesize] $text_upload_max_filesize<input type='hidden' name='MAX_FILE_SIZE' value='$form_upload_max_filesize' /></td></tr>\n";}
    print "<tr><td colspan='2'>$text[description]</td></tr>\n";
    print "<tr><td colspan='2'><textarea name='data' rows='20' cols='60'></textarea></td></tr>\n";
    print "<tr><td colspan='2'><input type='button' value='$text[newuser]' id='adduser' onclick=\"validate(this.form)\"  class='button'/> <input type='reset' value='$text[reset]' class='button'/></td></tr>\n";
    print "</table></form>\n";
    print "$bbcode";
}
//}}}
//{{{Edit user 
if ( "$page" == "edituser" and ( "$role" >= "3" or $_REQUEST['id'] == $userid ))
{
    print "<script type='text/javascript'>
        function validate(form)
        {
            error=\"\";
            if ( form.name.value == \"\" )
            {  error=\"".str_replace(":",","," ".$main->edit_array( $text['name'])." ")."\";
            }
            if ( form.pwd1.value != form.pwd2.value )
            {  error=error+\"".str_replace(":",","," ".$main->edit_array( $text['passwd'])." ")."\";
            }
            if ( form.email.value == \"\" )
            {  error=error+\"".str_replace(":",","," ".$main->edit_array( $text['email'])." ")."\";
            }

            if (error != '' )
            {
                error=error.replace(\":\", \",\");
                alert('".$main->edit_array( $text['missingfields'])."'+' '+error);
                return;
            }
            else
            {
                form.submit();
            }
        }
    </script>";

    $myhomeid=$userid;if ( isset($_REQUEST['id'])){$myhomeid=$_REQUEST['id'];}
    $usertable = $main->getuser($myhomeid);
    $utext=$main->edit_array($usertable->records[0]);
    print "<form enctype='multipart/form-data' action='?page=saveuser' method='post'><p><input type='hidden' name='rid' value='$requestid' /></p><table summary='add user'>\n";
    print "<tr><td colspan='3'><span class=\"headline\"><b>$text[edituser]</b></span></td></tr>\n";
    if( "$role" >= "3"  )
    {
        $selected="";
        print "<tr><td>$text[role]</td><td>\n"; 
        print "<select name='role'>\n";
        if ( "$utext[role]" == "0" ){$selected="selected='selected'";}else{$selected="";}
        print "<option $selected value='0'>$text[noaccess]</option>\n";
        if ( "$utext[role]" == "1" ){$selected="selected='selected'";}else{$selected="";}
        print "<option $selected value='1'>$text[limiteduser]</option>\n";
        if ( "$utext[role]" == "2" ){$selected="selected='selected'";}else{$selected="";}
        print "<option $selected value='2'>$text[normaluser]</option>\n";
        if ( "$utext[role]" == "3" ){$selected="selected='selected'";}else{$selected="";}
        print "<option $selected value='3'>$text[moderator]</option>\n";
        if ( "$utext[role]" == "4" ){$selected="selected='selected'";}else{$selected="";}
        if( "$role" == "4" ){print "<option $selected value='4'>$text[admin]</option>\n";}
        print "</select></td></tr>\n";
    }
    else
    {
        print "<input type='hidden' name='role' value='$utext[role]' />";
    }
    print "<tr><td>$text[name]</td><td><input name='name' type='text' id='name' value='$utext[name]' /></td></tr>\n";
    print "<tr><td>$text[username]</td><td>$utext[user]</td></tr>\n";
    print "<tr><td>$text[passwd]</td><td><input name='pwd1' type='password' id='pwd1'/> $text[verify]<input name='pwd2' type='password' id='pwd2'/></td></tr>\n";
    print "<tr><td>$text[email]</td><td><input name='email' type='text' id='email' value='$utext[email]' /></td></tr>\n";
    print "<tr><td>$text[homepageheader]</td><td><input name='homepage' type='text' id='homepage' value='$utext[homepage]'/></td></tr>\n";
    print "<tr><td>$text[lang]</td><td>\n";
    print "<select name='lang'>\n";
    $d=dir("lang");
    while($entry = $d->read()) 
    {
        $entry_path = "lang/$entry";
        if( is_file("lang/$entry") and substr_count($entry, 'mod_') == 0 )
        {
            $entry=str_replace(".php","",$entry);
            $selected="";
            if ( $utext['lang'] == $entry ){$selected=" selected='selected'";}
            if ( $text["lang$entry"] != "" )
            {
                print "<option value='$entry'$selected>".$text["lang$entry"]."</option>\n";
            }
            else
            {
                print "<option value='$entry'$selected>$entry</option>\n";
            }
        }

    }
    print "</select></td></tr>\n";
    print "<tr><td>$text[nrofnews]</td><td>\n";
    print "<select name='nr'>";
    $selected="";$nrselect=$newscol * 5;if ( $utext['nr'] == $nrselect ){$selected=" selected='selected'";};print "<option value='$nrselect'$selected>$nrselect</option>\n";
    $selected="";$nrselect=$newscol * 10;if ( $utext['nr'] == $nrselect ){$selected=" selected='selected'";};print "<option value='$nrselect'$selected>$nrselect</option>\n";
    $selected="";$nrselect=$newscol * 20;if ( $utext['nr'] == $nrselect ){$selected=" selected='selected'";};print "<option value='$nrselect'$selected>$nrselect</option>\n";
    $selected="";$nrselect=$newscol * 40;if ( $utext['nr'] == $nrselect ){$selected=" selected='selected'";};print "<option value='$nrselect'$selected>$nrselect</option>\n";
    $selected="";$nrselect=$newscol * 80;if ( $utext['nr'] == $nrselect ){$selected=" selected='selected'";};print "<option value='$nrselect'$selected>$nrselect</option>\n";
    print "</select></td></tr>\n";
    if ( $allowusertheme == "true" )
    {
        print "<tr><td>$text[theme]</td><td><select name='usetheme'>\n";
        $d=dir("themes");
        $curtheme=$utext['theme'];;
        print "<option value='default'>$text[default]</option>\n";
        while($entry = $d->read()) 
        {
            $entry=str_replace(".php","" ,$entry);
            if( is_dir("themes/$entry") and $entry != "." and $entry != ".." and is_file("themes/$entry/site.css"))
            {
                $selected="";
                if ($entry == $curtheme ){$selected="selected=selected";}
                print "<option value='$entry' $selected>$entry</option>\n";
            }
        }
        print "</select></td></tr>\n";
    }
    if ( "$role" >= "2" )
    {
        print "<tr><td>$text[replaceimg]</td><td> <input type='file' id='img' name='img'/> $text[maxfilesize] $text_upload_max_filesize<input type='hidden' name='MAX_FILE_SIZE' value='$form_upload_max_filesize' /></td></tr>\n";
        if ( isset($utext['img']) and $utext['img'] != "")
        {
            print "<tr><td><label for='delimg'>$text[removeimg]</label></td><td><input type='checkbox' id='delimg' name='delimg'/>\n";
            print "<img src='thumb/user/$utext[id]/$utext[img]' alt=''/>\n";
        }
    }
    print "</td></tr><tr><td colspan='2'>$text[description]</td></tr>\n";
    print "<tr><td colspan='2'><textarea name='data' rows='20' cols='60'>$utext[data]</textarea></td></tr>\n";
    print "<tr><td colspan='2'><input type='hidden' name='id' value='$utext[id]' />";
    print "<input type='hidden' name='user' value='$utext[user]' /><input type='button' value='$text[saveuser]' id='adduser' onclick=\"validate(this.form)\"  class='button'/> <input type='reset' value='$text[reset]' class='button'/></td></tr>\n";
    print "</table></form>\n";
    print "$bbcode";
}
//}}}
//{{{ Edit Menu
if ( $page == "editmenu" and $role >= "3" )
{
    if ( isset($_REQUEST['do']))
    {
        if ($_REQUEST['do'] == "save" )
        {
            if ( isset($_REQUEST['id']) and isset($_REQUEST['access']) and isset($_REQUEST['order']) and isset($_REQUEST['parent']) )
            {
                $main->savemenu($_REQUEST['id'], $_REQUEST['access'], $_REQUEST['order'], $_REQUEST['parent']);
            }
        }
    }
    $menuitems=$main->getallmenu();

    print "<form enctype='multipart/form-data' action='?page=editmenu' method='post'>";
    print "<table>";
    print "<tr><td colspan='5'><span class=\"headline\"><b>$text[editmenu]</b></span></td></tr>\n";
    print "<tr>";
    print "<th class='title'>$text[menuid]</th>";
    print "<th class='title'>$text[access]</th>";
    print "<th class='title'>$text[order]</th>";
    print "<th class='title'>$text[parent]</th>";
    print "<th class='title' colspan='2'>$text[menutext]</th>";
    print "</tr>";

    $togler=1;
    foreach ($menuitems->records as $item ) 
    {
        $class="";
        if ( $togler % 2 == 0 )
        {
            $class="class='light'";
        }
        print "<tr>";
        if ( isset($_REQUEST['editid']) and $_REQUEST['editid'] == $item['id'] )
        {

            print "<td $class>$item[id]";
            print "<input type='hidden' name='id' value='$item[id]' /><input type='hidden' name='do' value='save' /><input type='hidden' name='rid' value='$requestid' /></td>";
            print "<td $class><select name='access'>";

            $selected="";if( "$item[access]" == "0" ){$selected="selected='selected'";}print "<option $selected value='0'>$text[noaccess]</option>\n";
            $selected="";if( "$item[access]" == "1" ){$selected="selected='selected'";}print "<option $selected value='1'>$text[limiteduser]</option>\n";
            $selected="";if( "$item[access]" == "2" ){$selected="selected='selected'";}print "<option $selected value='2'>$text[normaluser]</option>\n";
            $selected="";if( "$item[access]" == "3" ){$selected="selected='selected'";}print "<option $selected value='3'>$text[moderator]</option>\n";
            $selected="";if( "$item[access]" == "4" ){$selected="selected='selected'";}print "<option $selected value='4'>$text[admin]</option>\n";
            print "</select></td>";
            print "<td $class><input name='order' type='text' id='word' alt='word' value='$item[order]' size='2'/></td>";
            print "<td $class><input name='parent' type='text' id='word' alt='word' value='$item[parent]' size='2'/></td>";
            if ( isset($text["$item[data]"]))
            {
                print "<td $class>".$text["$item[data]"]."</td>";
            }
            else
            {
                print "<td $class>$item[data]</td>";
            }
            print "<td $class><input type='submit' value='$text[savemenu]' id='savemenu' class='button'/><input type='reset' value='$text[reset]' class='button'/>";
            print "</td>";
        }
        else
        {
            print "<td $class>$item[id]</td>";
            print "<td $class>";

            if( "$item[access]" == "0" ){print "$text[noaccess]\n";}
            elseif( "$item[access]" == "1" ){print "$text[limiteduser]\n";}
            elseif( "$item[access]" == "2" ){print "$text[normaluser]\n";}
            elseif( "$item[access]" == "3" ){print "$text[moderator]\n";}
            elseif( "$item[access]" == "4" ){print "$text[admin]\n";}
            else{print "$item[access]";}
            print "</td>";
            print "<td $class>$item[order]</td>";
            print "<td $class>$item[parent]</td>";
            if ( isset($text["$item[data]"]))
            {
                print "<td $class>".$text["$item[data]"]."</td>";
            }
            else
            {
                print "<td $class>$item[data]</td>";
            }
            print "<td $class><a $class href='?page=editmenu&amp;editid=$item[id]&amp;rid=$requestid'>$text[edit]</a></td>";
        }
        print "</tr>";
        $togler++;
    }
    print "</table></form>";
}
//}}}
//{{{ Edit abbr
if ( "$page" == "editabbr" and $role >= "3" )
{

    if (isset($_REQUEST['do']))
    {
        if ($_REQUEST['do'] == "updateall")
        {
            $nr=$main->getnrabbrnews();
            $donr=30;
            for ($i = 0; $i <= $nr ; $i+=$donr) 
            {
                $news=$main->getabbrnews($i,$donr);
                $news=$main->edit_array($news);
                $news=$main->clean_array($news , false );
                foreach ($news['records'] as $onenews ) 
                {
                    $main->saveabbrnews($onenews['id'], $onenews['data'], $onenews['data2']);
                }
            }
            $nrc=$main->getnrabbrcomments();
            for ($i = 0; $i <= $nr ; $i+=$donr) 
            {
                $comments=$main->getabbrcomments($i,$donr);
                $comments=$main->edit_array($comments);
                $comments=$main->clean_array($comments, false );
                foreach ($comments['records'] as $onenews ) 
                {
                    $main->saveabbrcomment($onenews['id'], $onenews['data']);
                }
            }
        }
    }
    $order="id";if ( isset($_REQUEST['orderabbr'])){$order=$_REQUEST['orderabbr'];$_SESSION['abbrorder']=$order;}elseif(isset($_SESSION['abbrorder'])){$order=$_SESSION['abbrorder'];}
    $abbrlist = $main->getabbr($order);
    $togler=1;
    $class="class='title'";
    print "<script type='text/javascript'>
        function validate(form)
        {
            error=\"\";
            if ( form.word.value == \"\" )
            {
                error=\"".str_replace(":",","," ".$main->edit_array( $text['abbrword']).", ")."\";
            }

            if ( form.title.value == \"\" )
            {
                error=error+\"".str_replace(":",""," ".$main->edit_array( $text['abbrtitle'])." ")."\";
            }
            if (error != '' )
            {
                error=error.replace(\":\", \",\");
                alert('".$main->edit_array( $text['missingfields'])."'+' '+error);
                return;
            }
            else
            {
                form.submit();
            }
        }
    </script>";
    print "<table width='100%' summary='users'>\n";
    print "<tr><td colspan='5'><span class=\"headline\"><b>$text[editabbr]</b></span></td></tr>\n";
    print "<tr><th $class><a $class href='?page=editabbr&amp;orderabbr=type&amp;rid=$requestid'>$text[abbrtype]</a></th>";
    print "<th $class><a $class href='?page=editabbr&amp;orderabbr=word&amp;rid=$requestid'>$text[abbrword]</a></th>";
    print "<th $class><a $class href='?page=editabbr&amp;orderabbr=title&amp;rid=$requestid'>$text[abbrtitle]</a></th>";
    print "<th colspan='2' $class><a $class href='?page=editabbr&amp;order=data&amp;rid=$requestid'>$text[abbrlink]</a></th></tr>\n";

    foreach ($abbrlist->records as $abbr ) 
    {
        if (!isset($abbr['data']))
        {
            $abbr['data']="";
        }
        if ( isset($_REQUEST['editid']) and $_REQUEST['editid'] == $abbr['id'] )
        {
            print "<tr>\n";
            print "<td colspan='5'>";
            print "<form enctype='multipart/form-data' action='?page=editabbr' method='post'>";
            print "<p><input type='hidden' name='id' value='$abbr[id]' /><input type='hidden' name='do' value='save' /><input type='hidden' name='rid' value='$requestid' />";
            $selected="";
            print "<select name=type>";      
#if( $abbr['type'] == "1" ){$selected="selected='selected'";}else{$selected="";}print "<option $selected value='1'>$text[abbrtypeabbr]</option>";
            if( $abbr['type'] == "2" ){$selected="selected='selected'";}else{$selected="";}print "<option $selected value='2'>$text[abbrtypeacronym]</option>";
            if( $abbr['type'] == "3" ){$selected="selected='selected'";}else{$selected="";}print "<option $selected value='3'>$text[abbrtypelink]</option>";
            print "</select>";
            print "<input name='word' type='text' id='word' alt='word' value='$abbr[word]' size='12'/>";
            print "<input name='title' type='text' id='title' alt='title' size='29' value='$abbr[title]'/>";
            print "<input name='abbrdata' type='text' id='abbrdata' alt='abbrdata'  size='29' value='$abbr[data]'/>";
            print "<input type='button' value='$text[saveabbr]' id='saveabbr' onclick=\"validate(this.form)\" class='button'/>"; 	
            print "</p></form></td></tr>\n";
        }
        else
        {
            $class="";
            if ( $togler % 2 == 0 )
            {
                $class="class='light'";
            }
            print "<tr>";
            print "<td $class>";
#if( $abbr['type'] == "1" ){print "$text[abbrtypeabbr]";}
            if( $abbr['type'] == "2" ){print "$text[abbrtypeacronym]";}
            if( $abbr['type'] == "3" ){print "$text[abbrtypelink]";}
            print "&nbsp;</td>";
            print "<td $class>$abbr[word]&nbsp;</td>";
            print "<td $class>$abbr[title]&nbsp;</td>";
            print "<td $class>$abbr[data]&nbsp;</td>";
            print "<td $class><a $class href='?page=editabbr&amp;editid=$abbr[id]&amp;rid=$requestid'>$text[edit]</a>&nbsp;<a $class href='?page=editabbr&amp;deleteid=$abbr[id]&amp;rid=$requestid'>$text[delete]</a></td>";
            print "</tr>"; 

        }
        $togler++;
    }
    if (!isset($_REQUEST['editid']))
    {
        print "<tr>\n";
        print "<td colspan='5'>";
        print "<form enctype='multipart/form-data' action='?page=editabbr' method='post'>";
        print "<p><input type='hidden' name='do' value='add' /><input type='hidden' name='rid' value='$requestid' />";
        $selected="";
        print "<select name=type>";
#print "<option $selected value='1'>$text[abbrtypeabbr]</option>";
        print "<option $selected value='2'>$text[abbrtypeacronym]</option>";
        print "<option $selected value='3'>$text[abbrtypelink]</option>";
        print "</select>";
        print "<input name='word' type='text' id='word' alt='word' size='12'/>";
        print "<input name='title' type='text' id='title' alt='title' size='29'/>";
        print "<input name='abbrdata' type='text' id='abbrdata' alt='abbrdata'  size='29'/>";
        print "<input type='button' value='$text[addabbr]' id='saveabbr' onclick=\"validate(this.form)\"  class='button'/>";
        print "</p></form></td></tr>\n";
    }
    print "</table>";
    print "<a href='?page=editabbr&amp;do=updateall&amp;rid=$requestid'>$text[updateall]</a>";
}
//}}}
//{{{ List users
if ( "$page" == "listusers" and ( "$role" >= "1" or $allowanonuserhome == "true") )
{
    $_SESSION['lastpage']=$page;
    $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
    $nr=$nr*2;
    $uorder="name";
    if (isset($_REQUEST['uorder']))
    {
        if ($_REQUEST['uorder'] == 1 ){$uorder="name";}
        if ($_REQUEST['uorder'] == 2 ){$uorder="role";}
        if ($_REQUEST['uorder'] == 3 ){$uorder="email";}
        if ($_REQUEST['uorder'] == 4 ){$uorder="nrlogins desc";}
    }
    $userlist = $main->getuserlist( $start , $nr, $uorder);
    $nrofusers = $main->getnruserlist( );
    $nrofusers = $nrofusers->records[0]['nr'];
    
    $colls=3;
    print "<table width='100%' summary='users'>\n";
    if ($role >= 3)
    {
       $colls=6;
    }
    elseif ($role >= 2)
    {
       $colls=5;
    }
    print "<tr><td colspan='$colls'><span class=\"headline\"><b>$text[listusers]</b></span></td></tr>\n";
    $togler=0;
    print "<tr><th class=\"title\"><a href='?page=listusers&amp;start=$start&amp;nr=$nr&amp;rid=$requestid&amp;uorder=1' class=\"title\"> $text[name]</a></th>
    <th class=\"title\">$text[haveinfo]</th>
    <th class=\"title\"><a href='?page=listusers&amp;start=$start&amp;nr=$nr&amp;rid=$requestid&amp;uorder=2' class=\"title\">$text[role]</a></th>";
    if ( $role >= "2" ){print "<th class=\"title\"><a href='?page=listusers&amp;start=$start&amp;nr=$nr&amp;rid=$requestid&amp;uorder=3' class=\"title\">$text[email]</a></th>
                               <th class=\"title\"><a href='?page=listusers&amp;start=$start&amp;nr=$nr&amp;rid=$requestid&amp;uorder=4' class=\"title\">$text[nrlogins]</a></th>";}
    if ( $role >= "3" ){print "<th class=\"title\">$text[actions]</th>";}
    print "</tr>";
    foreach( $userlist->records as $utext )
    {	
        $class="";
        if ( $togler % 2  == 1 )
        {
            $class="class='light'";
        }
        print "<tr>\n";
        print "<td $class><a $class href='?page=userhome&amp;id=$utext[id]&amp;rid=$requestid'>$utext[name]</a></td>\n";
        print "<td $class>";
        if ($utext['data'] != "" )
        {
            print "<img src='images/havetext.gif' alt='$text[description]'/>";
        }
        if ( $utext['img'] != "")
        {
            print "<img src='images/havephoto.gif' alt='$text[image]' />";
        }
        if ( $role >= 3 and $utext['login'] == "" )
        {
            print "<img src='images/nologin.gif' alt='$text[nologin]' />";
        }
        print "</td>\n"; 
        if( $utext['role'] == 0 ){print "<td $class>$text[noaccess]</td>\n";}
        if( $utext['role'] == 1 ){print "<td $class>$text[limiteduser]</td>\n";}
        if( $utext['role'] == 2 ){print "<td $class>$text[normaluser]</td>\n";}
        if( $utext['role'] == 3 ){print "<td $class>$text[moderator]</td>\n";}
        if( $utext['role'] == 4 ){print "<td $class>$text[admin]</td>\n";}
        if ( $role >= "2" )
        {
            print "<td $class ><a $class href='mailto:$utext[email]'>$utext[email]</a></td>\n";
            print "<td $class >$utext[nrlogins]</td>\n";
        } 
        if ( $role >= "3" )
        {
            print "<td $class><a $class href='?page=edituser&amp;id=$utext[id]&amp;rid=$requestid'>$text[edit]</a> <a $class href='?page=rmuser&amp;id=$utext[id]&amp;rid=$requestid'>$text[remove]</a> <a $class href='?page=deluser&amp;id=$utext[id]&amp;rid=$requestid'>$text[delete]</a></td>\n";
        }
        $togler++;
        print "</tr>\n"; 	
    }
    print "<tr><td colspan='$colls' class='title'><span class=\"small\">$text[nrusers]&nbsp;$nrofusers&nbsp;&nbsp;\n";
    if ( $start > 0 )
    {
        $pstart=$start-$nr;if ($pstart < 0 ){$pstart=0;}
        print "<a href='?page=listusers&amp;start=$pstart&amp;nr=$nr&amp;rid=$requestid' class='title'>$text[prev]</a>\n";
    }
    else
    {
        print " $text[prev] ";
    }
    print "&nbsp;|&nbsp;";
    if ( $nrofusers > $nr+$start )
    {
        $nstart=$start+$nr;
        print "<a href='?page=listusers&amp;start=$nstart&amp;nr=$nr&amp;rid=$requestid' class='title'>$text[next]</a>\n";
    }
    else
    {
        print " $text[next] ";
    }
    print "</span></td></tr>\n";
    print "</table>\n";

}
//}}}
//{{{ Referer
if ( "$page" == "referer" and "$role" >= "3" )
{
    $referer=$main->getReferer();
    print "<table width='100%' summary='referer'>\n";
    print "<tr><td colspan='2'><span class=\"headline\"><b>$text[referer]</b></span></td></tr>\n";
    $togler=1;
    print "<tr><td class='title'><span class=\"small\">$text[counter]</span></td><td class='title'><span class=\"small\">$text[referer]:</span></td></tr>";
    foreach( $referer->records as $utext )
    {
        $class="";
        if ( $togler % 2  == 0 )
        {
            $class="class='light'";
        }
        print "<tr>\n";
        print "<td $class><span class=\"small\"> \n";
        print "$utext[nr]\n";
        print "</span></td><td $class><span class=\"small\">\n";
        print "<a $class href='$utext[referer]'>$utext[referer]</a>\n";
        print "</span></td></tr>\n";
        $togler++;
    }
    print "</table>\n";
}
//}}}
//{{{ Borwser statistic
if ( $page ==  "browserstat" and $role >= 3 )
    {
        print "<span class=\"headline\"><b>$text[browserstat]:</b></span><br /><br />";
        print "<table  width='100%' summary='$text[browserstat]'>\n";
        $brosterstat=$main->getbrowserstat("0");
        $togler=false;
        $class="class=\"title\"";
        print "<tr><th $class>$text[yearmonth]</th>
               <th $class>$text[pageviews]</th>
               <th $class>$text[browser]</th>
               <th $class>$text[version]</th>
               </tr> \n ";

        foreach( $brosterstat->records as $bstat )
        {
            if ($togler){$class="class='light'";}else{$class="";}
            print "<tr><td $class>$bstat[year]-$bstat[month]</td>
                       <td $class>$bstat[hits]</td>
                       <td $class>$bstat[browser]</td>
                       <td $class>$bstat[version]</td>
                       ";
                   print "</tr> \n ";
            $togler=!$togler;
        }
        print "</table>\n";
        
        print "<br /><br /><span class=\"headline\"><b>$text[crawlers]</b></span><br /><br />";
        print "<table  width='100%' summary='$text[browserstat]'>\n";
        $brosterstat=$main->getbrowserstat("1");
        $togler=false;
        $class="class=\"title\"";
        print "<tr><th $class>$text[yearmonth]</th>
               <th $class>$text[pageviews]</th>
               <th $class>$text[browser]</th>
               <th $class>$text[version]</th>
               </tr> \n ";

        foreach( $brosterstat->records as $bstat )
        {
            if ($togler){$class="class='light'";}else{$class="";}
            print "<tr><td $class>$bstat[year]-$bstat[month]</td>
                       <td $class>$bstat[hits]</td>
                       <td $class>$bstat[browser]</td>
                       <td $class>$bstat[version]</td>";
                   print "</tr> \n ";
            $togler=!$togler;
        }
        print "</table>\n";
        print "<br /><br /><span class=\"headline\"><b>$text[platform]</b></span><br /><br />";
        print "<table  width='100%' summary='$text[browserstat]'>\n";
        $brosterstat=$main->getbrowserstat("3");
        $togler=false;
        $class="class=\"title\"";
        print "<tr><th $class>$text[yearmonth]</th>
               <th $class>$text[pageviews]</th>
               <th $class>$text[platform]</th>
               </tr> \n ";

        foreach( $brosterstat->records as $bstat )
        {
            if ($togler){$class="class='light'";}else{$class="";}
            print "<tr><td $class>$bstat[year]-$bstat[month]</td>
                       <td $class>$bstat[hits]</td>
                       <td $class>$bstat[platform]</td>";
                   print "</tr> \n ";
            $togler=!$togler;
        }
        print "</table>\n";

    }
//}}}
//{{{ handle sessions
if ($page == "sessions" and $role >= 3 and $usedbsessions )
{
    if (isset($_REQUEST['do']) and isset($_REQUEST['sid']))
    {
        $do=$_REQUEST['do'];
        $sid=$_REQUEST['sid'];
        if ( $do == "del")
        {
            $session->destroy($sid);
        }
    }
    $activesessios=$main->run_query("select s.session_id, s.session_expires, s.page, s.ip , u.name, u.role, s.hits  from sessions s join user u on s.user = u.id order by s.session_expires desc;");
        print "<span class=\"headline\"><b>$text[sessions]</b></span><br /><br />";
        print "<b>Current time:</b> ".strftime("%Y-%m-%d %T",time())."";
        print "<table  width='100%' summary='$text[sessions]'>\n";
        $brosterstat=$main->getbrowserstat("0");
        $togler=false;
        $class="class=\"title\"";
        print "<tr><th $class>$text[name]</th>
               <th $class>$text[role]</th>
               <th $class>$text[pageviews]</th>
               <th $class>$text[ip]</th>
               <th $class>$text[lastpage]</th>
               <th $class>$text[expires]</th>
               <th $class>$text[actions]</th>
               </tr> \n ";

        foreach( $activesessios->records as $csessios )
        {
            if ($togler){$class="class='light'";}else{$class="";}
            $date=strftime("%Y-%m-%d %T",$csessios['session_expires']);
            print "<tr><td $class>$csessios[name]</td>";
            if( $csessios['role'] == 0 ){print "<td $class>$text[noaccess]</td>\n";}
            if( $csessios['role'] == 1 ){print "<td $class>$text[limiteduser]</td>\n";}
            if( $csessios['role'] == 2 ){print "<td $class>$text[normaluser]</td>\n";}
            if( $csessios['role'] == 3 ){print "<td $class>$text[moderator]</td>\n";}
            if( $csessios['role'] == 4 ){print "<td $class>$text[admin]</td>\n";}
            print "<td $class>$csessios[hits]</td>
                       <td $class>$csessios[ip]</td>
                       <td $class>$csessios[page]</td>
                       <td $class>$date</td>
                       <td $class><a $class href='?page=sessions&amp;do=del&amp;sid=$csessios[session_id]'>$text[terminate]</a></td>";
                   print "</tr> \n ";
            $togler=!$togler;
        }
        print "</table>\n";

}
//}}}


//{{{ manage init pages
if ( "$page" == "manageinitpages" and $role >= "3" )
{
    $_SESSION['lastpage']=$page;
    $start="0";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
    $news=$main->getnews($role, 4, $start, $nr );
    $nrofnews = $main->getnrnews( $role, 4);
    $nrofnews = $nrofnews->records[0]['nr'];
    $main->printnews( $news,$nrofnews,$role,$userid,$start,$nr,$page,"" );

}
//}}}
//{{{ Optimize table
if ($page == "optimizetables")
{
    $main->optimizetables();
}
//}}}
//{{{ Plugin
if ( "$page" == "plugin" and $enableplugin == "true" )
{
    if(  isset($_REQUEST['plug']))
    {
        $pluginname=$_REQUEST['plug'];
        if (isset($plugins[$pluginname]))
        {
            $plugin=$plugins[$pluginname];
            $plugin->execute($main);
        }
    }
}
//}}}
//{{{ Edit news
if ( "$page" == "editnews" and "$role" >= "1" )
{
    print "<script type='text/javascript'>
        function validate(form)
        {
            error=\"\";
            if ( form.header.value == \"\" )
            {
                error=\"".str_replace(":",","," ".$main->edit_array( $text['header'])." ")."\";
            }

            if ( form.news.value == \"\" )
            {
                error=error+\"".str_replace(":",""," ".$main->edit_array( $text['newstext'])." ")."\";
            }
            if (error != '' )
            {
                error=error.replace(\":\", \",\");
                alert('".$main->edit_array( $text['missingfields'])."'+' '+error);
                return;
            }
            else
            {
                form.submit();
            }
        }
    </script>";
    $id="";if ( isset($_REQUEST['id']) ){$id=$_REQUEST['id'];}
    $news = $main->geteditnews( $id );
    $news = $main->edit_array($news);
    $utext=$news['records']['0'];
    $selected="";
    print "<form enctype='multipart/form-data' action='?page=savenews' method='post'><p><input type='hidden' name='rid' value='$requestid' /></p>\n";
    print "<table summary='edit news'><tr><td valign='top'><label for='access'>$text[access]</label></td><td valign='top'><select name='access'>\n";
    
    if ( "$utext[access]" == "0" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" or ($allowuserstoaddannonnews and $role >= "1" )){print "<option $selected value='0'>$text[access0]</option>\n";}
    if ( "$utext[access]" == "1" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" or ($allowuserstoaddannonnews and $role >= "1" )){print "<option $selected value='1'>$text[access1]</option>\n";}
    if ( "$utext[access]" == "2" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "2" ){print "<option $selected value='2'>$text[access2]</option>\n";}
    if ( "$utext[access]" == "3" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "3" ){print "<option $selected value='3'>$text[access3]</option>\n";}
    if ( "$utext[access]" == "4" ){$selected="selected='selected'";}else{$selected="";}if ( $role >= "4" ){print "<option $selected value='4'>$text[access4]</option>\n";}
    
    print "</select></td></tr>\n";
    if ( "$role" >= "3" )
    {
        if ( "$utext[order]" == "1" ){$selected="selected='true'";}else{$selected="";}
        print "<tr><td valign='top'><label for='order'>$text[sticky]</label></td><td valign='top'><select name='order'>\n";
        print "<option $selected value='1'>$text[sticky1]</option>\n";
        if ( "$utext[order]" == "0" ){$selected="selected='true'";}else{$selected="";}
        print "<option $selected value='0'>$text[sticky0]</option>\n";
        
        print "</select></td></tr>\n";
    }
    print "<tr><td>$text[newstype]</td><td> <select name='type'>\n";
    if ( "$utext[type]" == "1" ){$selected="selected='true'";}else{$selected="";}if ( $role >= "2" ){print "<option $selected value='1'>$text[type1]</option>\n";}
    if ( "$utext[type]" == "2" ){$selected="selected='true'";}else{$selected="";}if ( $role >= "2" ){print "<option $selected value='2'>$text[type2]</option>\n";}
    if ( "$utext[type]" == "3" ){$selected="selected='true'";}else{$selected="";}if ( $role >= "3" ){print "<option $selected value='3'>$text[type3]</option>\n";}
    if ( "$utext[type]" == "4" ){$selected="selected='true'";}else{$selected="";}if ( $role >= "3" and $initpage == "true" ){print "<option $selected value='4'>$text[type4]</option>\n";}
    if ( "$utext[type]" == "5" ){$selected="selected='true'";}else{$selected="";}if ( $role >= "1" ){print "<option $selected value='5'>$text[type5]</option>\n";}
    if ( "$utext[type]" == "6" ){$selected="selected='true'";}else{$selected="";}if ( $role >= "1" ){print "<option $selected value='6'>$text[type6]</option>\n";}
    if ( "$utext[type]" == "7" ){$selected="selected='true'";}else{$selected="";}if ( $role >= "3" ){print "<option $selected value='7'>$text[type7]</option>\n";}
    if ( "$utext[type]" == "8" ){$selected="selected='true'";}else{$selected="";}if ( $role >= "3" ){print "<option $selected value='8'>$text[type8]</option>\n";}
    if ( "$utext[type]" == "9" ){$selected="selected='true'";}else{$selected="";}if ( $role >= "2" ){print "<option $selected value='9'>$text[type9]</option>\n";}
    print "</select></td></tr>";
    
    $category = $main->getAllCategories();
    print "<tr><td valign='top'>$text[category]</td><td valign='top'> <select name='category'>\n";
    foreach( $category->records as $item )
    {
        $catitem=str_replace(" ","&nbsp;",$item['name']);
        if ( isset($text[$item['name']])){$catitem=str_replace(" ","&nbsp;",$text[$item['name']]);}
        $selected="";
        if ( "$utext[category]" == $item['id'] ){$selected="selected='selected'";}else{$selected="";}
        print "<option $selected value='$item[id]'>$catitem</option>\n";
    }
    print "</select><input name='newcategory' type='text' id='newcategory'/></td></tr>\n";
    if ( $role >= "2" )
    {
        print "<tr><td valign='top'><label for='img'>$text[replaceimg]</label></td><td valign='top'><input type='file' id='img' name='img'/> $text[maxfilesize] $text_upload_max_filesize<input type='hidden' name='MAX_FILE_SIZE' value='$form_upload_max_filesize' /></td></tr>\n";
        if ( isset($utext['img']) and $utext['img'] != "")
        {
            print "<tr><td valign='top'><label for='delimg'>$text[removeimg]</label></td><td valign='top'><input type='checkbox' id='delimg' name='delimg'/>\n";
            print "<br /><img src='thumb/news/$utext[id]/$utext[img]' alt='' align='left' />\n";
            print "</td></tr>\n";
        }
    }
    print "<tr><td valign='top'><label for='header'>$text[header]</label></td><td valign='top'><input name='header' type='text' id='header' value='$utext[headline]' /></td></tr>\n";
    print "<tr><td valign='top' colspan='2'><label for='news'>$text[newstext]</label></td></tr>\n";
    print "<tr><td valign='top' colspan='2'><textarea name='news' rows='20' cols='60'>$utext[data]</textarea></td></tr>\n";
    print "<tr><td valign='top' colspan='2'><label for='extnews'>$text[extnewstext]</label></td></tr>\n";
    print "<tr><td valign='top' colspan='2'><textarea name='extnews' rows='20' cols='60'>$utext[data2]</textarea></td></tr>\n";
    print "<tr><td valign='top' colspan='2'><input type='hidden' name='id' value='$id' /><input type='button' value='$text[savenews]' id='savenews' onclick=\"validate(this.form)\" class='button' /> <input type='reset' value='$text[reset]'  class='button'/></td></tr>\n";
    print "</table></form>\n";
    print "$bbcode";
}
//}}}
//{{{ Viewnews
if ( "$page" == "viewnews" )
{ 
    $_SESSION['lastpage']=$page;
    $start="";if ( isset($_REQUEST['start']) ){$start=$_REQUEST['start'];}
    $id="";if ( isset($_REQUEST['id']) ){$id=$_REQUEST['id'];}elseif( isset($_SESSION['lastid'])){$id=$_SESSION['lastid'];}
    if ($id != "")
    {
        $news=$main->run_query ("select UNIX_TIMESTAMP(n.date) as date,n.access, n.views , n.owner, n.id, n.headline, n.img, n.data, n.data2, length(data2) as length, u.name, u.role, n.order, n.type , n.votes, n.rating,c.id as catid, c.name as category, (select count(c.toid) from comment c where c.toid=n.id and c.type = 1) as comments from news n, user u, category c where  n.owner = u.id and n.id = '$id' and c.id = n.category");
        $main->printnews( $news,"0",$role,$userid,"-1","-1",$page,"" );
    }
    $_SESSION['lastid']=$id;
}
//}}}
//{{{ Cookie information
if ( $page == "cookie" )
{
    print "<span class=\"headline\"><b>$text[cookieheader]</b></span><br /><br />$text[cookietext]";
}
//}}}
//{{{ Password recovery
if ( $page == "pwdrec2" )
    {
        if ( isset($_REQUEST['pwduname']) and isset($_REQUEST['pwdemail']) and $_REQUEST['pwduname'] != ""  and $_REQUEST['pwdemail'] != "" )
        {
            $tempuserinfo=$main->run_query("select * from user where email = '$_REQUEST[pwdemail]' and user = '$_REQUEST[pwduname]'");
        }
        else if ( isset($_REQUEST['pwdemail']) and $_REQUEST['pwdemail'] != "" )
        {
            $tempuserinfo=$main->run_query("select * from user where email = '$_REQUEST[pwdemail]'");
        }
        else if ( isset($_REQUEST['pwduname']) and $_REQUEST['pwduname'] != "" )
        {
            $tempuserinfo=$main->run_query("select * from user where user = '$_REQUEST[pwduname]'");
        }
        if ( isset($tempuserinfo) and $tempuserinfo->rows == 1 and $main->isemail($tempuserinfo->records['0']['email']))
        {
            print "<span class=\"headline\"><b>$text[pwdrecovery] (2/2)</b></span><br /><br />";
            print "$text[pwdrecoverytext2]";
            $_SESSION['pwdid']=rand(100000, 999999);
            $xforwardip="";
            if ( isset($_SERVER['HTTP_X_FORWARDED_FOR']) and $_SERVER['HTTP_X_FORWARDED_FOR'] != "" )
            {
                $xforwardip=" ($_SERVER[HTTP_X_FORWARDED_FOR])";
            }
            $_SESSION['tempuserlogin']=$tempuserinfo->records['0']; 
            $main->sendMail($tempuserinfo->records['0']['email'], $main->edit_array($text['pwdrecoverysubject']." ".$sitetitle),$main->edit_array($sitetitle."<br /><br />".$text['pwdrecoveryemail']." ".$_SESSION['pwdid']."<br />".$text['pwdrecoveryemailbottom']."<br /><br />".$sitetitle."<br /><br />IP= ".$_SERVER['REMOTE_ADDR'].$xforwardip),$adminemail);
            print "<script type='text/javascript'>
                function validate(form)
                {
                    error=\"\";
                    if ( form.pwdinid.value == \"\" )
                    {
                        alert('".$main->edit_array( $text['pwdrecoveryerror2'])."');
                        return;
                    }
                    else
                    {
                        form.submit();
                    }
                }
            </script>";
            print "<form enctype='multipart/form-data' action='?page=pwdrec3' method='post'><p><input type='hidden' name='rid' value='$requestid' />\n";
            print "<table summary='pwd recovery'>\n";
            print "<tr><td>$text[pwdrecoveryid]</td><td><input name='pwdinid' type='text' id='pwdinid'/></td></tr>\n";
            print "<tr><td colspan='2'><input type='button' value='$text[pwdrecoverysend]' id='adduser' onclick=\"validate(this.form)\"  class='button'/> <input type='reset' value='$text[reset]' class='button'/></td></tr>\n";
            print "</table>\n";
            print "</form>"; 
        }
        else
        {
            print "$text[pwdrecoveryerror2]<br /><br />";
            $page = "pwdrec";
        }

    }
if ( $page == "pwdrec" )
{
    print "";
    print "<script type='text/javascript'>
        function validate(form)
        {
            error=\"\";
            if ( form.pwduname.value == \"\" &&  form.pwdemail.value == \"\")
            {
                alert('".$main->edit_array( $text['pwdrecoveryerror1'])."');
                return;
            }
            else
            {
                form.submit();
            }
        }
    </script>";
    print "<span class=\"headline\"><b>$text[pwdrecovery] (1/2)</b></span><br /><br />";
    print "$text[pwdrecoverytext1]";
    print "<form enctype='multipart/form-data' action='?page=pwdrec2' method='post'><p><input type='hidden' name='rid' value='$requestid' />\n";
    print "<table summary='pwd recovery'>\n";
    print "<tr><td>$text[username]</td><td><input name='pwduname' type='text' id='pwduname'/></td></tr>\n";
    print "<tr><td>$text[email]</td><td><input name='pwdemail' type='text' id='pwdemail'/></td></tr>\n";
    print "<tr><td colspan='2'><input type='button' value='$text[pwdrecoverysend]' id='adduser' onclick=\"validate(this.form)\"  class='button'/> <input type='reset' value='$text[reset]' class='button'/></td></tr>\n";
    print "</table>\n";
    print "</form>"; 

}
//}}}
//{{{ Bottom page
print "</td>\n";

if ($page!="splash")
{
if ( $rightcolumn == "true" and $role >= $rightcolumnaccess )
{
    print "<td valign='top' class='menusmall' rowspan='2'>\n";
    $latestnews=$main->getlatestnews($role,$nrlatest);
    print "<b>$text[latestnews]</b><br />";
    foreach( $latestnews->records as $lnews )
    {
        $date=date("y-m-d\&\\n\b\s\p\;H:i:s",$lnews['date']);
        if ($lnews['headline'] == "")
        {
            $lnews['headline']="...";
        }
       print "<a href='?page=viewnews&amp;id=$lnews[id]'>$lnews[headline]</a><br />($date)<br />\n";
    }
    $latestcomments=$main->getlatestcomments($role,$nrlatest);
    print "<br /><b>$text[latestcomments]</b><br />";
    foreach( $latestcomments->records as $lcomment )
    {  
        $date=date("y-m-d\&\\n\b\s\p\;H:i:s",$lcomment['date']);
        if ($lcomment['headline'] == "")
        {
            $lcomment['headline']="...";
        }
        print "<a href='?page=viewnews&amp;id=$lcomment[id]'>$lcomment[headline]</a><br />";
        if ( $lcomment['from'] == 0 and $lcomment['anonname'] != "" )
        {
            print "$lcomment[anonname]<br />";
        }
        elseif ( $lcomment['name'] != "" )
        {
            print "$lcomment[name]<br />";
        }
        print "($date)<br />\n";
    }
    $latestguestbook=$main->getlatestguestbook($role,$nrlatest);
    print "<br /><b>$text[latestguestbook]</b><br />";
    foreach( $latestguestbook->records as $lgbook )
    {  
        $date=date("y-m-d\&\\n\b\s\p\;H:i:s",$lgbook['date']);
        if ($lgbook['headline'] == "")
        {
            $lgbook['headline']="...";
        }
        print "<a href='?page=guestbook'>$lgbook[headline]</a><br />";
        
        if ( $lgbook['from'] == 0 and $lgbook['anonname'] != ""  )
        {
            print "$lgbook[anonname]<br />";
        }
        elseif ( $lgbook['name'] != "" )
        {
            print "$lgbook[name]<br />";
        }
        
        print "($date)<br />\n";
    }
    
    print "</td>";
}


print "</tr>\n";
print "<tr><td class='menusmallbottom'>$text[menusistersites]<br />";
$spacer="";
foreach ($sistersites as $sistersite)
{
    print "$spacer<a href='http://$sistersite' onclick=\"window.open(this.href);return false;\">$sistersite</a>&nbsp;";
    $spacer="<br />";
}
if ( isset( $extrasiteinfo ) and $extrasiteinfo != "" )
{
    print "<br /><br />$extrasiteinfo<br />"; 
}
if ( ($enablecounter == "true" and $showcounter == "true") or ($enablecounter == "true" and $role >= 3 ))
{
    print "<br /><br />$text[counter] $count";
}
print "</td>";
print "</tr></table>\n";
print "</td>";
}
print "<td class='rs'></td></tr><tr><td class='bls'></td><td class='bs'></td><td class='brs'></td></tr></table>\n";
if ($page!="splash")
{
#stop timer:
$etimer = explode( ' ', microtime() );
$etimer = $etimer[1] + $etimer[0];
#print generation time:
print "<table class='tpns' summary='vendor'><tr>";
print "<td class='tpns'><br /><a class='tpns' href=\"http://validator.w3.org/check?uri=referer\" onclick=\"window.open(this.href);return false;\"><img src=\"images/xhtml11.png\" alt=\"Valid XHTML 1.1\"/></a>";

if ( $enablerss == "true" )
{
    print "<br /><a class='tpns' href=\"http://jigsaw.w3.org/css-validator/check/referer\" onclick=\"window.open(this.href);return false;\"><img src=\"images/css.png\" alt=\"Valid CSS!\" /></a>";
}
print "</td><td class='tpns'>";
print "$text[webmaster] <a href='mailto:$adminemail' class='tpns'>$adminemail</a><br />";
$lastupdate=$main->getlastupdate();
if ( $lastupdate != NULL )
{
    $lastupdate=date("Y-m-d H:i:s",$lastupdate);
    print  "$text[lastupdate] $lastupdate<br />";
}
printf( "$text[pagegtime] %f $text[seconds]", ($etimer-$stimer) );
print "<br />$text[poweredby] <a  class='tpns' href='http://tpns.sourceforge.net' onclick=\"window.open(this.href);return false;\">Tiger Php News System 1.0 beta ( build: 39 )</a>.<br />$text[licensetext] <a class='tpns' href='http://www.gnu.org/licenses/gpl.txt'>GPL</a></td>";
print "<td class='tpns'>";

if ( $enablerss == "true" )
{
print "<br /><a  class='tpns' href=\"http://validator.w3.org/feed/check.cgi?url=http%3A//$_SERVER[HTTP_HOST]/rss.php\" onclick=\"window.open(this.href);return false;\"><img src=\"images/rss.png\" alt=\"[Valid RSS]\" /></a><br />
                        <a class='tpns' href=\"http://validator.w3.org/feed/check.cgi?url=http%3A//$_SERVER[HTTP_HOST]/atom.php\" onclick=\"window.open(this.href);return false;\"><img src=\"images/atom.png\" alt=\"[Valid Atom 1.0]\" /></a>";
}
else
{
    print "<br /><a class='tpns' href=\"http://jigsaw.w3.org/css-validator/check/referer\" onclick=\"window.open(this.href);return false;\"><img src=\"images/css.png\" alt=\"Valid CSS!\" /></a>";
}
print "</td></tr></table>";
}
if ( $debug == "on" and !$main->isPublicIp($_SERVER['REMOTE_ADDR']))
{
    //Debug
    print "<pre>";
    print $main->sqlstatments."\n";
    print "page=$page\n";
    print "subpage=$page\n";
    if ( $isbot )
    {
        print "isbot=true\n";
    }
    else
    {
        print "isbot=false\n";
    }
    if ($havecookie)
    {
        print "havecookie=true\n";
    }
    else
    {
        print "havecookie=false\n";
    }
    print "requestid=$requestid\n";
    print "oldrequestid=$oldrequestid\n";
    print "userid=$userid\nrole=$role\n";
    print "_SESSION\n";print_r($_SESSION);
    print "_REQUEST\n";print_r($_REQUEST);
    print "_COOKIE\n";print_r($_COOKIE);
    print "_FILES\n";print_r($_FILES);
    print "plugins\n";print_r($plugins);
    print "siteheader\n";
    print_r($siteheader);
#print "_POST\n";print_r($_POST);
#print "_GET\n";print_r($_GET);
    print "_SERVER\n";print_r($_SERVER);
    print ("text\n");print_r($text);
    print "loaded extensions:\n";
    print_r(get_loaded_extensions());
    print "System information: ".php_uname()."\n";
    print "PHP version: ".phpversion()."\n";
    print "Upload max filesize $upload_max_filesize\n";
    print "Upload max filesize for forms $form_upload_max_filesize\n";
    print ip2long("192.168.0.0");print " = 192.168.0.0 \n";
    print ip2long("172.16.0.0");print " = 172.16.0.0\n";
    print ip2long("169.254.0.0");print " = 169.254.0.0\n";
    print ip2long("10.0.0.0");print " = 10.0.0.0\n";
    print ip2long("127.0.0.0");print " = 127.0.0.0\n";
    ini_set("browscap", "php_browscap.ini");
    $testbrowsercap=ini_get("browscap");
    $browser = get_browser();
    print_r($browser);
    
    
    print "";
    
    print "</pre>";
    //End debug
}
if (!$usedbsessions){$main->closedb();}
print "</body></html>\n";
//}}}   
?>
