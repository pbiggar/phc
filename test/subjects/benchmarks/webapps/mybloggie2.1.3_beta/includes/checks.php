<?

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


?>