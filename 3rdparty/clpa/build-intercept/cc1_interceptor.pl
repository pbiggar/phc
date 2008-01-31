#!/usr/bin/perl -w
# See License.txt for copyright and terms of use

use strict;
use warnings;
use FindBin;
use lib "${FindBin::RealBin}";
use BuildInterceptor ':all';

use Cwd;
use File::Spec;
use File::Copy;
use FileHandle;
use FindBin;

# When used as a replacement to the system cc1 or cc1plus this script
# will intercept the build process and keep a copy of the .i files
# generated.

# If we being invoked as a preprocessor, just delegate to the real thing.
if (grep {/^-E$/} @$argv) {
    intercept_prog();
}

# Mapping from build filesystem to isomorphic copy.
my $prefix = $ENV{BUILD_INTERCEPTOR_PREPROC} || "${home_path}/preproc";

my $pwd = getcwd;

my $orig_filename = get_orig_filename();

# Input behavior:
# If you specify multiple input files, it just uses the last one.
# If there is no input file, it uses standard in.
#
# Assumptions:
# I assume any .i or .ii file is an input file and that no other files
# are input files.
# If you give as an input file '-' then it will make a file -.s as the
# output file!  I don't reproduce this behavior.

my ($infile, $input, $tname) = get_input_and_tname();
my $rel_tmpfile = "." . uniquify_filename($tname);
my $tmpfile = "$prefix/$rel_tmpfile";
# put the contents there
copy_file($input, $tmpfile);

my $md5 = md5_file($tmpfile);

unshift @$argv, $tmpfile;        # add input file to @$argv

my $dumpbase = get_dumpbase();     # this seems to be the original source file

# Output behavior:
# You can specify an output file with -o FILE; the space before FILE is required
my $outfile = get_output_filename() || deduce_output_filename($infile);
die unless defined $outfile;

my $run_args = join(':', $prog, @$argv);
run_prog();                                       # delegate to the real thing
check_output_file($outfile);

# append metadata to output
my $metadata = <<'END'                              # do not interpolate
        .section        .note.cc1_interceptor,"",@progbits
END
  ;

# initialize anything still uninitialized
$infile = '-' unless defined $infile;
$metadata .= <<END                                  # do interpolate!
        .ascii "("
        .ascii "\\n\\tpwd:${pwd}"
        .ascii "\\n\\tdollar_zero:$0"
        .ascii "\\n\\traw_args: ("
END
    ;

for my $a (@$raw_args) {
    $metadata .= <<END                                # do interpolate!
        .ascii "\\n\\t\\t${a}"
END
;
}

my $pkg = $ENV{BUILD_INTERCEPTOR_PACKAGE} || '';
my $timestamp = $ENV{BUILD_INTERCEPTOR_TIMESTAMP} || '';
my $chroot_id = $ENV{BUILD_INTERCEPTOR_CHROOT_ID} || '';

$metadata .= <<END                                  # do interpolate!
        .ascii "\\n\\t)"
        .ascii "\\n\\trun_args:${run_args}"
        .ascii "\\n\\torig_filename:${orig_filename}"
        .ascii "\\n\\tinfile:${infile}"
        .ascii "\\n\\tdumpbase:${dumpbase}"
        .ascii "\\n\\ttmpfile:${tmpfile}"
        .ascii "\\n\\tifile:${rel_tmpfile}"
        .ascii "\\n\\tpackage:${pkg} ${timestamp} ${chroot_id}"
        .ascii "\\n\\tmd5:${md5}"
        .ascii "\\n)\\n"
END
  ;

append_to_file($outfile, $metadata);



sub get_orig_filename {
    my $orig_filename = '';
    my @orig_filenames = grep {/^---build-interceptor-orig_filename=.*$/} @$argv;
    if (@orig_filenames) {
        die "more than one orig_filenames" if ($#orig_filenames > 0);
        $orig_filenames[0] =~ /^---build-interceptor-orig_filename=(.*)$/;
        $orig_filename = File::Spec->rel2abs($1);
        # warn "tmpfile:${tmpfile}: from --build-interceptor-orig_filenames\n";
        @$argv = grep {!/^---build-interceptor-orig_filename=.*$/} @$argv;
    }
    return $orig_filename;
}

sub get_input_and_tname {
    # If we have been told the original name of the file, use that.
    my @infiles = grep {/\.ii?$/} @$argv; # get any input files
    my $infile;
    my $tname;
    my $input;
    if (@infiles) {
        $infile = $infiles[$#infiles]; # the last infile
        die "$0: no such file '$infile'" unless -f $infile;
        @$argv = grep {!/\.ii?$/} @$argv;   # remove from @$argv
        # make the temp file name
        $input = File::Spec->rel2abs($infile);
        $tname = $orig_filename || $input;
    } else {
        $infile = '-';
        # make the temp file name
        $input = \$STDIN;
        $tname = $orig_filename || "$pwd/STDIN";
    }

    return ($infile, $input, $tname);
}

sub get_dumpbase {
    my $dumpbase = [];
    for (my $i=0; $i<@$argv; ++$i) {
        if ($argv->[$i] eq '-dumpbase') {
            push(@$dumpbase, $argv->[$i+1]);
        }
    }
    return join(":",@$dumpbase);
}

sub deduce_output_filename {
    my ($infile) = @_;

    # If we don't see an output filename on the command line, deduce it.
    my $outfile;

    # By default, output to stdout if input from stdin.  "-" means stdout.
    if ($infile eq '-') {
        $outfile = '-';
    }
    # Otherwise, it puts it in the last .i file mentioned with .i
    # replaced with .s
    else {
        $outfile = $infile;
        $outfile =~ s|\.ii?$|.s|;
    }
    return $outfile;
}

sub uniquify_filename {
    my ($filename) = @_;
    my $time0 = time;
    my $unique = "$time0-$$";

    # $filename =~ s|\.|-$unique.| ||
    $filename .= "-$unique";
    return $filename;
}

sub copy_file {
    my ($input, $tmpfile) = @_;
    ensure_dir_of_file_exists($tmpfile);
    die "$0: tmpfile '$tmpfile' already exists" if -e $tmpfile;
    copy($input, $tmpfile) || die "$0: couldn't copy $input $tmpfile: $!";
    die "$0: couldn't copy to tmpfile '$tmpfile'" unless -e $tmpfile;
}
