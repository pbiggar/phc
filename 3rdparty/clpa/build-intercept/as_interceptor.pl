#!/usr/bin/perl -w
# See License.txt for copyright and terms of use

use warnings;
use strict;
use FindBin;
use lib "${FindBin::RealBin}";
use BuildInterceptor ':all';

use File::Spec;
use FileHandle;
use File::Basename;

my $extract_pl = "${FindBin::RealBin}/extract_section.pl";
if (!-f $extract_pl) {
    die "$0: Couldn't find extract_section.pl (should be $extract_pl)\n";
}

sub find_input_filename {
    my @infiles = grep { /[.][sS]$/ } @$argv;
    return $infiles[0];
}

sub file_contains_ocaml_asm {
    # Returns 1 iff we think this .s file was the output of ocamlopt.  They're
    # named /tmp/camlasm*.s, and their contents start with ".data\n.globl
    # caml".

    my ($filename) = @_;
    return 0 unless $filename =~ m,^/tmp/caml.*[.]s$,;

    my $fh = new FileHandle($filename) or die;
    my ($l1, $l2) = <$fh>;
    return ($l1 && $l1 =~ /^\t[.]data/ and
            $l2 && $l2 =~ /^\t[.]globl\s+caml/);
}

sub file_contains_java_asm {
    # Returns 1 iff we think this .s file was the output of gcj.
    my ($filename) = @_;
    my $fh = new FileHandle($filename) or die;
    my ($l1) = <$fh>;
    return ($l1 =~ /^\t.file\s+".+?[.]java"/);
}

sub file_contains_gcj_resource {
    # Returns 1 iff we think this .s file was the output of gcj --resource.
    # These are simply data files (such as a .gif) embedded in a .o with a
    # little bit of stub code to access it.
    my ($filename) = @_;
    my $fh = new FileHandle($filename) or die;
    local $_;
    while (<$fh>) {
        if (/^\.globl _Jv_RegisterResource/) {
            return 1;
        }
    }
    return 0;
}

my $infile = find_input_filename();

if ($infile && -f $infile && file_is_empty_p($infile)) {
    # if the file was empty, remember so.  (This is needed later by
    # as_interceptor as well as collect2_interceptor)
    my $metadata = <<'END'         # do not interpolate
        .section        .note.as_interceptor_empty,"",@progbits
        .ascii "dummy\n"
END
;
    append_to_file($infile, $metadata);
}

my $lang = 'x';
if ($infile && -f $infile && file_contains_ocaml_asm($infile)) {
    # It's hard to intercept ocamlopt, so for now it's good enough to ignore
    # it here.
    $lang = 'ocaml';

    my $metadata = <<'END'         # do not interpolate
        .section        .note.ocaml_interceptor,"",@progbits
        .ascii "dummy\n"
END
;
    append_to_file($infile, $metadata);
}

if ($infile && -f $infile && file_contains_java_asm($infile)) {
    $lang = 'java';

    my $metadata = <<'END'         # do not interpolate
        .section        .note.java_interceptor,"",@progbits
        .ascii "dummy\n"
END
;
    append_to_file($infile, $metadata);
}

if ($infile && -f $infile && file_contains_gcj_resource($infile)) {
    $lang = 'java_resource';

    my $metadata = <<'END'         # do not interpolate
        .section        .note.java_resource_interceptor,"",@progbits
        .ascii "dummy\n"
END
;
    append_to_file($infile, $metadata);
}

run_prog();                                      # delegate to the real thing.

my $outfile = get_output_filename() || 'a.out';
my $outfile_abs = File::Spec->rel2abs($outfile);
check_output_file($outfile);

# if ($infile && -f $infile && file_is_empty_p($infile)) {
#     # We don't need interceptions if the .S was empty.  Some packages have
#     # some #ifdefs that end up creating empty .S files -- it's OK to link
#     # them.

#     exit(0);
# }

if (do_not_add_interceptions_to_this_file_p($outfile_abs)) {
    # there shouldn't be any .notes at this point, but don't add or check for
    # more.
    exit(0);
}

my $cc1_note = `$extract_pl .note.cc1_interceptor $outfile 2>/dev/null`;
if ($? || !$cc1_note) {
    my $empty_note = `$extract_pl .note.as_interceptor_empty $outfile 2>/dev/null`;
    if ($empty_note && !$?) {
        # ignore empty .S files
        exit 0;
    }

    my $f771_note = `$extract_pl .note.f771_interceptor $outfile 2>/dev/null`;
    if ($f771_note && !$?) {
        # Ignore fortran files for now
        exit 0;
    }

    my $ocaml_note = `$extract_pl .note.ocaml_interceptor $outfile 2>/dev/null`;
    if ($ocaml_note && !$?) {
        # Ignore ocaml files for now
        exit 0;
    }

    my $java_note = `$extract_pl .note.java_interceptor $outfile 2>/dev/null`;
    if ($java_note && !$?) {
        # Ignore java files for now
        exit 0;
    }

    my $java_resource_note = `$extract_pl .note.java_resource_interceptor $outfile 2>/dev/null`;
    if ($java_resource_note && !$?) {
        # Ignore java resource files
        exit 0;
    }

    # hawkinsp: Dying is clearly wrong if we're compiling a hand-written
    # assembly file.
    exit(0);
#    die "$0: assembled file with no .note.cc1_interceptor: $outfile\n";
}

my ($tmpfile) = ($cc1_note =~ /^\ttmpfile:(.*)$/m) or
  die "$0: couldn't find tmpfile in .note.cc1_interceptor in $outfile:\n$cc1_note\n";
my ($md5) = ($cc1_note =~ /^\tmd5:(.*)$/m) or
  die "$0: couldn't find md5 in .note.cc1_interceptor in $outfile:\n$cc1_note\n";


if (!-f $tmpfile) {
    die "$0: couldn't find tmpfile $tmpfile from $outfile\n";
}

if (! $ENV{BUILD_INTERCEPTOR_DONT_EMBED_PREPROC}) {
    system('objcopy', $outfile, '--add-section', ".file.$md5=$tmpfile") &&
      die "$0: couldn't objcopy .file.$md5=$tmpfile";
}
