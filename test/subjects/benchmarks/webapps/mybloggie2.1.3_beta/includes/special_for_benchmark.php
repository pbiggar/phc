<?php

	// phc wasnt having great luck compiling this (method_aliases and class_aliases), so we've moved conditionally defined things up here.
           function sendmail( $from, $to, $subject, $body )
           {
           $headers  = "MIME-Version: 1.0\r\n";
           $headers .= "Content-type: text/plain\r\n";
           $headers .= "From: {$from}\r\n";
           $result = @mail( $to, $subject, $body, $headers );
           if( $result ) return true;
           }
class tb
{
    /**** Public variables ****/
    
    /* user definable vars */

    var $host            =    "www.php.net";        // host name we are connecting to
    var $port            =    80;                    // port we are connecting to
    var $proxy_host      =    "";                    // proxy host to use
    var $proxy_port      =    "";                    // proxy port to use
    var $proxy_user      =    "";                    // proxy user to use
    var $proxy_pass      =    "";                    // proxy password to use
    
    var $agent           =    "Snoopy v1.2";        // agent we masquerade as
    var $referer         =    "";                    // referer info to pass
    var $cookies         =    array();            // array of cookies to pass
                                                // $cookies["username"]="joe";
    var $rawheaders      =    array();            // array of raw headers to send
                                                // $rawheaders["Content-type"]="text/html";

    var $maxredirs        =    5;                    // http redirection depth maximum. 0 = disallow
    var $lastredirectaddr =    "";                // contains address of last redirected address
    var $offsiteok        =    true;                // allows redirection off-site
    var $maxframes        =    0;                    // frame content depth maximum. 0 = disallow
    var $expandlinks      =    true;                // expand links to fully qualified URLs.
                                                // this only applies to fetchlinks()
                                                // or submitlinks()
    var $passcookies      =    true;                // pass set cookies back through redirects
                                                // NOTE: this currently does not respect
                                                // dates, domains or paths.
    
    var    $user            =    "";                    // user for http authentication
    var    $pass            =    "";                    // password for http authentication
    
    // http accept types
    var $accept            =    "image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, */*";
    
    var $results        =    "";                    // where the content is put
        
    var $error            =    "";                    // error messages sent here
    var    $response_code    =    "";                    // response code returned from server
    var    $headers        =    array();            // headers returned from server sent here
    var    $maxlength        =    500000;                // max return data length (body)
    var $read_timeout    =    0;                    // timeout on read operations, in seconds
                                                // supported only since PHP 4 Beta 4
                                                // set to 0 to disallow timeouts
    var $timed_out        =    false;                // if a read operation timed out
    var    $status            =    0;                    // http request status

    var $temp_dir        =    "/tmp";                // temporary directory that the webserver
                                                // has permission to write to.
                                                // under Windows, this should be C:\temp

    var    $curl_path        =    "/usr/local/bin/curl";
                                                // Snoopy will use cURL for fetching
                                                // SSL content if a full system path to
                                                // the cURL binary is supplied here.
                                                // set to false if you do not have
                                                // cURL installed. See http://curl.haxx.se
                                                // for details on installing cURL.
                                                // Snoopy does *not* use the cURL
                                                // library functions built into php,
                                                // as these functions are not stable
                                                // as of this Snoopy release.
    
    /**** Private variables ****/    
    
    var    $_maxlinelen    =    4096;                // max line length (headers)
    
    var $_httpmethod    =    "GET";                // default http request method
    var $_httpversion    =    "HTTP/1.0";            // default http request version
    var $_submit_method    =    "POST";                // default submit method
    var $_submit_type    =    "application/x-www-form-urlencoded";    // default submit type
    var $_mime_boundary    =   "";                    // MIME boundary for multipart/form-data submit type
    var $_redirectaddr    =    false;                // will be set if page fetched is a redirect
    var $_redirectdepth    =    0;                    // increments on an http redirect
    var $_frameurls        =     array();            // frame src urls
    var $_framedepth    =    0;                    // increments on frame depth
    
    var $_isproxy        =    false;                // set if using a proxy server
    var $_fp_timeout    =    30;                    // timeout for socket connection


/*======================================================================*\
    Function:    submit
    Purpose:    submit an http form
    Input:        $URI    the location to post the data
                $formvars    the formvars to use.
                    format: $formvars["var"] = "val";
                $formfiles  an array of files to submit
                    format: $formfiles["var"] = "/dir/filename.ext";
    Output:        $this->results    the text output from the post
\*======================================================================*/

    function submit($URI, $formvars="", $formfiles="")
    {
        unset($postdata);
        
        $postdata = $this->_prepare_post_body($formvars, $formfiles);
            
        $URI_PARTS = parse_url($URI);
        if (!empty($URI_PARTS["user"]))
            $this->user = $URI_PARTS["user"];
        if (!empty($URI_PARTS["pass"]))
            $this->pass = $URI_PARTS["pass"];
        if (empty($URI_PARTS["query"]))
            $URI_PARTS["query"] = '';

        switch($URI_PARTS["scheme"])
        {
            case "http":
                $this->host = $URI_PARTS["host"];
                if(!empty($URI_PARTS["port"]))
                    $this->port = $URI_PARTS["port"];
                if($this->_connect($fp))
                {
                    if($this->_isproxy)
                    {
                        // using proxy, send entire URI
                        $this->_httprequest($URI,$fp,$URI,$this->_submit_method,$this->_submit_type,$postdata);
                    }
                    else
                    {
                        $path = $URI_PARTS["path"].($URI_PARTS["query"] ? "?".$URI_PARTS["query"] : "");
                        // no proxy, send only the path
                        $this->_httprequest($path, $fp, $URI, $this->_submit_method, $this->_submit_type, $postdata);
                    }
                    
                    $this->_disconnect($fp);

                    if($this->_redirectaddr)
                    {
                        /* url was redirected, check if we've hit the max depth */
                        if($this->maxredirs > $this->_redirectdepth)
                        {                        
                            if(!preg_match("|^".$URI_PARTS["scheme"]."://|", $this->_redirectaddr))
                                $this->_redirectaddr = $this->_expandlinks($this->_redirectaddr,$URI_PARTS["scheme"]."://".$URI_PARTS["host"]);                        
                            
                            // only follow redirect if it's on this site, or offsiteok is true
                            if(preg_match("|^http://".preg_quote($this->host)."|i",$this->_redirectaddr) || $this->offsiteok)
                            {
                                /* follow the redirect */
                                $this->_redirectdepth++;
                                $this->lastredirectaddr=$this->_redirectaddr;
                                if( strpos( $this->_redirectaddr, "?" ) > 0 )
                                    $this->fetch($this->_redirectaddr); // the redirect has changed the request method from post to get
                                else
                                    $this->submit($this->_redirectaddr,$formvars, $formfiles);
                            }
                        }
                    }

                    if($this->_framedepth < $this->maxframes && count($this->_frameurls) > 0)
                    {
                        $frameurls = $this->_frameurls;
                        $this->_frameurls = array();
                        
                        foreach ($frameurls as $frameurl)
                        {                                                        
                            if($this->_framedepth < $this->maxframes)
                            {
                                $this->fetch($frameurl);
                                $this->_framedepth++;
                            }
                            else
                                break;
                        }
                    }                    
                    
                }
                else
                {
                    return false;
                }
                return true;                    
                break;
            case "https":
                if(!$this->curl_path)
                    return false;
                if(function_exists("is_executable"))
                    if (!is_executable($this->curl_path))
                        return false;
                $this->host = $URI_PARTS["host"];
                if(!empty($URI_PARTS["port"]))
                    $this->port = $URI_PARTS["port"];
                if($this->_isproxy)
                {
                    // using proxy, send entire URI
                    $this->_httpsrequest($URI, $URI, $this->_submit_method, $this->_submit_type, $postdata);
                }
                else
                {
                    $path = $URI_PARTS["path"].($URI_PARTS["query"] ? "?".$URI_PARTS["query"] : "");
                    // no proxy, send only the path
                    $this->_httpsrequest($path, $URI, $this->_submit_method, $this->_submit_type, $postdata);
                }

                if($this->_redirectaddr)
                {
                    /* url was redirected, check if we've hit the max depth */
                    if($this->maxredirs > $this->_redirectdepth)
                    {                        
                        if(!preg_match("|^".$URI_PARTS["scheme"]."://|", $this->_redirectaddr))
                            $this->_redirectaddr = $this->_expandlinks($this->_redirectaddr,$URI_PARTS["scheme"]."://".$URI_PARTS["host"]);                        

                        // only follow redirect if it's on this site, or offsiteok is true
                        if(preg_match("|^http://".preg_quote($this->host)."|i",$this->_redirectaddr) || $this->offsiteok)
                        {
                            /* follow the redirect */
                            $this->_redirectdepth++;
                            $this->lastredirectaddr=$this->_redirectaddr;
                            if( strpos( $this->_redirectaddr, "?" ) > 0 )
                                $this->fetch($this->_redirectaddr); // the redirect has changed the request method from post to get
                            else
                                $this->submit($this->_redirectaddr,$formvars, $formfiles);
                        }
                    }
                }

                if($this->_framedepth < $this->maxframes && count($this->_frameurls) > 0)
                {
                    $frameurls = $this->_frameurls;
                    $this->_frameurls = array();

                    foreach ($frameurls as $frameurl)
                    {                                                        
                        if($this->_framedepth < $this->maxframes)
                        {
                            $this->fetch($frameurl);
                            $this->_framedepth++;
                        }
                        else
                            break;
                    }
                }                    
                return true;                    
                break;
                
            default:
                // not a valid protocol
                $this->error    =    'Invalid protocol "'.$URI_PARTS["scheme"].'"\n';
                return false;
                break;
        }        
        return true;
    }


    function _prepare_post_body($formvars, $formfiles)
    {
        settype($formvars, "array");
        settype($formfiles, "array");
        $postdata = '';

        if (count($formvars) == 0 && count($formfiles) == 0)
            return;
        
        switch ($this->_submit_type) {
            case "application/x-www-form-urlencoded":
					 foreach ($formvars as $key => $val)
					 {
                    if (is_array($val) || is_object($val)) {
							  foreach ($val as $cur_key => $cur_val)
							  {
                            $postdata .= urlencode($key)."[]=".urlencode($cur_val)."&";
							  }
                    } else
                        $postdata .= urlencode($key)."=".urlencode($val)."&";
                }
                break;

            case "multipart/form-data":
                $this->_mime_boundary = "Snoopy".md5(uniqid(microtime()));
                
                foreach ($formvars as $key => $val)
					 {
                    if (is_array($val) || is_object($val)) {
							  foreach ($val as $cur_key => $cur_val) {
                            $postdata .= "--".$this->_mime_boundary."\r\n";
                            $postdata .= "Content-Disposition: form-data; name=\"$key\[\]\"\r\n\r\n";
                            $postdata .= "$cur_val\r\n";
                        }
                    } else {
                        $postdata .= "--".$this->_mime_boundary."\r\n";
                        $postdata .= "Content-Disposition: form-data; name=\"$key\"\r\n\r\n";
                        $postdata .= "$val\r\n";
                    }
                }
                
                foreach ($formfiles as $field_name => $filenames) {
                    settype($file_names, "array");
						  foreach ($filenames as $file_name)
						  {
                        if (!is_readable($file_name)) continue;

                        $fp = fopen($file_name, "r");
                        $file_content = fread($fp, filesize($file_name));
                        fclose($fp);
                        $base_name = basename($file_name);

                        $postdata .= "--".$this->_mime_boundary."\r\n";
                        $postdata .= "Content-Disposition: form-data; name=\"$field_name\"; filename=\"$base_name\"\r\n\r\n";
                        $postdata .= "$file_content\r\n";
                    }
                }
                $postdata .= "--".$this->_mime_boundary."--\r\n";
                break;
        }

        return $postdata;
    }
    
    function _connect(&$fp)
    {
        if(!empty($this->proxy_host) && !empty($this->proxy_port))
            {
                $this->_isproxy = true;
                
                $host = $this->proxy_host;
                $port = $this->proxy_port;
            }
        else
        {
            $host = $this->host;
            $port = $this->port;
        }
    
        $this->status = 0;
        
        if($fp = fsockopen(
                    $host,
                    $port,
                    $errno,
                    $errstr,
                    $this->_fp_timeout
                    ))
        {
            // socket connection succeeded

            return true;
        }
        else
        {
            // socket connection failed
            $this->status = $errno;
            switch($errno)
            {
                case -3:
                    $this->error="socket creation failed (-3)";
                case -4:
                    $this->error="dns lookup failure (-4)";
                case -5:
                    $this->error="connection refused or timed out (-5)";
                default:
                    $this->error="connection failed (".$errno.")";
            }
            return false;
        }
    }
     
    function _httprequest($url,$fp,$URI,$http_method,$content_type="",$body="")
    {
        $cookie_headers = '';
        if($this->passcookies && $this->_redirectaddr)
            $this->setcookies();
            
        $URI_PARTS = parse_url($URI);
        if(empty($url))
            $url = "/";
        $headers = $http_method." ".$url." ".$this->_httpversion."\r\n";        
        if(!empty($this->agent))
            $headers .= "User-Agent: ".$this->agent."\r\n";
        if(!empty($this->host) && !isset($this->rawheaders['Host']))
            $headers .= "Host: ".$this->host."\r\n";
        if(!empty($this->accept))
            $headers .= "Accept: ".$this->accept."\r\n";
        if(!empty($this->referer))
            $headers .= "Referer: ".$this->referer."\r\n";
        if(!empty($this->cookies))
        {            
            if(!is_array($this->cookies))
                $this->cookies = (array)$this->cookies;
    
            if ( count($this->cookies) > 0 ) {
                $cookie_headers .= 'Cookie: ';
                foreach ( $this->cookies as $cookieKey => $cookieVal ) {
                $cookie_headers .= $cookieKey."=".urlencode($cookieVal)."; ";
                }
                $headers .= substr($cookie_headers,0,-2) . "\r\n";
            } 
        }
        if(!empty($this->rawheaders))
        {
            if(!is_array($this->rawheaders))
                $this->rawheaders = (array)$this->rawheaders;
            foreach ($this->rawheaders as $headerKey => $headerVal)
                $headers .= $headerKey.": ".$headerVal."\r\n";
        }
        if(!empty($content_type)) {
            $headers .= "Content-type: $content_type";
            if ($content_type == "multipart/form-data")
                $headers .= "; boundary=".$this->_mime_boundary;
            $headers .= "\r\n";
        }
        if(!empty($body))    
            $headers .= "Content-length: ".strlen($body)."\r\n";
        if(!empty($this->user) || !empty($this->pass))    
            $headers .= "Authorization: Basic ".base64_encode($this->user.":".$this->pass)."\r\n";
        
        //add proxy auth headers
        if(!empty($this->proxy_user))    
            $headers .= 'Proxy-Authorization: ' . 'Basic ' . base64_encode($this->proxy_user . ':' . $this->proxy_pass)."\r\n";


        $headers .= "\r\n";
        
        // set the read timeout if needed
        if ($this->read_timeout > 0)
            socket_set_timeout($fp, $this->read_timeout);
        $this->timed_out = false;
        
        fwrite($fp,$headers.$body,strlen($headers.$body));
        
        $this->_redirectaddr = false;
        unset($this->headers);
                        
        while($currentHeader = fgets($fp,$this->_maxlinelen))
        {
            if ($this->read_timeout > 0 && $this->_check_timeout($fp))
            {
                $this->status=-100;
                return false;
            }
                
            if($currentHeader == "\r\n")
                break;
                        
            // if a header begins with Location: or URI:, set the redirect
            if(preg_match("/^(Location:|URI:)/i",$currentHeader))
            {
                // get URL portion of the redirect
                preg_match("/^(Location:|URI:)[ ]+(.*)/",chop($currentHeader),$matches);
                // look for :// in the Location header to see if hostname is included
                if(!preg_match("|\:\/\/|",$matches[2]))
                {
                    // no host in the path, so prepend
                    $this->_redirectaddr = $URI_PARTS["scheme"]."://".$this->host.":".$this->port;
                    // eliminate double slash
                    if(!preg_match("|^/|",$matches[2]))
                            $this->_redirectaddr .= "/".$matches[2];
                    else
                            $this->_redirectaddr .= $matches[2];
                }
                else
                    $this->_redirectaddr = $matches[2];
            }
        
            if(preg_match("|^HTTP/|",$currentHeader))
            {
                if(preg_match("|^HTTP/[^\s]*\s(.*?)\s|",$currentHeader, $status))
                {
                    $this->status= $status[1];
                }                
                $this->response_code = $currentHeader;
            }
                
            $this->headers[] = $currentHeader;
        }

        $results = '';
        do {
            $_data = fread($fp, $this->maxlength);
            if (strlen($_data) == 0) {
                break;
            }
            $results .= $_data;
        } while(true);

        if ($this->read_timeout > 0 && $this->_check_timeout($fp))
        {
            $this->status=-100;
            return false;
        }
        
        // check if there is a a redirect meta tag
        
        if(preg_match("'<meta[\s]*http-equiv[^>]*?content[\s]*=[\s]*[\"\']?\d+;[\s]*URL[\s]*=[\s]*([^\"\']*?)[\"\']?>'i",$results,$match))

        {
            $this->_redirectaddr = $this->_expandlinks($match[1],$URI);    
        }

        // have we hit our frame depth and is there frame src to fetch?
        if(($this->_framedepth < $this->maxframes) && preg_match_all("'<frame\s+.*src[\s]*=[\'\"]?([^\'\"\>]+)'i",$results,$match))
        {
            $this->results[] = $results;
            for($x=0; $x<count($match[1]); $x++)
                $this->_frameurls[] = $this->_expandlinks($match[1][$x],$URI_PARTS["scheme"]."://".$this->host);
        }
        // have we already fetched framed content?
        elseif(is_array($this->results))
            $this->results[] = $results;
        // no framed content
        else
            $this->results = $results;
        
        return true;
    }
    
    function _disconnect($fp)
    {
        return(fclose($fp));
    }
  function trackback_reply($error = 0, $error_message = '')
   {
    echo '<?xml version="1.0" encoding="iso-8859-1"?'.">\n";
    echo "<response>\n";
    echo "<error>$error</error>\n";
    echo "<message>$error_message</message>\n";
    echo "</response>";
    die();
   }
}

function do_upload($upload_dir, $upload_url) {

  $temp_name = $_FILES['userfile']['tmp_name'];
  $file_name = $_FILES['userfile']['name']; 
  $file_name = str_replace("\\","",$file_name);
  $file_name = str_replace("'","",$file_name);
  $file_path = $upload_dir.$file_name;

  //File Name Check
  if ( $file_name =="") { 
    $message = "Invalid File Name Specified";
    return $message;
  }

  $result  =  move_uploaded_file($temp_name, $file_path);
  if (!chmod($file_path,0755))
     $message = "change permission to 755 failed 1.";
  else
    $message = ($result)?"$file_name uploaded successfully." :
             "Somthing is wrong with uploading a file.";
  return $message;
}    //

function thumbnail() {

global  $max_width, $max_height;

$file_name = $_FILES['userfile']['name'];
$tempfilename = $_FILES['userfile']['tmp_name'];  // temporary file at server side


if ( extension_loaded( 'gd' ) ) {

// read image
$tempfile = fopen($tempfilename, "r");
$binaryimage = fread($tempfile, fileSize($tempfilename)); // Try to read image
$old_error_reporting = error_reporting(E_ALL & ~(E_WARNING));// ingore warnings
$src_img = imagecreatefromstring($binaryimage);  // try to create image
error_reporting($old_error_reporting);

$size=GetImageSize($tempfilename);

$width_ratio  = ($size[0] / $max_width);
$height_ratio = ($size[1] / $max_height);

if($width_ratio >=$height_ratio)
{
   $ratio = $width_ratio;
}
else
{
   $ratio = $height_ratio;
}

$new_width    = ($size[0] / $ratio);
$new_height   = ($size[1] / $ratio);

if ($file_name) // file uploaded
{ $filenameparts = explode(".", $file_name);
   $ext =  array_pop($filenameparts);
   $new_name =  $filenameparts[0]."_thumb.".$ext ;
}

$thumb = ImageCreateTrueColor($new_width,$new_height);
ImageCopyResampled($thumb, $src_img, 0,0,0,0,($new_width),($new_height),$size[0],$size[1]);

if ( strtolower($ext) == "png" )
{
   imagepng($thumb, "./files/".$new_name);
}
else if ( strtolower($ext)== "jpg" || strtolower($ext)== "jpeg")
{
   imagejpeg($thumb, "./files/".$new_name);
}
else if ( strtolower($ext)== "gif"  )
{
   imagegif($thumb, "./files/".$new_name);
}
else echo 'Cannot find a suitable output format';

ImageDestroy($src_img);
ImageDestroy($thumb);

}
else { echo 'GD-library support is not available'; }

}



function check_postid($post_id) {
  global $db ;

  $sql = "SELECT post_id FROM ". POST_TBL." WHERE post_id=".$post_id;
  $result = $db->sql_query($sql);
  if ( $db->sql_numrows($result)== 0  )
     {
       error( 'Error', 'Post Id selected not VALID' ) ;
     }
}
function check_commentid($comment_id) {
  global $db ;

  $sql = $sql = "SELECT ".COMMENT_TBL.".comment_id FROM ".COMMENT_TBL." WHERE ".COMMENT_TBL.".comment_id = ".$comment_id;
  $result = $db->sql_query($sql);
  if ( $db->sql_numrows($result)== 0  )
     {
       error( 'Error', 'Comment Id selected not VALID' ) ;
     }
}

function check_catid($cat_id) {
  global $db ;

  $sql = $sql = "SELECT ".CAT_TBL.".cat_id FROM ".CAT_TBL." WHERE ".CAT_TBL.".cat_id = ".$cat_id;
  $result = $db->sql_query($sql);
  if ( $db->sql_numrows($result)== 0  )
     {
       error( 'Error', 'Cat Id selected not VALID' ) ;
     }
}


class cls_encrypt
{
    var $_key;

    function cls_encrypt()
    {

// This is your private key. Set to something else
// when using in your site.

        $this->_key = "php_example";
        return 1;
    }    

    function keyED($txt)
    {
        $encrypt_key = md5($this->_key);
        $ctr=0;
        $tmp = "";
        for ($i=0;$i<strlen($txt);$i++)
             {
             if ($ctr==strlen($encrypt_key)) $ctr=0;
             $tmp.= substr($txt,$i,1) ^ substr($encrypt_key,$ctr,1);
             $ctr++;
             }
        return $tmp;
    }

    function html_encrypt ($txt)
    {
        return urlencode($this->encrypt($txt));
    }

    function encrypt($txt)
    {
        
// Public key, which we always set to a unique value.

        $encrypt_key = md5(microtime());
        $ctr=0;
        $tmp = "";
        for ($i=0;$i<strlen($txt);$i++)
        {
             if ($ctr==strlen($encrypt_key)) $ctr=0;
             $tmp.= substr($encrypt_key,$ctr,1) .
             (substr($txt,$i,1) ^ substr($encrypt_key,$ctr,1));
             $ctr++;
         }
        return $this->keyED($tmp);
    }

    function html_decrypt($txt)
    {
        return $this->decrypt(urldecode($txt));
    }

    function decrypt($txt)
    {
        $txt = $this->keyED($txt);
        $tmp = "";
        for ($i=0;$i<strlen($txt);$i++)
        {
             $md5 = substr($txt,$i,1);
             $i++;
             $tmp.= (substr($txt,$i,1) ^ $md5);
        }
        return $tmp;
    }
}

function single_tb($tb) {
  // Send trackback ping and display results
  // For specifications, see http://www.movabletype.org/docs/mttrackback.html
  global $pingError, $pingReply ;

  $tback = new tb;

  //$submitURL = $tb['tbURL'];
  $submitURL = $tb_url;
  $submitVars['Content-Type'] = 'application/x-www-form-urlencoded';
  $submitVars['title']        = $tb['blogEntryTitle'];
  $submitVars['url']          = $tb['blogEntryURL'];
  $submitVars['blog_name']    = $tb['blogName'];
  $submitVars['excerpt']      = $tb['blogExcerpt'];

  $tback->submit($submitURL, $submitVars);
  $pingReply = $tback->results;
  
  // search through XML reply for any ping errors

  /**
  if (ereg('<error>([01])</error>', $pingReply, $pieces)) {
    $pingError = $pieces[1];
    }
  else {
    $pingError = 1;
    }
  if (!$pingError) {
    $perror = 'Trackback was successful!';
    }
  else {
    if (ereg('<message>(.{0,})</message>', $pingReply, $pieces)) {
      $perror = 'Error:&nbsp; '.$pieces[1];
      }
    else {
      $perror = 'Error:&nbsp; Unknown';
      }
    } **/
      //echo $pingError;

  if (ereg('<error>([01])</error>', $pingReply, $pieces)) {
    $pingError = $pieces[1];
    }
  else {
    $pingError = 1;
    }
  return $pingError ;
    }

function multi_tb($post_urls, $tb) {
  // Send trackback ping to multiple urls and display results
  // For specifications, see http://www.movabletype.org/docs/mttrackback.html
  global $tbreply ;
  $tbreply ="";
  $tback = new tb;
  $submitVars['Content-Type'] = 'application/x-www-form-urlencoded';
  $submitVars['title']        = $tb['blogEntryTitle'];
  $submitVars['url']          = $tb['blogEntryURL'];
  $submitVars['blog_name']    = $tb['blogName'];
  $submitVars['excerpt']      = $tb['blogExcerpt'];

  $tb_urls = split('( )+', $post_urls,10);
  foreach($tb_urls as $tb_url) {
     // Send trackback to all url:
     $tb_url = trim($tb_url);
     if( empty( $tb_url ) ) continue;
     //echo $tb_url;
     $tback->submit($tb_url, $submitVars);
     $pingReply = $tback->results;

     // search through XML reply for any ping errors
     if (ereg('<error>([01])</error>', $pingReply, $pieces)) {
       $pingError = $pieces[1];
       }
     else {
       $pingError = 1;
       }
     if (!$pingError) {
       $tbreply .= "Sending to <b>".$tb_url."</b><br /> Trackback Response : Trackback was successful!";
       }
     else {
       if (ereg('<message>(.{0,})</message>', $pingReply, $pieces)) {
          $tbreply .= "Sending to <b>".$tb_url."</b><br /> Trackback Response : ".$pieces[1];
          }
          else {
         $tbreply .= "Sending to <b>".$tb_url."</b><br /> Trackback Response : Error! :".$pingReply;
         }
     }
     $tbreply .= "<br />";
  }
}
