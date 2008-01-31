#!/usr/bin/perl -w
# -*-perl-*-
# See License.txt for copyright and terms of use
use strict;
use FindBin;

# Given an input ELF file infile and a non-existant directory name
# outdir:
# 1) read the notes and extract the names of the .i files embedded and
#   the sections where embedded
# 2) extract those sections and put them all into a new directory of
#   the given name

# NOTE: I don't know why, but emacs CPerl mode does not work for this
# file.

my @infiles = ();
my $outdir;
my %md5sum2orig_filename;
my %md5sum2tmp_filename;
my %md5sum2friendly_name;
my %friendly_name2md5sum;

my $extract_section = "${FindBin::RealBin}/extract_section.pl";
die "Can't find $extract_section" unless -f $extract_section;

sub read_command_line {
  while(@ARGV) {
    my $arg = shift @ARGV;
    if ($arg =~ /--infile/) {
      my $infile = shift @ARGV;
      push(@infiles, $infile);
    } elsif ($arg =~ /--outdir/) {
      $outdir = shift @ARGV;
    } else {
      die "Illegal argument $arg";
    }
  }
  # verify
  die "provide an infile using the flag -infile" unless @infiles > 0;
  die "provide an outdir using the flag -outdir" unless $outdir;
}

sub read_cc1_notes {
  my $binfile = shift @_;
  my $extract_sectionCmd = "$extract_section .note.cc1_interceptor $binfile 2>/dev/null";
#    print "$extract_sectionCmd\n";
  my $exOut = `$extract_sectionCmd`;
  die "no cc1_interceptor notes in $binfile" if $exOut eq '';
  eval {
    # for each .i file mentioned:
    my @components = ($exOut =~ m/\s* ( ^ \( $ .*? ^ \) $ ) \s*/gmsx);
    for my $comp (@components) {
#        print "---- comp\n";
#        print "$comp\n";
#        print "\n----\n";
      my ($pwd, $dollar_zero, $raw_args, $run_args, $orig_filename,
          $infile, $dumpbase, $tmpfile, $ifile, $package0, $md5) =
        $comp =~
      m|   ^\t pwd:           (.*?) $
        \n ^\t dollar_zero:   (.*?) $
        \n ^\t raw_args: \s \(   $
          (.*?)
        \n ^\t \)                $
        \n ^\t run_args:      (.*?) $
        \n ^\t orig_filename: (.*?) $
        \n ^\t infile:        (.*?) $
        \n ^\t dumpbase:      (.*?) $
        \n ^\t tmpfile:       (.*?) $
        \n ^\t ifile:         (.*?) $
        \n ^\t package:       (.*?) $
        \n ^\t md5:           (.*?) $
        |xsm;
      die "bad ELF file: $extract_sectionCmd" unless
          defined $pwd           &&
          defined $dollar_zero   &&
          defined $raw_args      &&
          defined $run_args      &&
          defined $orig_filename &&
          defined $infile        &&
          defined $dumpbase      &&
          defined $tmpfile       &&
          defined $ifile         &&
          defined $package0      &&
          defined $md5;

      # **** get what we want out of it
      $md5sum2orig_filename{$md5} = $orig_filename;
      $md5sum2tmp_filename{$md5} = $tmpfile;
    }
  };
  print ($@) if ($@);
}

sub try_one_prefix {
    my ($len) = @_;
    %friendly_name2md5sum = ();
    # try this prefix length of the md5 to see if it makes things
    # unique
    foreach my $md5 (keys %md5sum2orig_filename) {
        my $orig_filename = $md5sum2orig_filename{$md5};
        $md5 =~ /(.{$len})/;
        my $stuff = $1;
        die unless length($stuff) == $len;
        my $delim = $len ? '_' : ''; # don't use a delimiter if using none of the md5
        $orig_filename =~ m|^.*?([^/]*)(\.[^\.]+)$| or die "can't match name '$orig_filename'";
        my ($stem, $suffix) = ($1, $2);
        my $friendly_name = "${stem}${delim}${stuff}${suffix}";
        if ($friendly_name2md5sum{$friendly_name}) {
            # name collision; abort and try a longer prefix
            return 0;
        } else {
            $friendly_name2md5sum{$friendly_name} = $md5;
        }
    }
    return 1;
}

sub compute_friendly_names {
    # yes, <= 32
    for (my $len=0; $len<=32; ++$len) {
        # try a prefix of length $len
        if (try_one_prefix($len)) {
            return;
        }
    }
    die "No way can this ever happen.  Go buy a lottery ticket today.";
}

sub reverse_friendly_name_map {
    die if %md5sum2friendly_name;
    while(my ($friendly_name, $md5) = each %friendly_name2md5sum) {
        $md5sum2friendly_name{$md5} = $friendly_name;
    }
}

sub copy_preproc_tmpfiles {
  while(my ($md5, $tmp_filename) = each %md5sum2tmp_filename) {
#    print "extracting md5:$md5, orig_filename:$orig_filename\n";
    my $friendly_name = $md5sum2friendly_name{$md5};
    die unless defined $friendly_name;
    my $outfile = "$outdir/$friendly_name";
    die "something's wrong: file already exists: $outfile" if -e $outfile;
    my $extract_sectionCmd = "cp $tmp_filename $outfile";
#    print "$extract_sectionCmd\n";
    die "command failed" if system($extract_sectionCmd);
  }
}

# ****

read_command_line();
foreach (@infiles) {
    read_cc1_notes($_);
}
die "Output directory does not exist: $outdir" if ! -e $outdir;
compute_friendly_names();
reverse_friendly_name_map();
copy_preproc_tmpfiles();
