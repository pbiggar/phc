<?php
/*
 $Id: spellcheck.php,v 1.1 2004/02/16 14:35:19 tim Exp $
 http://www.bagley.org/~doug/shootout/
*/

//(with some modifications by tim)
//the data is from /usr/dict/words

function spellcheck() {
  $datafile = "test/subjects/3rdparty/benchmarks/roadsend/benchmarks/data/spellcheck";

  if(!file_exists($datafile)) {
    trigger_error("Couldn't find datafile $datafile.", E_USER_ERROR);
  }

  $dict = array();
  $fd = fopen($datafile, "r");
  while (!feof ($fd)) { $dict[chop(fgets($fd, 1024))] = 1; }
  fclose($fd);
  
  $fd = fopen($datafile, "r");
  while (!feof ($fd)) {
    $word = chop(fgets($fd, 1024));
    if (! $dict[$word]) {
      print "$word\n";
    }
  }
  fclose($fd);
}

spellcheck();
?>
