<?php
	// All these constructs get unparsed differently depending on whether the
	// --next-line-curlies option is used

	if($x)
		echo "hi";
	else
		echo "bye";

	if($x)
		echo "hi";
	elseif($y)
		echo "ho";
	else
		echo "bo";

	while($c)
		echo "do something";

	do
		echo "do something else";
	while($c);

	for($a; $b; $c)
		echo $d;

	foreach(array () as $key => $val)
		echo "booh";

	switch($a)
	{
		case 1:
			break;
		case 2:
			break;
		default:
			break;
	}

	try
	{
		echo "do something that could fail";
	}
	catch(FirstException $e)
	{
		echo "deal with the failure";
	}
	catch(SecondException $e)
	{
		echo "and again";
	}

	echo "final statement";
?>
