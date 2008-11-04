<? /* The Great Computer Language Shootout
      contributed by Isaac Gouy 

      php -q wc.php < in.txt 
*/ 

// called with 1000-2500 works from wc/Input


$nl = $nw = $nc = 0;
$hasSplitWord = FALSE;

$fp = fopen("php://stdin", "r");
while ($block = fread($fp, 4096)){

   $nc += strlen($block);

   $pos = 0;
   while ($pos = strpos($block,"\n", $pos+1)) $nl++;


   $words = preg_split('/\s+/', $block);

   if ($size = sizeof($words)){
      $nw += $size;                 // count all the splits as words 
                                    // and then correct for empty words
      if (strlen($words[0])){          
         if ($hasSplitWord) $nw--;  // we counted the split-word twice
      } else {
         $nw--;                     // there was no first word
      }
      $hasSplitWord = strlen($words[$size-1]);
      if (!$hasSplitWord) $nw--;    // there was no last word
   }

   unset($words);
}
fclose($fp);

print "$nl $nw $nc\n";

?>
