#!/usr/bin/perl

# Pick a random sample of 1/Nth of the sessions analyzed during a clpa run

$usage = "USAGE: random-sample.pl frequency < input > output\n";
$frequency = shift or die $usage;

$line = <>;
while ($line) {
    if ($line =~ /^Entering / && rand($frequency) < 1) {
	print $line;
	while ($line = <>) {
	    if ($line =~ /^Entering /) {
		last;
	    }
	    else {
		print $line;
	    }
	}
    }
    else {
	$line = <>;
    }
}
