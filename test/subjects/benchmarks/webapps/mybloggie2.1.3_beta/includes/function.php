<?

// Blog Script - File Name : function.php
//Copyright (C) myBloggie 2004 Sean

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


function verifyuser()
    {   global $username, $passwd ;
        session_start();
        //session_cache_limiter('private');
        header("Cache-control: private");
        if (isset($_SESSION['username']) && isset($_SESSION['passwd']))
        {
            $username = $_SESSION['username'] ;
            $passwd = $_SESSION['passwd'] ;

            $sql = "SELECT user, password FROM ".USER_TBL." WHERE user='$username' AND password='$passwd'";
            $result = mysql_query( $sql ) or error( mysql_error() );
            if( mysql_num_rows( $result ) == 1 ) return true;
        }
        return false;
    }

// GMT Date function
function gmtdate($format, $gmepoch, $timezone)
{
    return ( @gmdate($format, $gmepoch + (3600 * $timezone)));
}
function filter_1($message) {
    //$message = str_replace("'", "&#8217;", $message);
    $message = str_replace("&", "&amp;", $message);
    //$message = str_replace("\"", "&quot;", $message);
}

function viewsmile($message) {
//    $message = preg_replace('#(script|about|applet|activex|chrome):#is', "\\1&#058;", $message);
    $message = str_replace(":)", "<img src=\"images/smilies/icon_smile.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":cry:", "<img src=\"images/smilies/icon_cry.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":(", "<img src=\"images/smilies/icon_sad.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":twisted:", "<img src=\"images/smilies/icon_twisted.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":D", "<img src=\"images/smilies/icon_biggrin.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":o", "<img src=\"images/smilies/icon_surprised.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":shock:", "<img src=\"images/smilies/icon_eek.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":?", "<img src=\"images/smilies/icon_confused.gif\" alt=\"\"></img>", $message);
    $message = str_replace("8)", "<img src=\"images/smilies/icon_cool.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":p", "<img src=\"images/smilies/icon_razz.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":P", "<img src=\"images/smilies/icon_razz.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":lol:", "<img src=\"images/smilies/icon_lol.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":x", "<img src=\"images/smilies/icon_mad.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":redface:", "<img src=\"images/smilies/icon_redface.gif\" alt=\"\"></img>", $message);
    $message = str_replace(";)", "<img src=\"images/smilies/icon_wink.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":wink:", "<img src=\"images/smilies/icon_wink.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":roll:", "<img src=\"images/smilies/icon_rolleyes.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":!:", "<img src=\"images/smilies/icon_exclaim.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":?:", "<img src=\"images/smilies/icon_question.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":idea:", "<img src=\"images/smilies/icon_idea.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":arrow:", "<img src=\"images/smilies/icon_arrow.gif\" alt=\"\"></img>", $message);
    $message = str_replace(":evil:", "<img src=\"images/smilies/icon_evil.gif\" alt=\"\"></img>", $message);

    return($message);
}

function viewbbcode($message) {
    $uid = md5(mt_rand());
    $uid = substr($uid, 0, 10);

    $message = preg_replace('#(script|about|applet|activex|chrome):#is', "\\1&#058;", $message);
    $message = " " . $message;
      if (! (strpos($message, "[") && strpos($message, "]")) )
  {
    // Remove padding, return.
    $message = substr($message, 1);
    return $message;
  }

    //$uid = "";
    //$message = str_replace("[br]", "<br />", $message);
    $message = str_replace("[u]", "<u>", $message);
    $message = str_replace("[b]", "<b>", $message);
    $message = str_replace("[/u]", "</u>", $message);
    $message = str_replace("[/b]", "</b>", $message);
    $message = str_replace("[i]", "<i>", $message);
    $message = str_replace("[/i]", "</i>", $message);
    $message = str_replace("[quote]", "<center><div class=\"codequotetitle\"><b>Quote</b> : <div class=\"quote\">", $message);
    $message = str_replace("[/quote]", "</div ></div></center>", $message);
    $message = str_replace("[code]", "<center><div class=\"codequotetitle\"><b>Code</b> : <div class=\"code\">", $message);
    $message = str_replace("[/code]", "</div ></div></center>", $message);

    // [list] and [list=x] for (un)ordered lists.
    $open_tag = array();
    $open_tag[0] = "[list]";

    // unordered..
    $message = bbencode_first_pass_pda($message, $uid, $open_tag, "[/list]", "[/list:u]", false, 'replace_listitems');

    $open_tag[0] = "[list=1]";
    $open_tag[1] = "[list=a]";

    // ordered.
    $message = bbencode_first_pass_pda($message, $uid, $open_tag, "[/list]", "[/list:o]",  false, 'replace_listitems');
    //echo $message;
    $bbcode_ol['olist_open'] = '<ol type="{LIST_TYPE}">';
    $bbcode_ol['olist_open'] = str_replace('{LIST_TYPE}', '\\1', $bbcode_ol['olist_open']);

    $message = preg_replace("/\[list=([a1]):$uid\]/si", $bbcode_ol['olist_open'], $message);
    $message = str_replace("[list:$uid]", "<ul>", $message);

    // li tags
    $message = str_replace("[*:$uid]", "<li>", $message);
    //echo $message ;
    //$message = str_replace("[*]", "<li>", $message);
    // ending tags
    //$message = str_replace("[/*]", "</li>", $message);
    $message = str_replace("[/list:u:$uid]", "</ul>", $message);
    $message = str_replace("[/list:o:$uid]", "</ol>", $message);
    return  substr($message, 1); ;
}

function autolink($message)
{
    $text = " " . $message;
    $text = preg_replace("#([\n ])([a-z]+?)://([a-z0-9\-\.,\?!%\*_\#:;~\\&$@\/=\+]+)#i", "\\1<a class='postlink' href=\"\\2://\\3\" target=\"_blank\">\\2://\\3</a>", $text);
    $text = preg_replace("#([\n ])www\.([a-z0-9\-]+)\.([a-z0-9\-.\~]+)((?:/[a-z0-9\-\.,\?!%\*_\#:;~\\&$@\/=\+]*)?)#i", "\\1<a class='postlink' href=\"http://www.\\2.\\3\\4\" target=\"_blank\">www.\\2.\\3\\4</a>", $text);
    $text = preg_replace("#([\n ])([a-z0-9\-_.]+?)@([\w\-]+\.([\w\-\.]+\.)?[\w]+)#i", "\\1<a href=\"mailto:\\2@\\3\">\\2@\\3</a>", $text);
    $text = substr($text, 1);
    return($text);
}

function viewlink($message) {

  $urltpl['url']='<a target="_blank" class="postlink" href="{URL}">{DESCRIPTION}</a>';
  $urltpl['url1'] = str_replace('{URL}', '\\1', $urltpl['url']);
  $urltpl['url1'] = str_replace('{DESCRIPTION}', '\\1', $urltpl['url1']);

  $urltpl['url2'] = str_replace('{URL}', 'http://\\1', $urltpl['url']);
  $urltpl['url2'] = str_replace('{DESCRIPTION}', '\\1', $urltpl['url2']);

  $urltpl['url3'] = str_replace('{URL}', '\\1', $urltpl['url']);
  $urltpl['url3'] = str_replace('{DESCRIPTION}', '\\2', $urltpl['url3']);

  $urltpl['url4'] = str_replace('{URL}', 'http://\\1', $urltpl['url']);
  $urltpl['url4'] = str_replace('{DESCRIPTION}', '\\3', $urltpl['url4']);



    $bbcode_tpl['img']= '<div><img src="{URL}" border="0" /></div>';
    $bbcode_tpl['img'] = str_replace('{URL}', '\\1', $bbcode_tpl['img']);

    $bbcode_tpl['imgr']= '<table cellspacing="0" cellpadding="5" align="right"><tr><td><img src="{URL}" border="0" /></td></tr></table>';
    $bbcode_tpl['imgr'] = str_replace('{URL}', '\\1', $bbcode_tpl['imgr']);

    $bbcode_tpl['imgl']= '<table cellspacing="0" cellpadding="5" align="left"><tr><td><img src="{URL}" border="0" /></td></tr></table>';
    $bbcode_tpl['imgl'] = str_replace('{URL}', '\\1', $bbcode_tpl['imgl']);

    $pattern[] = "#\[url\]([\w]+?://[^ \"\n\r\t<]*?)\[/url\]#is";
    $replacement[] = $urltpl['url1'];

    $pattern[] = "#\[url\]((www|ftp)\.[^ \"\n\r\t<]*?)\[/url\]#is";
    $replacement[] = $urltpl['url2'];


    $pattern[] = "#\[url=([\w]+?://[^ \"\n\r\t<]*?)\]([^?].*?)\[/url\]#i";
    $replacement[] = $urltpl['url3'];

    $pattern[] = "#\[url=((www|ftp)\.[^ \"\n\r\t<]*?)\]([^?].*?)\[/url\]#i";
    $replacement[] = $urltpl['url4'];

    $pattern[] = "#\[img](.*?)\[/img]#si";
    $replacement[] = $bbcode_tpl['img'];

    $pattern[] = "#\[imgr](.*?)\[/imgr]#si";
    $replacement[] = $bbcode_tpl['imgr'];

    $pattern[] = "#\[imgl](.*?)\[/imgl]#si";
    $replacement[] = $bbcode_tpl['imgl'];

    $message = preg_replace($pattern, $replacement, $message);
    return($message);

    }
/**
 * $text - The text to operate on.
 * $uid - The UID to add to matching tags.
 * $open_tag - The opening tag to match. Can be an array of opening tags.
 * $close_tag - The closing tag to match.
 * $close_tag_new - The closing tag to replace with.
 * $mark_lowest_level - boolean - should we specially mark the tags that occur
 *                     at the lowest level of nesting? (useful for [code], because
 *                        we need to match these tags first and transform HTML tags
 *                        in their contents..
 * $func - This variable should contain a string that is the name of a function.
 *                That function will be called when a match is found, and passed 2
 *                parameters: ($text, $uid). The function should return a string.
 *                This is used when some transformation needs to be applied to the
 *                text INSIDE a pair of matching tags. If this variable is FALSE or the
 *                empty string, it will not be executed.
 * If open_tag is an array, then the pda will try to match pairs consisting of
 * any element of open_tag followed by close_tag. This allows us to match things
 * like [list=A]...[/list] and [list=1]...[/list] in one pass of the PDA.
 *
 * NOTES:    - this function assumes the first character of $text is a space.
 *                - every opening tag and closing tag must be of the [...] format.
 */
function bbencode_first_pass_pda($text, $uid, $open_tag, $close_tag, $close_tag_new, $mark_lowest_level, $func, $open_regexp_replace = false)
{
    $open_tag_count = 0;

    if (!$close_tag_new || ($close_tag_new == ''))
    {
        $close_tag_new = $close_tag;
    }

    $close_tag_length = strlen($close_tag);
    $close_tag_new_length = strlen($close_tag_new);
    $uid_length = strlen($uid);

    $use_function_pointer = ($func && ($func != ''));

    $stack = array();

    if (is_array($open_tag))
    {
        if (0 == count($open_tag))
        {
            // No opening tags to match, so return.
            return $text;
        }
        $open_tag_count = count($open_tag);
    }
    else
    {
        // only one opening tag. make it into a 1-element array.
        $open_tag_temp = $open_tag;
        $open_tag = array();
        $open_tag[0] = $open_tag_temp;
        $open_tag_count = 1;
    }

    $open_is_regexp = false;

    if ($open_regexp_replace)
    {
        $open_is_regexp = true;
        if (!is_array($open_regexp_replace))
        {
            $open_regexp_temp = $open_regexp_replace;
            $open_regexp_replace = array();
            $open_regexp_replace[0] = $open_regexp_temp;
        }
    }

    if ($mark_lowest_level && $open_is_regexp)
    {
        error("ERROR", "Unsupported operation for bbcode_first_pass_pda().");
    }

    // Start at the 2nd char of the string, looking for opening tags.
    $curr_pos = 1;
    while ($curr_pos && ($curr_pos < strlen($text)))
    {
        $curr_pos = strpos($text, "[", $curr_pos);

        // If not found, $curr_pos will be 0, and the loop will end.
        if ($curr_pos)
        {
            // We found a [. It starts at $curr_pos.
            // check if it's a starting or ending tag.
            $found_start = false;
            $which_start_tag = "";
            $start_tag_index = -1;

            for ($i = 0; $i < $open_tag_count; $i++)
            {
                // Grab everything until the first "]"...
                $possible_start = substr($text, $curr_pos, strpos($text, ']', $curr_pos + 1) - $curr_pos + 1);

                //
                // We're going to try and catch usernames with "[' characters.
                //
                if( preg_match('#\[quote=\\\"#si', $possible_start, $match) && !preg_match('#\[quote=\\\"(.*?)\\\"\]#si', $possible_start) )
                {
                    // OK we are in a quote tag that probably contains a ] bracket.
                    // Grab a bit more of the string to hopefully get all of it..
                    if ($close_pos = strpos($text, '"]', $curr_pos + 9))
                    {
                        if (strpos(substr($text, $curr_pos + 9, $close_pos - ($curr_pos + 9)), '[quote') === false)
                        {
                            $possible_start = substr($text, $curr_pos, $close_pos - $curr_pos + 2);
                        }
                    }
                }

                // Now compare, either using regexp or not.
                if ($open_is_regexp)
                {
                    $match_result = array();
                    if (preg_match($open_tag[$i], $possible_start, $match_result))
                    {
                        $found_start = true;
                        $which_start_tag = $match_result[0];
                        $start_tag_index = $i;
                        break;
                    }
                }
                else
                {
                    // straightforward string comparison.
                    if (0 == strcasecmp($open_tag[$i], $possible_start))
                    {
                        $found_start = true;
                        $which_start_tag = $open_tag[$i];
                        $start_tag_index = $i;
                        break;
                    }
                }
            }

            if ($found_start)
            {
                // We have an opening tag.
                // Push its position, the text we matched, and its index in the open_tag array on to the stack, and then keep going to the right.

                $match = array("pos" => $curr_pos, "tag" => $which_start_tag, "index" => $start_tag_index);
                bbcode_array_push($stack, $match);
                //
                // Rather than just increment $curr_pos
                // Set it to the ending of the tag we just found
                // Keeps error in nested tag from breaking out
                // of table structure..
                //
                $curr_pos += strlen($possible_start);
            }
            else
            {
                // check for a closing tag..
                $possible_end = substr($text, $curr_pos, $close_tag_length);
                if (0 == strcasecmp($close_tag, $possible_end))
                {
                    // We have an ending tag.
                    // Check if we've already found a matching starting tag.
                    if (sizeof($stack) > 0)
                    {
                        // There exists a starting tag.
                        $curr_nesting_depth = sizeof($stack);

                        // We need to do 2 replacements now.
                        $match = bbcode_array_pop($stack);
                        $start_index = $match['pos'];
                        $start_tag = $match['tag'];
                        $start_length = strlen($start_tag);
                        $start_tag_index = $match['index'];

                        if ($open_is_regexp)
                        {
                            $start_tag = preg_replace($open_tag[$start_tag_index], $open_regexp_replace[$start_tag_index], $start_tag);
                        }

                        // everything before the opening tag.
                        $before_start_tag = substr($text, 0, $start_index);

                        // everything after the opening tag, but before the closing tag.
                        $between_tags = substr($text, $start_index + $start_length, $curr_pos - $start_index - $start_length);

                        // Run the given function on the text between the tags..
                        if ($use_function_pointer)
                        {
                            $between_tags = $func($between_tags, $uid);
                        }

                        // everything after the closing tag.
                        $after_end_tag = substr($text, $curr_pos + $close_tag_length);

                        // Mark the lowest nesting level if needed.
                        if ($mark_lowest_level && ($curr_nesting_depth == 1))
                        {
                            if ($open_tag[0] == '[code]')
                            {
                                $code_entities_match = array('#<#', '#>#', '#"#', '#:#', '#\[#', '#\]#', '#\(#', '#\)#', '#\{#', '#\}#');
                                $code_entities_replace = array('&lt;', '&gt;', '&quot;', '&#58;', '&#91;', '&#93;', '&#40;', '&#41;', '&#123;', '&#125;');
                                $between_tags = preg_replace($code_entities_match, $code_entities_replace, $between_tags);
                            }
                            $text = $before_start_tag . substr($start_tag, 0, $start_length - 1) . ":$curr_nesting_depth:$uid]";
                            $text .= $between_tags . substr($close_tag_new, 0, $close_tag_new_length - 1) . ":$curr_nesting_depth:$uid]";
                        }
                        else
                        {
                            if ($open_tag[0] == '[code]')
                            {
                                $text = $before_start_tag . '&#91;code&#93;';
                                $text .= $between_tags . '&#91;/code&#93;';
                            }
                            else
                            {
                                if ($open_is_regexp)
                                {
                                    $text = $before_start_tag . $start_tag;
                                }
                                else
                                {
                                    $text = $before_start_tag . substr($start_tag, 0, $start_length - 1) . ":$uid]";
                                }
                                $text .= $between_tags . substr($close_tag_new, 0, $close_tag_new_length - 1) . ":$uid]";
                            }
                        }

                        $text .= $after_end_tag;

                        // Now.. we've screwed up the indices by changing the length of the string.
                        // So, if there's anything in the stack, we want to resume searching just after it.
                        // otherwise, we go back to the start.

                        if (sizeof($stack) > 0)
                        {
                            $match = bbcode_array_pop($stack);
                            $curr_pos = $match['pos'];
//                            bbcode_array_push($stack, $match);
//                            ++$curr_pos;
                        }
                        else
                        {
                            $curr_pos = 1;
                        }
                    }
                    else
                    {
                        // No matching start tag found. Increment pos, keep going.
                        ++$curr_pos;
                    }
                }
                else
                {
                    // No starting tag or ending tag.. Increment pos, keep looping.,
                    ++$curr_pos;
                }
            }
        }
    } // while

    return $text;

} // bbencode_first_pass_pda()

function bbcode_array_pop(&$stack)
{
   $arrSize = count($stack);
   $x = 1;
      //print_r($stack);
      //echo $arrSize;
   foreach ($stack as $key => $val)
   {
      if($x < count($stack))
      {
             $tmpArr[] = $val;
      }
      else
      {
             $return_val = $val;
      }
      $x++;
   }
   if (isset($tmpArr)) $stack = $tmpArr;
   else  $stack =array();
   return($return_val);
}

function bbcode_array_push(&$stack, $value)
{
   $stack[] = $value;
   return(sizeof($stack));
}

function replace_listitems($message, $uid)
{
    $message = str_replace("[*]", "[*:$uid]", $message);

    return $message;
}



function pagelink($mode, $pageno, $limit, $numrows) {
  if (!isset($pagestring)) { $pagestring = "";}
  $pages = intval($numrows/$limit);
  if ($numrows%$limit) { $pages++;}
  $current = ($pageno/$limit) + 1;
  if (($pages < 1) || ($pages == 0)) { $total = 1;}
  else { $total = $pages;}
  $first = $pageno + 1;
  if (!((($pageno + $limit) / $limit) >= $pages) && $pages != 1)
    {
     $last = $pageno + $limit;
     }
    else
    {
     $last = $numrows;
    }
    //echo  $total ;
    //echo  $pages ;
    $notprinted = true;
  if ($pageno != 0)
    {

     $back_page = $pageno - $limit;
     $pagestring .= "<a class=page href=".$_SERVER['PHP_SELF']."?mode=$mode&pageno=$back_page&limit=$limit>Prev</a> " ;
     }
   for ($i=1; $i <= $pages; $i++)
     {
     $ppage = $limit*($i - 1);
     if ($ppage == $pageno)     { //echo $ppage;

     $pagestring .= "<font class=currentpage><b>$i </b></font>";
     $nextpage = $i + 1;
     }
    elseif ($pages - 3 < $i || $i < 4 || $i == $nextpage){
    // else{
    $pagestring .= "<a class=page href=".$_SERVER['PHP_SELF']."?mode=$mode&pageno=$ppage&limit=$limit>$i</a> ";
     }

     else {
     if ($notprinted) {
     $pagestring .= "...";
     $notprinted = false;
       }
       }
 //    echo ($ppage)."<br />";
   }

   if (!((($pageno+$limit) / $limit) >= $pages) && $pages != 1) { // If last page don't give next link.
    $next_page = $pageno + $limit;
    $pagestring .= "<a class=page href=".$_SERVER['PHP_SELF']."?mode=$mode&pageno=$next_page&limit=$limit>Next</a>";
    }
   $notprinted = true;
return $pagestring;
}


//
// Append $SID to a url. Borrowed from phplib and modified. This is an
// extra routine utilised by the session code above and acts as a wrapper
// around every single URL and form action. If you replace the session
// code you must include this routine, even if it's empty.
//
function append_sid($url, $non_html_amp = false)
{
    global $SID;

    if ( !empty($SID) && !preg_match('#sid=#', $url) )
    {
        $url .= ( ( strpos($url, '?') != false ) ?  ( ( $non_html_amp ) ? '&' : '&amp;' ) : '?' ) . $SID;
    }

    return $url;
}
function error( $alert, $message )
    { global $mybloggie_root_path;
      ?>
     <table width="98%"  height="300" cellspacing="0" cellpadding="0"  border="0">
     <tr><td valign="middle">
     <table width="100%" class="tableborder" cellspacing="1" cellpadding="2"  border="0">
    <tr>
     <td class="tdhead" bgcolor="#6699ff"><center><? echo $alert  ?></center></td></tr>
    <tr>
     <td class="error" valign="middle">
      <center><br /><? echo $message  ?><br /><br /></center>
     </td></tr><tr>
     <td class="error" align="center"><a class="std" href="index.php">myBloggie Home</a>  | <a class="std" href="javascript:history.back()">Back</a></td>
     </tr>
     </table>
     </td></tr>
     </table>
   <?
   $template = new Template('./templates/') ;
   $template->set_filenames(array(
              'footer' => $mybloggie_root_path.'footer.tpl' ));
   $template->pparse('footer');
   exit;
    }

function message( $alert, $message )
    { ?>
     <table width="98%"  height="300" cellspacing="0" cellpadding="0"  border="0">
     <tr><td valign="middle">
     <table width="100%" class="tableborder" cellspacing="1" cellpadding="2"  border="0">
    <tr>
     <td class="tdhead" bgcolor="#6699ff"><center><? echo $alert  ?></center></td></tr>
    <tr>
     <td class="error" valign="middle">
      <center><br /><? echo $message  ?><br /><br /></center>
     </td></tr><tr>
     <td class="error" align="center"><a class="std" href="index.php">myBloggie Home</a>  | <a class="std" href="javascript:history.back()">Back</a></td>
     </tr>
     </table>
     </td></tr>
     </table>
   <?
    }

function chop_text($posttext, $minimum_length, $length_offset) {
   // The approximate length you want the concatenated text to be
   //$minimum_length = 260;
   // The variation in how long the text can be
   // in this example text length will be between 200-10=190 characters
   // and the character where the last tag ends
   //$length_offset = 10;
   // Reset tag counter & quote checker
   $tag_counter = 0;
   $quotes_on = FALSE;
   // Check if the text is too long
   if (strlen($posttext) > $minimum_length) {
       // Reset the tag_counter and pass through (part of) the entire text
       for ($i = 0; $i < strlen($posttext); $i++) {
           // Load the current character and the next one
           // if the string has not arrived at the last character
           $current_char = substr($posttext,$i,1);
           if ($i < strlen($posttext) - 1) {
               $next_char = substr($posttext,$i + 1,1);
           }
           else {
               $next_char = "";
           }
           // First check if quotes are on
           if (!$quotes_on) {
               // Check if it's a tag
               // On a "<" add 3 if it's an opening tag (like <a href...)
               // or add only 1 if it's an ending tag (like </a>)
               if ($current_char == "<") {
                   if ($next_char == "/") {
                                       $tag_counter++;
                   }
                   else {
                       $tag_counter = $tag_counter + 3;
                   }
               }
               // Slash signifies an ending (like </a> or ... />)
               // substract 2
               if ($current_char == "/") $tag_counter = $tag_counter - 2;
               // On a ">" substract 1
               if ($current_char == ">") $tag_counter--;
               // If quotes are encountered, start ignoring the tags
               // (for directory slashes)
               if ($current_char == "\"") $quotes_on = TRUE;
           }
           else {
               // IF quotes are encountered again, turn it back off
               if ($current_char == "\"") $quotes_on = FALSE;
           }

                           
           // Check if the counter has reached the minimum length yet,
           // then wait for the tag_counter to become 0, and chop the string there
           if ($i > $minimum_length - $length_offset && $tag_counter == 0) {
              // Ensure complete word is display & not partial... search for space
              $nospace = true;
              while ( $nospace ) {
              if ( substr($posttext,$i,1) != " ")
               {   $i++;
               }
               else {  $nospace = false; }
              }
               if ( substr($posttext,$i+1,1) == "/") {   $i=$i+2;   }
               $posttext = substr($posttext,0,$i + 1) . "...";
               return $posttext;
           }
       }
   }
             return $posttext;
}

function highlight($text,$keywords) {

      $regex = '#(?!<.*?)(%s)(?![^<>]*?>)#si';
      $colors = array('FFF000','FF0000','FFFF00','0000FF','000FFF'  ,'00FF00','00FFF0','0FFF00');
      $i=0;
      // surround search item items with highlight class
      foreach($keywords as $needle){
          if ($i>count($colors)-1) {
              $i=0;
           }
           $start_tag = "<span style=\"background:#" . $colors[$i] . "\">";
           $end_tag = "</span>";
           $pattern =  sprintf($regex, $needle);
           $replacement = $start_tag . '\1' . $end_tag;
           $text = preg_replace($pattern, $replacement, $text);
           $i++;
      }
      return $text;
}
function self_url( $display=0 ) {

if  (isset($_SERVER['PHP_SELF']) && isset($_SERVER['HTTP_HOST'])) {
   $me = $_SERVER['PHP_SELF'];
   $Apathweb = explode("/", $me);
$myFileName = array_pop($Apathweb);
   $pathweb = implode("/", $Apathweb);
   $myUrl = "http://".$_SERVER['HTTP_HOST'].$pathweb;
   }
elseif (isset($_SERVER['PHP_SELF']) && isset($_SERVER['SERVER_NAME'])) {
   $me = $_SERVER['PHP_SELF'];
   $Apathweb = explode("/", $me);
   $pathweb = implode("/", $Apathweb);
   $myUrl = 'http://'.$_SERVER['SERVER_NAME'].$pathweb;
   }
   //echo $pathweb;
   //echo $Apathweb[0];
 if ($display) {
        echo $myUrl;
    } else {
        return $myUrl;
    }
}


function tb_rdf($post_id, $title) {
$tb_rdf = "
<!--
  <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"
    xmlns:dc=\"http://purl.org/dc/elements/1.1/\"
    xmlns:trackback=\"http://madskills.com/public/xml/rss/module/trackback/\">
    <rdf:Description rdf:about=\"".self_url()."/index.php?mode=viewid&amp;post_id=".$post_id."\"
    dc:identifier=\"".self_url()."/index.php?mode=viewid&amp;post_id=".$post_id."\"
    dc:title=\"".$title."\"
    trackback:ping=\"".self_url()."/trackback.php/".$post_id."\" />
</rdf:RDF>  -->" ;
return $tb_rdf;
}

function gen_permalink($post_id) {
$permalink = self_url()."/index.php?mode=viewid&amp;post_id=".$post_id ;
return $permalink;
}

function validate_url($url) {
if  ( ! preg_match('#^http\\:\\/\\/[a-z0-9\-]+\.([a-z0-9\-]+\.)?[a-z]+#i', $url, $matches) ) {
       return false ;}
       else {
     return true;  }
} 
?>
