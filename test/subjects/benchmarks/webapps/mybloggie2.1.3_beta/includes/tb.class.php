<?php

/*************************************************
This script of extracted & modified from

Snoopy - the PHP net client
Author: Monte Ohrt <monte@ispi.net>
Copyright (c): 1999-2000 ispi, all rights reserved
Version: 1.2

The latest version of Snoopy can be obtained from:
http://snoopy.sourceforge.net/

*************************************************/

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


?>
