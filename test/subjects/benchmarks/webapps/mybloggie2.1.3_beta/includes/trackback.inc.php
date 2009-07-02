<?

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

?>