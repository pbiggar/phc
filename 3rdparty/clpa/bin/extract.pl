#!/usr/bin/perl

# Extracts calls to gcc from a make output, replaces gcc with
# $newcc and writes the resulting calls back out.

$usage = "USAGE: extract.pl newcc < input > output\n";
$newcc = shift or die $usage;

@dir_stack = ();
@curr_dir = ();

$pwd = `pwd`; chomp($pwd);
set_currdir($pwd);

while ($line = <>) {
    chomp($line);
    $line =~ s/^cc /gcc /;
    $line =~ s/\s+gcc /gcc /;
    # stupid hack for httpd
    $line =~ s/.*srclib\/apr\/libtool --silent --mode=compile//;
    if ($line =~ /^gcc/) {
        die "..." unless (scalar(@curr_dir));
        @args = split / +/, $line;
        $args[0] = $newcc;
        for ($i = 1; $i < scalar(@args); $i++) {
            $a = $args[$i];
            if ($a =~ /-I(.*)/) {
                $path = rm_dotdot($1);
                $args[$i] = "-I$path";
            }
            elsif ($a =~ /-L(.*)/) {
                $path = rm_dotdot($1);
                $args[$i] = "-L$path";
            }
            elsif ($a eq '-o') {
                $i++;
                $args[$i] = make_abs($args[$i]);
            }
	    elsif ($a =~ /^\/usr\/lib\/gcc-lib\//) {
		# stupid hack for linux
		$args[$i] = "-I$a";
	    }
            elsif ($a =~ /^\/usr\/lib\/gcc\//) {
                $args[$i] = "-I$a";
            }
            elsif (!($a =~ /^-/)) {
                $args[$i] = make_abs($args[$i]);
            }
        }
        print (join(' ', @args)."\n");
    }
    elsif ($line =~ /Entering directory `(.+)'/) {
	push @dir_stack, $curr_dir;
	set_currdir($1);
        # print "entering '$1'\n";
    }
    elsif ($line =~ /Leaving directory/) {
	my $dir = pop @dir_stack;
	# print "leaving ... reentering '$dir'\n";
	set_currdir($dir);
    }
}

exit 0;

sub set_currdir {
    my $dir = shift;
    $curr_dir = $dir;
    @curr_dir = decompose($curr_dir);
}

sub decompose {
    my $dir = shift;
    return split /\//, $dir;
}

sub make_abs {
    my $path = shift;

    if ($path =~ /^\//) {
	return $path;
    } else {
	return join('/', @curr_dir, $path);
    }
}

sub rm_dotdot {
    my $path = shift;
    my @path = split /\//, $path;
    my @pfx = @curr_dir;

    # print "...processing $path...";
    return $path if ($path =~ /^\//);
    while ($path =~ s/^\.\///) {}
    while ($path =~ s/^\.\.\///) {
        pop(@pfx);
    }
    # print "...arrived at '$path'...";
    if ($path eq '.') {
	return join('/', @pfx);
    } elsif ($path eq '..') {
        pop(@pfx);
        return join('/', @pfx);
    } elsif ($path =~ /^\//) {
	return $path;
    } else {
        return join('/', @pfx, $path);
    }
}


