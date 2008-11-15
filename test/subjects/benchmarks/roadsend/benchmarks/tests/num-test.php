<?

function foo() {
	for ($i = 0; $i < 1000000; $i++) {
		$j += $i * 2;
	}
	print "$j, $i\n";
}

foo();


?>