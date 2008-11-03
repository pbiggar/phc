<?php
/*
 $Id: wc.php,v 1.2 2004/02/16 15:11:12 tim Exp $
 http://www.bagley.org/~doug/shootout/
 
 TBD - this program should not assume lines are less than 10000 characters long
*/

wc();

function wc() {
  $datafile = "test/subjects/3rdparty/benchmarks/roadsend/benchmarks/data/spellcheck";

  if(!file_exists($datafile)) {
    trigger_error("Couldn't find datafile $datafile.", E_USER_ERROR);
  }

  $fd = fopen($datafile, "r");
  $nl = $nw = $nc = 0;
  while (!feof ($fd)) {
      if ($line = fgets($fd, 10000)) {
	  ++$nl;
          $nc += strlen($line);
          $nw += count(preg_split("/\s+/", $line, -1, PREG_SPLIT_NO_EMPTY));
      }
  }
  fclose($fd);
  print "$nl $nw $nc\n";
}

?>
