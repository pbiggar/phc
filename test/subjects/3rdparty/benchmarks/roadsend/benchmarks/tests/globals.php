This test bangs on the globals.  Courtesy of BDKR.
<?php
# Another test of the GLOBALS var
set_time_limit(0);
$time_start=0;
$GLOBALS[0]=0;
$GLOBALS['Y']=0;
$numbered[0]=0;
$x=0;
$k=0;

// print_r($GLOBALS);
// exit;


echo "Now starting the benchmark.\n";
while($GLOBALS[0]<1000000)
	{ ++$GLOBALS[0]; }
unset($GLOBALS[0]);


while($GLOBALS['Y']<1000000)
	{ ++$GLOBALS['Y']; }

while($numbered[0]<1000000)
	{ ++$numbered[0]; }

while($x<1000000)
	{ ++$x; }


increment_global_k();
increment_k2($k);
// echo "\$k = $k\n";



function increment_global_k()
	{ 
	while($GLOBALS['k']<1000000)
		{ ++$GLOBALS['k']; }
	$GLOBALS['k']='';
	}

function increment_k2(&$var)
	{ 
	echo "\$k = \"".$var."\"\n";
	$var=0;
	while($var<1000000)
		{ ++$var; }
	}


?>
