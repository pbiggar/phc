#!/usr/bin/perl -w
# See License.txt for copyright and terms of use
use strict;
use FindBin;
use FindBin;
use lib "${FindBin::RealBin}";
use BuildInterceptor ':all';

sub strip_minus_j {
    # Remove the -j argument.  If we are going to replay the build process, I
    # want the order in which things are built to be as canonical as possible.
    my ($argv) = @_;
    my $output_argv = [];

    for (my $i=0; $i<@$argv; ++$i) {
        if ($argv->[$i] =~ /^-j/) {
            # skip the -j
            if ($argv->[$i] eq '-j') {
                if ($argv->[$i+1] =~ /^\d/) {
                    # Also skip the following argument.  GNU make considers
                    # this the argument to -j if it starts with a digit.
                    ++$i;
                }
            }
        } else {
            push(@$output_argv, $argv->[$i]);
        }
    }
    return $output_argv;
}

$argv = strip_minus_j($argv);

intercept_prog();           # delegate to the real thing
