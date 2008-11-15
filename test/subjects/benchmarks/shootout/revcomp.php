<?php
#
# TheComputer Language Shootout
# http://shootout.alioth.debian.org/
#
# reverse complement in PHP
# contributed by Danny Sauer
#

/*
	  --range 25000,250000,2500000 \
	  --inputfile ../../website/desc/revcomp-input.txt \
	  --uniqueinput \
*/
	

# We'll need some definitions
define( 'LINE_LENGTH', 60 );
define( 'SRC', 'CGATMKRYVBHD');
define( 'DST', 'GCTAKMYRBVDH');
$str = '';
$seq = '';

# read in the file, a line at a time
while( !feof(STDIN) ) {
    $str = trim(fgets(STDIN));
    if( $str[0] == '>' ){
        # if we're on a comment line, print the previous seq and move on
        print_seq();
        echo $str, "\n";
    }else{
        # otherwise, just append to the sequence
        $seq .= $str;
    }
}
print_seq();

exit;

# print the sequence out, if it exists
function print_seq(){
    global $seq; # no time-consuming argument passing for us! :)
    if($seq != ''){
        echo wordwrap( strrev( strtr(strtoupper($seq), SRC, DST) ),
                       LINE_LENGTH, "\n", true ), "\n";
    }
    $seq = '';
}
?>
