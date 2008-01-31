#!/usr/bin/perl -w
# See License.txt for copyright and terms of use
use strict;
use warnings;
use FindBin;
use lib "${FindBin::RealBin}";
use BuildInterceptor ':all';

# When used as a replacement to the system cpp0 or tradcpp0 will just
# pass the arguments through.

# Get rid of any -P arguments.
@$argv = grep {!/^-P$/} @$argv;

intercept_prog();
