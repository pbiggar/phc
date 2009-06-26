<?
//
// emulates the parsing of sitemanager templates 
//


define('SM_TAG_IDENTIFIER','SM'); // if you want something other than <SM> tags, change this
define('SM_TAG_PREGEXP','/<\s*'.SM_TAG_IDENTIFIER.'\s(.+)\s*>/Ui');
define('SM_TAG_ATTR_PREGEXP','/(\w+)\s*=\s*[\"\'](.+)[\"\']/SUi');

function test() {
  $htmlTemplate = file("data/pcre-data.xml");

  // for each line in the file...
  foreach ($htmlTemplate as $line) {
    
    // use this to determine what kind of tag we're dealing with
    $tagType = '';
    $areaSub = '';
    
    // check for standard SM tags
    if (preg_match_all(SM_TAG_PREGEXP,$line,$smTagMatch)) {
                
      // for each match we found on this line...
      for ($i=0; $i < sizeof($smTagMatch[1]); $i++) {
                    
	// grab TYPE parameter
	$smParms = $smTagMatch[1][$i];
	// parse the attributes
	//   this screws with the type inference
	unset($attrs);
	//   this should be friendlier
//	$attrs = array();
	preg_match_all(SM_TAG_ATTR_PREGEXP,$smParms,$matchList);
	for ($x = 0; $x<count($matchList[1]); $x++) {
	  $key = strtoupper($matchList[1][$x]);
	  $attrs[$key] = $matchList[2][$x];
	}

      }
            
    } // end of main tag block
  }
}

for ($i=0; $i<100; $i++) {
  test();
}

    
?>
