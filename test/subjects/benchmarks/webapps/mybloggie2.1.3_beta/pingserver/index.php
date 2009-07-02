<?php
/*
Pingback Server version 0.9 - September 15th 2004. Copyright Andreas Haugstrup Pedersen, 2004. Some Rights Reserved (see below).

This work is licensed under the Creative Commons Attribution-ShareAlike License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/2.0/ or send a letter to Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

Comments are welcome at http://www.solitude.dk/contact.php
*/

/*
INSTALLATION NOTES:
This pingback server relies on the IXR XML-RPC library. You need to download a copy of IXR at http://scripts.incutio.com/xmlrpc/ (save the IXR_Library.inc.php.txt file as IXR_Library.inc.php)

On lines 29 and 30 change the yourdomain.com to whatever your domain is. This ensures that the server only records pingbacks that have a target on your domain.

Upload this file, the XML-file that came along with this file and the IXR_Library.inc.php to the same directory on your webserver. The URL of this file is the URL of your pingback server.

CHMOD the XML file to 666 or 777. This is imperative! After that the server is up and running.
*/

/*
TODO list for this script:
 - pingback.ping : Fetch source to check for source link.
 - pingback.ping : Save excerpt if source is text.
 - pingback.ping : Check if target exists.
*/

// Domains we record pingbacks from. Change these to your own domain.
$pingback_sites[] = "http://www.yourdomain.com/";
$pingback_sites[] = "http://yourdomain.com/";

// Paths.
require("IXR_Library.inc.php"); // Path to the IXR XML-RPC library.
$xmlfile = "pingbacks.xml"; // Path to the XML-file.

header("Content-Type: text/xml;charset=ISO-8859-1");
$server = new IXR_Server(array('pingback.ping' => 'recordPingback','pingback.extensions.getPingbacks' => 'getPingbacks'));

function recordPingback($args) { // Saves a pingback on the server.
    global $pingbacks, $pingback_sites, $xmlfile;
    if (is_array($args)) {
        $source = trim($args[0]);
        $target = trim($args[1]);
        $status = "";
        // Check if target is a valid domain.
        foreach ($pingback_sites as $domain) {
            if (substr($target, 0, strlen($domain)) == $domain) {
                $status = "ok";
            }
        }
        if ($status == "ok") {
            // Check if pingback has already been registered.
            if (parsePingbackXML($xmlfile, "startPB", "endPB", "PBdata")) {
                foreach ($pingbacks as $p) {
                    if ($p["t"] == $target && $p["s"] == $source) {
                        $status = "notOk";
                    }
                }
                if ($status != "notOk") {
                    // This is where we should fetch the source document to see if it actually links to the target. To speed up developement we'll skip this step for now.

                    // This is also where we should see if the target actually exists.

                    // Adding pingback.
                    $newId = count($pingbacks);
                    $pingbacks[$newId]["time"] = mktime();
                    $pingbacks[$newId]["t"] = $target;
                    $pingbacks[$newId]["s"] = $source;
                    // Saving XML-file.
                    $xml = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\r\n";?><?php
                    $xml = "{$xml}<pingbacks>\r\n";
                    foreach ($pingbacks as $p) {
                        $xml = "{$xml}<p time=\"{$p["time"]}\"><s><![CDATA[{$p["s"]}]]></s><t><![CDATA[{$p["t"]}]]></t></p>\r\n";
                    }
                    $xml = "{$xml}</pingbacks>\r\n";
                    if (is_writeable($xmlfile)) {
                        $fp = fopen($xmlfile, "wb");
                        fputs ($fp, $xml);
                        fclose($fp);
                        // Success!
                        $return = "Success! Have a nice day.";
                        return $return;
                    } else {
                        return new IXR_Error(-32400, 'System error.');
                    }
                } else {
                    return new IXR_Error(48, 'The pingback has already been registered.');
                }
            } else {
                return new IXR_Error(-32400, 'System error.');
            }
        } else {
            return new IXR_Error(33, 'This server is not the pingback server for this target.');
        }
    } else {
        return new IXR_Error(-32602, 'Server error. Invalid method parameters.');
    }
}
function getPingbacks($t) { // Gets recorded pingbacks for an URL.
    global $pingbacks, $pingback_sites, $xmlfile;
    $return = array();
    if (is_array($t)) {
        $t = $t[0];
    }
    // Check if this server is the server for the target.
    foreach ($pingback_sites as $url) {
        if ($url == substr($t, 0, strlen($url))) {
            $status = "ok";
        }
    }
    if ($status == "ok") {
        if (parsePingbackXML($xmlfile, "startPB", "endPB", "PBdata")) {
            foreach ($pingbacks as $p) {
                if ($p["t"] == $t) {
                    $return[] = $p["s"];
                }
            }
            return $return;
        } else {
            return new IXR_Error(-32400, 'System error.');
        }
    } else {
        return new IXR_Error(-32400, 'System error. This pingback server is not accepting pingbacks from this URL.');
    }
}
function parsePingbackXML($xmlfile, $start, $end, $cdata) { /* This function parses an XML file. */
    global $xml_parser, $pingbacks;
    $xml_parser = xml_parser_create();
    xml_parser_set_option ($xml_parser, XML_OPTION_CASE_FOLDING, 0);
    xml_set_element_handler($xml_parser, $start, $end);
    xml_set_character_data_handler($xml_parser, $cdata);
    $pingbacks = array();
    if ($fp = @fopen($xmlfile, "r")) {
        while ($data = fread($fp, filesize($xmlfile))) {
            if (!@xml_parse($xml_parser, $data, feof($fp))) {
                return FALSE;
            }
        }
        return TRUE;
    } else {
        return FALSE;
    }
    xml_parser_free($xml_parser);
}
function startPB($parser, $name, $a) { /* This function is executed everytime an xml start tag is met. */
    global $currentTag, $currentId, $pingbacks;
    $currentTag = $name;
    if ($currentTag == "p") {
        $currentId = count($pingbacks);
        $pingbacks[$currentId]["time"] = $a["time"];
    }
}
function PBData($parser, $data) { /* This function is executed on all xml content. */
    global $currentTag, $currentId, $pingbacks;
    // Add timestamp to it's own array so we can sort them later.
    if ($currentTag == "s") {
        $pingbacks[$currentId]["s"] = $data;
    } elseif ($currentTag == "t") {
        $pingbacks[$currentId]["t"] = $data;
    }
}
function endPB($parser, $name) { /* This function is executed everytime an xml end tag is met. */
    global $currentTag, $currentId, $pingbacks;
    $currentTag = "";
}
?>