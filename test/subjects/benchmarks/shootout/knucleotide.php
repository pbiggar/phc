<?php
/* The Computer Language Shootout
   http://shootout.alioth.debian.org/
 
   contributed by Damien Bonvillain
*/

/*
	--range 2500,25000,250000 \
  --inputfile ../../website/desc/knucleotide-input.txt \
  --uniqueinput
*/


$sequence = read_sequence('THREE');

fclose(STDIN);

// sequence read, let's write some stats
write_freq($sequence, 1);
write_freq($sequence, 2);
write_count($sequence, 'GGT');
write_count($sequence, 'GGTA');
write_count($sequence, 'GGTATT');
write_count($sequence, 'GGTATTTTAATT');
write_count($sequence, 'GGTATTTTAATTTATAGT');

/* functions definitions follow */

function read_sequence($id) {
  $ln_id = strlen($id);
  // reach sequence three
  while(!feof(STDIN)) {
    $line = fgets(STDIN, 255);
    if($line[0] == '>' && substr($line, 1, $ln_id) == $id) {
      break;
    }
  }
  if(feof(STDIN)) {
    // sequence not found
    exit(-1);
  }
  // next, read the content of the sequence
  $sequence = '';
  while(!feof(STDIN)) {
    $line = fgets(STDIN, 100);
    switch($line[0]) {
    case ';':
      // comment, continue
      continue;
    case '>':
      // next sequence starts, this one is finished
      break 2;
    default:
      // append the uppercase sequence fragment,
      // must get rid of the CR/LF or whatever if present
      $sequence .= strtoupper(rtrim($line));
    }
  }
  return $sequence;
}

function write_freq(&$sequence, $key_length) {
  $map = generate_frequencies($sequence, $key_length);
  sort_by_freq_and_name($map);
  foreach($map as $key => $val) {
    printf ("%s %.3f\n", $key, $val);
  }
  echo "\n";
}

function write_count(&$sequence, $key) {
  $map = generate_frequencies($sequence, strlen($key), false);
  printf ("%d\t%s\n", (array_key_exists($key, &$map))?$map[$key]:0, $key);
}

/**
 * Returns a map (key, count or freq(default))
 */
function generate_frequencies(&$sequence, $key_length, $compute_freq = true) {
  $result = array();
  $total = strlen(&$sequence) - $key_length + 1;
  $i = $total;
  while(--$i >= 0) {
    // highly inefficient, alas, no real choice
    $key = substr(&$sequence, $i, $key_length);
    if(!array_key_exists($key,&$result)) $result[$key] = 0;
    $result[$key]++;
  }
  if($compute_freq) {
    array_walk($result, 'compute_freq', $total);
  }
  return $result;
}

function compute_freq(&$count_freq, $key, $total) {
  $count_freq = ($count_freq* 100) / $total;
}

function sort_by_freq_and_name(&$map) {
  // since PHP 4.1.0, sorting is not stable => dirty kludge
  array_walk($map, 'append_key');
  uasort($map, 'freq_name_comparator');
  array_walk($map, 'remove_key');
}

function append_key(&$val, $key) {
  $val = array($val, $key);
}

function freq_name_comparator($val1, $val2) {
  $delta = $val2[0] - $val1[0];
  // the comparator must return something close to an int
  $result = ($delta == 0)?strcmp($val1[1],$val2[1]):
    ($delta < 0)?-1:1;
  return $result;
}

function remove_key(&$val, $key) {
  $val = $val[0];
}
?>
