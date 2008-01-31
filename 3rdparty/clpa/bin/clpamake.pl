#!/usr/bin/perl

use strict;
use POSIX qw(setsid);

use File::Spec;
use Getopt::Long;
use Pod::Usage;
use Cwd;

my $sourcedir = "";
my $subroot = "";
my $program = "";

my $make = 1;
my $extract = 1;
my $combine = 1;
my $daemon = 0;
my $help = 0;

GetOptions ('sources=s' => \$sourcedir,
            'root=s' => \$subroot,
            'program=s' => \$program,
            'make!' => \$make,
            'extract!' => \$extract,
            'daemon!' => \$daemon,
            'help|?' => \$help);

pod2usage(1) if $help;

pod2usage("Need -sources") if ($sourcedir eq "");
pod2usage("Need -root") if ($subroot eq "");

$sourcedir = File::Spec->rel2abs($sourcedir,cwd);

my $rootdir = "$sourcedir/$subroot";
my $tmp = "$sourcedir/$subroot/tmp";
my $logic = "$sourcedir/$subroot/logic";

$ENV{TMPDIR} = $tmp;

if ($daemon == 1) {
    defined(my $pid = fork) or die "can't fork";
    if ($pid) {
        printf "Successfully forked, exiting...\n";
        exit;
    }
    setsid or die "can't set sid";
}

my $start = time();

if ($make == 1) {
    system("rm -rf $rootdir") if (-e $rootdir);
    system("mkdir $rootdir");

    my $mkflags = "";
    if ($sourcedir =~ /\/linux\-/) {
        print "detected linux, using V=1\n";
        $mkflags .= "V=1";
    }

    # Make the source target
    chdir($sourcedir);
    print "make $mkflags\n";
    system("make clean > /dev/null 2> /dev/null");
    system("make $mkflags | tee $rootdir/make.txt 2> $rootdir/makewrn.txt");
}

my $maketime = time() - $start;

if ($extract == 1) {
    system("rm -rf $tmp") if (-e $tmp);
    system("mkdir $tmp");

    system("rm -rf $logic") if (-e $logic);
    system("mkdir $logic");

    # Extract the GCC commands
    system("extract.pl cilly < $rootdir/make.txt > $rootdir/makegcc.txt");

    # Execute the corresponding cil commands
    open(EXTRACT, "$rootdir/makegcc.txt");
    while (my $extractline = <EXTRACT>) {
	chop $extractline;
        $extractline =~ s/\&\&.*//;
	system("$extractline > $tmp/cillygcc.txt 2> $tmp/cilly.txt");
	open(CILLY, "$tmp/cilly.txt");
	while (my $line = <CILLY>) {
	    chop $line;
	    if ($line =~ /^cilcc /) {
		$line = "$line --omitprefix $sourcedir/ --logicdir $logic";
	    }
	    else {
                # Escape any strings
                $line =~ s/\"/\\\"/g;
                $line =~ s/\\\\\"/\\\"/g;
	    }

            print("$line\n");
            system($line);
	}
	close(CILLY);
    }
    close(EXTRACT);
}

my $extracttime = time() - $start - $maketime;

if ($program ne "") {
    # Perform the interprocedural analysis
    system("clpa --logic $logic $program | tee $rootdir/output.txt");
}

my $ipanltime = time() - $start - $maketime - $extracttime;

my $totaltime = time() - $start;

sub getdifftime {
    my $diff = shift;
    my $seconds = $diff % 60;
    my $minutes = ($diff / 60) % 60;
    my $hours = ($diff - ($diff % 3600)) / 3600;

    my $secspacer = ($seconds < 10) ? "0" : "";
    my $minspacer = ($minutes < 10) ? "0" : "";
    my $hourspre = ($hours > 0) ? "$hours:$minspacer" : "";

    return "$hourspre$minutes:$secspacer$seconds";
}

open(TIME, "> $rootdir/times.txt");

my $tdiff = getdifftime($totaltime);
my $mdiff = getdifftime($maketime);
my $ediff = getdifftime($extracttime);
my $idiff = getdifftime($ipanltime);

my $timestr =
      "MAKE:    $mdiff\n"
    . "EXTRACT: $ediff\n"
    . "IPANL:   $idiff\n"
    . "-------\n"
    . "OVERALL: $tdiff\n";

print "\n$timestr";
print TIME $timestr;

close(TIME);

__END__

=head1 NAME

sample - Using Getopt::Long and Pod::Usage

=head1 SYNOPSIS

clpamake [options]

Options:

    -help         brief help message
    -sources=s    program source directory [required]
    -root=s       analysis subdirectory [required]
    -program=s    CLP to run
    -make!        Make the sources (def:true)
    -extract!     Extract logic from the sources (def:true)
    -daemon!      Run in daemon mode (def:false)
    -linux!       Running on linux sources (def:false)

=cut
