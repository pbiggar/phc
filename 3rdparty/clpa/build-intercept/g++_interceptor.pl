#!/usr/bin/perl -w
use strict;
use warnings;
use FindBin;
use lib "${FindBin::RealBin}";
use BuildInterceptor ':all';

# Move the system gcc executable to gcc_orig and make a softlink from
# the name gcc to this script.

# The intent is that when gcc is run, dirname $0 will be the directory
# that contains the link to this script, and should be the directory
# where the gcc executable got moved to gcc_orig.

if ("@$raw_args" =~ /-E -P -\s*$/ || grep {$_ eq '-V'} @$raw_args) {
    # -E -P kludge: don't output line markers if the program is just using gcc
    # to get preprocessor definitions.  What glibc does is:
    #     echo '#include <linux/version.h>\nUTS_RELEASE' | gcc -E -P -
    # -V kludge: with -V argument (which must be first): just call gcc-VERSION
    # (which is also intercepted)
    intercept_prog();
}

my $BUILD_INTERCEPTOR_EXTRA_GCC_ARGS = [
    split(/ /, $ENV{BUILD_INTERCEPTOR_EXTRA_GCC_ARGS}||'')];

my $version = get_gcc_version();

if ($version >= 3.0) {
    # gcc-2.95 always has non-integrated cpp.
    unshift(@$argv, "--no-integrated-cpp");
}

my $specfile = get_spec_file($version);

if (grep {$_ eq '-v'} @$raw_args) {
    print STDERR "Build-Interceptor enabled; gcc appears to be version $version, so using specfile $specfile\n";
}

if (!-f $specfile) {
    die "$0: can't find specfile $specfile";
}

unshift(@$argv, "-specs=$specfile");
unshift(@$argv, @$BUILD_INTERCEPTOR_EXTRA_GCC_ARGS);

# We no longer need this:
#  unshift(@$argv, "-B$FindBin::RealBin");

intercept_prog();

sub get_gcc_version {
    my $version_data = ` ($prog -v >/dev/null ) 2>&1 `;
    if ($? != 0) {
        die "$0: couldn't run $prog to get gcc version; exit code $?\n";
    }

    # get major and minor version numbers (but not patch level)
    if ($version_data !~ /^gcc version (\d+[.]\d+)/m) {
        die "$0: couldn't parse version number from $prog -v\n";
    }

    my $version = $1;

    if ($version < 2.0 || $version > 5.0) {
        die "$0: insane gcc version $version\n";
    }

    return $version;
}

sub get_spec_file {
    my ($version) = @_;
    die unless $version;

    my $d = $FindBin::RealBin;
    if ($version < 3.0) {
        # gcc-2.95
        return "$d/interceptor.specs-2.95";
    } elsif ($version < 3.4) {
        # gcc-3.0, gcc-3.1, gcc-3.2, gcc-3.3
        return "$d/interceptor.specs-3.0";
    } elsif ($version < 4.2) {
        # gcc-3.4, gcc-4.0
        return "$d/interceptor.specs-3.4";
    } else {
        die "$0: I don't know which spec file to use for gcc version $version\n";
    }
}
