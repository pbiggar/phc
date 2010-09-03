<?php

	// The $TEMP = 1 from $n+1 should be DCEd.

	// { phc-option: -O3 --dump=codegen } 
	// { phc-regex-output: !/= 1/ }


	function Ack($m, $n){
	  if($m == 0) return $n+1;
	}

  $r = Ack(3,3);
  print "Ack(3,$n): $r\n";

?>
