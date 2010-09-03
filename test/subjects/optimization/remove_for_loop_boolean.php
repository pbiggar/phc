<?php

	// { phc-option: -O1 --dump=codegen }
	// { phc-regex-output: !/true/ }
	// { phc-regex-output: !/false/ }


	/*for ($i = 0; $i < 100; $i++)
	{
		echo "$i\n";
	}

	for ($j = 0; $j < 100 && $j >= 0; $j++)
	{
		echo "$j\n";
	}
*/
	// nested loop
	for ($k = 0; $k < 100; $k++)
	{
		for ($l = 0; $l < 50; $l++)
		{
			$sum = $sum + $l;
		}
	}
	echo $sum;

	/*// The branch block has 3 entry points.
	for ($y=0 ; $y<=$w1; $y=$y+1) {
      if ( $y==5 ) {
        print "_";
      } else {
        print "#";
      }
  }*/


?>
