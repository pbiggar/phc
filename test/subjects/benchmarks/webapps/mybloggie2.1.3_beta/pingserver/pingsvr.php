<?php
//require "settings";
//checks settings to see if Pingback is enabled
//if (!PINGBACK)
{exit;}
//includes Incutio XML-RPC library (http://scripts.incutio.com/xmlrpc/)
include_once('./includes/IXR_Library.inc.php');
//checks settings to see if logging is enabled
//if (PINGLOG)
//{
//$log = @fopen($_SERVER['DOCUMENT_ROOT'].PATH."dat/pingback.log", "a");
//}
//runs server
$pingback = new IXR_Server(array('pingback.ping' => 'pingback'));


function pingback($var)
{global $SQL, $log;
  $source = $var[0];
  $target = $var[1];
  //allows permalink with comments, but normalises
  $target = str_replace("&discuss", "", $target);
  $id = substr(strrchr($target, "="), 1);
  $src = addslashes($source);

//error checking

  //check if the ping is for the right log
  if (strpos($target, DOMAIN.PATH)===FALSE)
   {@fwrite($log, "($target <=> $source) 0x0031\n");
    return new IXR_Error(49, "target is not handled by this server");}
  //perform HEAD request on the local entry
  $pointer = @fopen($target, "r");
  $head = implode("\n", $http_response_header);
  @fclose($pointer);
  //check for 404
  if (strpos($head, "404 Not Found")!==FALSE)
   {@fwrite($log, "($target <=> $source) 0x0020\n");
    return new IXR_Error(32, "target does not exist");}
  //check if local URI is a permalink (via custom HTTP header)
  if (strpos($head, "X-Permalink: Yes")===FALSE)
   {@fwrite($log, "($target <=> $source) 0x0021\n");
    return new IXR_Error(33, "target is not a permalink");}
  //check if the ping has been recorded
  $query = mysql_query("select post from log_pingback where post = '$id' and source = '$src'", $SQL);
  if (mysql_num_rows($query) > 0)
   {@fwrite($log, "($target <=> $source) 0x0030\n");
    return new IXR_Error(48, "ping from source already recorded");}
  //perform HEAD request on remote entry
  $pointer = @fopen($source, "r");
  $head = implode("\n", $http_response_header);
  @fclose($pointer);
  //check for 404
  if (strpos($head, "404 Not Found")!==FALSE)
   {@fwrite($log, "($target <=> $source) 0x0010\n");
    return new IXR_Error(16, "source does not exist");}
  if (strpos($head, "403 Forbidden")!==FALSE)
   {@fwrite($log, "($target <=> $source) 0x0031\n");
    return new IXR_Error(49, "access to source denied");}
  //check for text or XML content-type
  if (preg_match("!content-type: (text/|application/.+?\+xml|application/xml)!i", $head)==0)
   {@fwrite($log, "($target <=> $source) 0\n");
    return new IXR_Error(0, "source is not a text resource");}
  //check for presence of local URI in remote file
  $file = @file_get_contents($source);
  if (strpos($file, $target)===FALSE)
   {@fwrite($log, "($target <=> $source) 0x0011\n");
    return new IXR_Error(17, "source does not link to target");}

//done error checking; gather data

  //grab remote document title
  preg_match("!<title>(.+?)</title>!i", $file, $match);
  $title = $match[1];
  //grab remote document language
  preg_match("!content-language: (.+?)$!i", $head, $match);
  if (!$match[1])
       {preg_match("!<html.+?lang(=\"|='|=)(.+?)('|\"|>)!i", $file, $match);
        $lang = $match[2];}
  else {$lang = $match[1];}

//done gathering data (for now--not sure what else can be accounted for); enter into Db

  $title = addslashes($title);
  $lang = addslashes($lang);
  $query = "insert into log_pingback values('$id', '$src', '$title', '$lang', NOW() )";
  mysql_query($query, $SQL);
  @fwrite($log, "($target <=> $source) OK\n");
  return "#$id pinged OK";
}

?> 
