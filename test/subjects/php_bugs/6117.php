<? 

	// nothing to learn here

$test[123]="one hundred twenty three";
$test[13]="thirteen";
$test[0]="zero";
$test[3]="three";
$test[11]="eleven";

// try the for construct:
for(reset($test);$key=key($test);next($test)) {
        echo "TEST[$key]=".$test[$key]."<br>";

}

echo "************************************<br>";

// try the foreach construct
foreach($test as $key => $value) {
        echo "TEST[$key]=$value<br>";
}

/***** THE OUTPUT IS:

TEST[123]=one hundred twenty three
TEST[13]=thirteen
************************************
TEST[123]=one hundred twenty three
TEST[13]=thirteen
TEST[0]=zero
TEST[3]=three
TEST[11]=eleven

****/

?>
