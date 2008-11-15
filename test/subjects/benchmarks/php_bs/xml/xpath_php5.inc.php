<?

function bench2() 
{
global $XML;

	
	$dom = new domDocument;
	$dom->loadxml($XML);
	$xp = new domxpath($dom);
	$nodes = $xp->query("//title/text()");
	foreach ($nodes as $n) {
		$arr[] = $n->nodeValue;
	}
	return $arr;
	
	/*
	// simplexml syntax...
	$s = simplexml_load_string($XML);
	$nodes = $s->xpath("//title");
	foreach($nodes as $v) {
		$arr[] = reset($v);
	}
	return $arr;
	*/
}

?>