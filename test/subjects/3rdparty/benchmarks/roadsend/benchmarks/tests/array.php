<?

$NUMRECS = 100000;

$arr = array();

for ($i=0; $i < $NUMRECS; $i++) {
    $arr["a name $i"] = array($i,$i);
}

mt_srand(10);

for ($i=0, $max = $NUMRECS/2; $i < $max; $i++) {
    $n = 'a name '.mt_rand(0,$NUMRECS-1);
    $arr2 = $arr[$n];
    if (!$arr2) {
        print "Error searching for $n n";
    }
}

?>