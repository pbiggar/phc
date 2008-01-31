#!/usr/bin/perl -w
# See License.txt for copyright and terms of use

use warnings;
use strict;
use FindBin;
use lib "${FindBin::RealBin}";
use BuildInterceptor ':all';

# Intercepts f771 to add a dummy .note.f771_interceptor, for now just so that
# the assembler interceptor knows this is coming from Fortran.

my $outfile = get_output_filename() || 'a.out';

run_prog($prog, $argv);
check_output_file($outfile);

# append metadata to output
my $metadata = <<'END'                              # do not interpolate
        .section        .note.f771_interceptor,"",@progbits
        .ascii "dummy\n"
END
    ;

append_to_file($outfile, $metadata);
