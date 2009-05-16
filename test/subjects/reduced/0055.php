<?

	// Reported by Viesturs Decens

	class class1
	{
		function myfunct($var1)
		{
			echo $var1;
		}
	}

	$ptr = new class1;
	$ptr->myfunct ("test1");
	$myarr [$key1]["key2"]="test2";
	$ptr->myfunct ($myarr [$key1]["key2"]);
?>
