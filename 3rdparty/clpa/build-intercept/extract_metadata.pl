#!/usr/bin/perl -w
# -*-perl-*-
# See License.txt for copyright and terms of use
use strict;
use FindBin;

# Given an input ELF file infile read the notes and extract the names
# of the .i files embedded and the sections where embedded

# NOTE: This file is very redundant with extract_preproc.pl

# NOTE: I don't know why, but emacs CPerl mode does not work for this
# file.

my $infile;
my $section;
my %md5sum2orig_filename;
my %md5sum2friendly_name;
my %friendly_name2md5sum;

my $extract = "${FindBin::RealBin}/extract_section.pl";
die "Can't find $extract" unless -f $extract;

sub read_command_line {
  while(@ARGV) {
    my $arg = shift @ARGV;
    if ($arg =~ /-infile/) {
      $infile = shift @ARGV;
    } elsif ($arg =~ /-insection/) {
      $section = shift @ARGV;
    } else {
      die "Illegal argument $arg";
    }
  }
  # verify
  die "provide an infile using the flag -infile" unless $infile;
}

sub read_infile_notes {
  my $section = shift || "cc1";  
  my $extractCmd = "$extract .note.${section}_interceptor $infile 2>/dev/null";
#    print "$extractCmd\n";
  my $exOut = `$extractCmd`;
  die "no interceptor notes in $infile" if $exOut eq '';
  eval {
    # for each .i file mentioned:
    my @components = ($exOut =~ m/\s* ( ^ \( $ .*? ^ \) $ ) \s*/gmsx);
    for my $comp (@components) {
        warn "---- comp\n";
        warn "$comp\n";
        warn "\n----\n";
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
      die "bad ELF file: $extractCmd" unless
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
      $md5sum2orig_filename{$md5} = $orig_filename;
    }
  };
  warn ($@) if ($@);
}

# ****

read_command_line();
read_infile_notes($section);
