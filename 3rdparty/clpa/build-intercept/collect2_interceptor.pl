#!/usr/bin/perl -w
# See License.txt for copyright and terms of use
use strict;
use warnings;
use FindBin;
use lib "${FindBin::RealBin}";
use BuildInterceptor ':all';

use FindBin;
use Cwd;
use Cwd 'abs_path';
use File::Spec;
use File::Path;                 # provides mkpath
use File::Basename;
use File::Temp;
use FileHandle;
use Memoize;

# When used as a replacement to the system collect2 will just pass the
# arguments through.

if (grep {/^--help$/ || /^--version$/ || /^-[vV]$/ } @$raw_args) {
    intercept_prog();
}

# make a unique id for breaking symmetry with any other occurances of
# this process
my $time0 = time;
my $unique = "$$-$time0";

# directory for all build interceptor temporaries
my $tmpdir_interceptor = $ENV{BUILD_INTERCEPTOR_TMP} || "${home_path}/build-interceptor.tmpdir";
mkpath($tmpdir_interceptor);
# directory for all the temporaries relevant to collect2 interceptor
my $tmpdir = "$tmpdir_interceptor/collect2";
mkpath($tmpdir);

# directory where we cache the "built with cc1" test
my $cc1_test_cache = "$tmpdir/cc1_test";
mkpath($cc1_test_cache);
my $cc1_test_cache_good = "$cc1_test_cache/good/";
mkpath($cc1_test_cache_good);
my $cc1_test_cache_bad = "$cc1_test_cache/bad/";
mkpath($cc1_test_cache_bad);

# directory where archives are unpacked
my $ar_cache = "$tmpdir/ar_cache";
mkpath($ar_cache);

# You can't re-use a section name, and it seems that sometimes both
# collect2 and ld are called on the same file.  Update: It seems that
# collect2 calls ld.
my $sec_name = basename($arg0);
die "$0: bad sec_name:$sec_name:" unless
  $sec_name eq 'ld' ||
  $sec_name eq 'collect2';

# test-only extract
my $extract_pl = "${FindBin::RealBin}/extract_section.pl";
if (!-f $extract_pl) {
    die "$0: Couldn't find extract_section.pl (should be $extract_pl)\n";
}
my $extract = "$extract_pl -t -q";

memoize('md5_file');

sub canonicalize {
    my ($filename) = @_;
    if (!-f $filename) {
        die "$0: can't find $filename";
    }
    my $canon = Cwd::realpath(File::Spec->rel2abs($filename));
    if (!$canon) {
        die "$0: can't find $filename";
    }
    if (!-f $canon) {
        die "$0: can't find $filename [$canon]";
    }
    return $canon;
}

sub archive_extract_object {
    my ($archive, $object) = @_;
    if (!-f $archive) {
        die "$0: archive not found: $archive";
    }

    my $md5sum = md5_file($archive);
    my $dname = "$ar_cache/$md5sum";

    if (!-d $dname) {
        mkdir $dname || die;
        if (system("cd $dname && ar x $archive")) {
            die;
        }
    }

    my $file = "$dname/$object";
    if (! -f $file) {
        die "$0: Couldn't find archive $archive object $object";
    }

    return $file;
}

sub check_object_intercepted {
    my ($file) = @_;
    return 0 == system("$extract .note.cc1_interceptor $file");
}

sub check_object_interceptless {
    my ($file) = @_;
    return 0 == system("$extract .note.ignore_cc1_interceptor $file");
}

sub check_object_empty {
    my ($file) = @_;
    return 0 == system("$extract .note.as_interceptor_empty $file");
}

sub check_object_fortran_only {
    # check that an executable was Fortran, and not C/C++
    my ($file) = @_;
    return ((0==system("$extract .note.f771_interceptor $file")) &&
            (!check_object_intercepted($file)));
}

sub check_object_ocaml {
    # check that an executable contains Ocaml
    my ($file) = @_;
    return ((0==system("$extract .note.ocaml_interceptor $file"))
            # && (!check_object_intercepted($file))
        );
}

sub check_object_has_ld_interception {
    my ($file) = @_;
    return 0 == system("$extract .note.ld_interceptor $file");
}

sub add_section {
    my ($file, $section, $content) = @_;

    my $tmpfile = new File::Temp(TEMPLATE=>"/tmp/elf.XXXXXXXXX");
    print $tmpfile $content;
    $tmpfile->close();

    my @objcopy_cmd =
      ('objcopy', $file, '--add-section', ".note.${section}=$tmpfile");
    if (system(@objcopy_cmd)) {
        die "$0: Error executing @objcopy_cmd\n";
    }
}

sub remove_section {
    my ($file, $section) = @_;
    my @cmd = ('objcopy', $file, '--remove-section', ".note.${section}");
    if (system(@cmd)) {
        die "$0: Error executing @cmd\n";
    }
}

sub add_or_append_section {
    my ($file, $section, $content) = @_;

    my $existing_note = `$extract_pl .note.$section $file 2>/dev/null`;
    my $err = $? >> 8;
    if ($err == 1) {
        # no existing note
        if ($existing_note) { die; }
    } elsif ($err == 0) {
        # existing note
        if (!$existing_note) { die; }
        remove_section($file, $section);
    } else {
        die "$0: unknown exit code extracting .note.$section from '$file': $err\n";
    }

    add_section($file, $section, $existing_note . $content);
}

# where are we?
my $pwd = getcwd;

my $outfile = get_output_filename() || 'a.out';
my $outfile_abs = File::Spec->rel2abs($outfile);

# Print out the files that are linked in.
unshift @$argv, "--trace";
my $run_args = join(':', @$argv);

# Run the real ld and get its stdout.  Don't catch stderr -- random error
# messages go there and can confuse us [this would break for example linking
# any object that invokes tmpnam()].
my $trace_output0 = pipe_prog();                  # delegate to the real thing
check_output_file($outfile_abs);

my $executable_p = -x $outfile_abs &&
 $outfile_abs !~ /[.](?:so(?:[.]\d+)*(?:-UTF8)?|la|al|o|lo|os|oS|po|opic|pic_o|sho)$/;

if (do_not_add_interceptions_to_this_file_p($outfile_abs)) {
    # Don't add .note.ld_interceptor, and in addition, remove
    # .note.cc1_interceptor.
    #
    # Some build processes break when we insert these; and we aren't going to
    # analyze them so it's OK to remove notes.
    remove_section($outfile_abs, 'cc1_interceptor');
    exit(0);
}

# Double-indent this to quote it.
my $trace_output = tab_indent_lines($trace_output0);
# Make sure ends in a newline, since we count on that below for tab quoting.
die unless $trace_output =~ m|\n$|;

my $intercept_data = '';


$intercept_data .= <<END        # do interpolate!
(
\tpwd:${pwd}
\tdollar_zero:$0
\traw_args: (
END
  ;

for my $a (@$raw_args) {
$intercept_data .= <<END        # do interpolate!
\t\t${a}
END
  ;
}

$intercept_data .= <<END        # do interpolate!
\t)
\trun_args:${run_args}
\toutfile:${outfile}
\toutfile_abs:${outfile_abs}
\ttrace_output: (
${trace_output}\t)
)
END
  ;

# Stick this stuff into the object file
add_or_append_section($outfile_abs, "${sec_name}_interceptor", $intercept_data);

my $EXTRA_OBJ_EXT = $ENV{BUILD_INTERCEPTOR_EXTRA_OBJECT_EXTENSIONS} ?
    "|".$ENV{BUILD_INTERCEPTOR_EXTRA_OBJECT_EXTENSIONS} : '';

my $EXTRA_IGNORE_LINES = $ENV{BUILD_INTERCEPTOR_EXTRA_IGNORE_LINES};

# don't bother proclaiming failures for ocaml files
if (check_object_ocaml($outfile_abs)) {
    my $good = new FileHandle(">>$tmpdir/cc1_ignored_ocaml") or die $!;
    print $good "$outfile_abs\n";
    exit 0;
}


my @not_intercepted;
# if we are ld, then iterate through the .o files that were generated
# warn "trace_output0 -----\n$trace_output0\n-----\n";
for my $line (split '\n', $trace_output0) {
  chomp $line;

  # skip this line: /usr/bin/ld_orig: mode elf_i386
  next if $line =~ m/: mode elf_i386$/;
  next if $line =~ m/: mode elf_x86_64$/;

  my $file;
  if ($line =~ m/^\(([^()]+[.]al?)\)([^()]+[.](?:o|os|oS|lo|ao$EXTRA_OBJ_EXT))$/) {
      # TODO: remove .ao after figuring out which package needed it

      # .o from .a:
      # (/path/archive.a)object.o
      my $archive = canonicalize($1);
      my $object = $2;

      $file = archive_extract_object($archive, $object);
  } elsif ($line =~ m/^-l[^ ()]+ \(([^()]+[.]so(?:[.][0-9]+)*)\)$/) {
      # shared libraries:
      # -lm (/usr/lib/libm.so)
      # -lgtk (/opt/gnome/lib/libgtk.so)
      # ignore for now
      next;
      # $file = $1;
  } elsif ($EXTRA_IGNORE_LINES && $line =~ m/^${EXTRA_IGNORE_LINES}$/) {
      # Some packages have weird names for shared libraries that we can also
      # ignore.
      #
      # Some packages have extra crud that we just have to ignore (e.g. jpeg
      # files)
      next;
  } elsif ($line =~ m/-lieee \(.*\/libieee.a\)$/) {
      # These are the contents of the file ieee-math.c which build the
      # *shared* library /usr/lib/libieee.a:
      #     /* Linking in this module forces IEEE error handling rules for
      #     math functions.
      #        The default is POSIX.1 error handling.  */
      #
      #     #include <math.h>
      #
      #     _LIB_VERSION_TYPE _LIB_VERSION = _IEEE_;
      #
      # All it does is change error handling; -lm is still required.  It gets
      # added as a result of gcc -mieee-fp.  So I think it is safe to ignore
      # this particular library.
      next;
  } elsif ($line =~ m/^([^()]+\.(?:o|os|oS|lo|sho|po|opic|pic_o|ro$EXTRA_OBJ_EXT))$/) {
      # TODO: remove .sho,po,opic,pic_o,ro after figuring out which packages
      # needed them

      # a .o file not from an archive, like this:
      #   /usr/lib/crt1.o
      # Can also include .lo (libtool object) files.
      $file = canonicalize($1);
  } elsif ($line =~ m/^([^()]+\.so(?:[.][0-9]+)*(?:-UTF8)?)$/) {
      # $file = canonicalize($1);
      next;
  } else {
      die "$0: unknown trace_output line: $line\n\nTrace output:\n$trace_output0";
  }

  # get the file id
  die "$0: Something is wrong, no such file :$file:" unless -f $file;
  # my $file_id = getCanonIdForFile($file);
  my $file_id = md5_file($file);

  # see if the file was the result of compiling with build
  # interception turned on
  my $built_with_interceptor;

  # check the cc1 test cache; NOTE: in case you are afraid of the
  # complexity of this, for a simple C++ hello world on my system with
  # a warm cache the link time went from 5.9 seconds to 1.4 seconds
  my $cachefile_good = "$cc1_test_cache_good/$file_id";
  my $cachefile_bad = "$cc1_test_cache_bad/$file_id";
#    warn "cachefile_ok: '$cachefile_ok', cachefile_bad: '$cachefile_bad'\n";
  if (-e $cachefile_good) {
    $built_with_interceptor = 1;
#      warn "\tfound cache ok $cachefile_ok";
    # outputToFile($cachefile_ok, $file); # update the cache
  } elsif (-e $cachefile_bad) {
    $built_with_interceptor = 0;
#      warn "\tfound cache bad $cachefile_ok";
    # outputToFile($cachefile_bad, $file);  # update the cache
  } else {
      # actually run the extractor
      #      warn "\tNOT found in cache";
      $built_with_interceptor = (check_object_intercepted($file) ||
                                 check_object_interceptless($file) ||
                                 check_object_empty($file) ||
                                 check_object_fortran_only($file) ||
                                 check_object_ocaml($file)
          );
      if ($built_with_interceptor) {
          outputToFile($cachefile_good, $file); # update the cache
      } else {
          outputToFile($cachefile_bad, $file); # update the cache
      }
  }

  # record if ok or not
  unless ($built_with_interceptor) {
    push @not_intercepted, $line;
  }
}

if (@not_intercepted) {
    # bad; some files we were built with were not intercepted
    my $bad = new FileHandle(">>$tmpdir/cc1_bad") or die $!;
    print $bad "$outfile_abs\n";
    for my $input (@not_intercepted) {
        print $bad "\t$input\n";
    }

    # categorize into executable and non-executable (call it non-executable to
    # be conservative, since non-executables are more dangerous and we're
    # checking for dangerous situations)
    my $bad_ftype = $executable_p ? "exec" : "nonexec";
    $bad = new FileHandle(">>$tmpdir/cc1_bad_${bad_ftype}") or die $!;
    print $bad "$outfile_abs\n";
    for my $input (@not_intercepted) {
        print $bad "\t$input\n";
    }

    # put a bad section into the file
    my $bad_section_data = join("", map{"$_\n"} @not_intercepted);
    add_or_append_section($outfile_abs, "${sec_name}_interceptor_bad",
                          $bad_section_data);
} else {
    # good
    my $good = new FileHandle(">>$tmpdir/cc1_good") or die $!;
    print $good "$outfile_abs\n";
}

exit 0;

# subroutines ****************

# get a canonical id for a file; this is better than the absolute path
# because the id will become invalid if the inode changes but also
# even if it or the file is modified
sub getCanonIdForFile {
  my ($filename) = @_;
  # check for cached results; from 'perldoc -f stat':
#    my ($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,
#        $atime,$mtime,$ctime,$blksize,$blocks) = stat($file);
  my (undef,$ino,undef,undef,undef,undef,undef,undef,
      undef,$mtime,$ctime,undef,undef) = stat($filename);
  die "$0: no such file $filename"
    unless defined $ino && defined $mtime && defined $ctime;
  my $file_id = "${ino}_${ctime}_${mtime}";
  return $file_id;
}

sub touchFile {
    my ($file) = @_;
    mkpath(dirname($file));
    new FileHandle(">$file") || die $!;
}

sub outputToFile {
    my ($file, $data) = @_;
    die unless defined $file && defined $data;
    mkpath(dirname($file));
    my $f = new FileHandle(">>$file") || die $!;
    print $f $data;
}
