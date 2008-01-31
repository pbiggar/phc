#!/usr/bin/perl -w

##
# Authors:
#   Ryan Propper   <rpropper@stanford.edu>
#
# Copyright (c) 2006,
#   The Board of Trustees of The Leland Stanford Junior University
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
# 
# 3. The names of the contributors may not be used to endorse or promote
# products derived from this software without specific prior written
# permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
##

use strict;

use SaturnConf;
use SaturnReport;
use SaturnTOC;

my $cfile = $ARGV[0] or die "Usage: static.pl file.conf [category]";
my $category = $ARGV[1];

my $config = SaturnConf->readConfigFile($cfile);

system("rm -rf display") if (-e "display");
system("mkdir display");

open(INDEX_FILE, ">display/index.html");
print INDEX_FILE SaturnTOC->genTOC("-static", $config, $category);
close(INDEX_FILE);

my $binPath = SaturnConf->queryConfig($config,"binpath");
my $displayDB = SaturnConf->queryConfig($config,"display");

my $cmd = "$binPath/dbkeys $displayDB";
my @keys = `$cmd`;

foreach my $key (@keys) {
	chomp $key;
	my $outputFileName = $key;
	$outputFileName =~ s/\W/_/g;

	my $curReportHTML = SaturnReport->genReport("-static", $config, $key, 0, "");

	open(REPORT_FILE, ">display/$outputFileName.html");
	print REPORT_FILE $curReportHTML;
	close(REPORT_FILE);
}
