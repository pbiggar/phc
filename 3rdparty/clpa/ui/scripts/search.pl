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
use CGI qw(:standard);

use SaturnConf;
use SaturnTOC;

sub getSelfURI {
  return 'http://' . $ENV{"SERVER_NAME"} . $ENV{"SCRIPT_NAME"};
}

print "Content-type: text/html\n\n";

if(defined param('conf') && defined param('query') && defined param('search_type') &&
   defined param('category')) {
  my $configFile = param('conf');
  chomp $configFile;

  my $category = param('category');
  chomp $category;

  my $config = SaturnConf->readConfigFile("./configs/$configFile.conf");

  my $binPath = SaturnConf->queryConfig($config,"binpath");
  my $searchDB = SaturnConf->queryConfig($config,"search");

  my @tocEntries;
  if(param('search_type') eq 'keyword') {
    my $keysCmd = "$binPath/dbkeys $searchDB";
    my @searchKeys = `$keysCmd`;

    foreach my $searchKey (@searchKeys) {
      chomp $searchKey;
      if(index($searchKey, param('query')) >= 0) {
        my $findCmd = "$binPath/dbfind $searchDB $searchKey";

        my @findResult = split(/\n/,`$findCmd`);
        foreach my $res (@findResult) {
          push @tocEntries, $res;
        }
      }
    }
  } else {
    my $searchKey = param('query');
    chomp $searchKey;

    if ($searchKey =~ /^[a-zA-Z0-9_]*$/) {
        my $findCmd = "$binPath/dbfind $searchDB $searchKey";
        @tocEntries = split(/\n/,`$findCmd`);
    } else {
	print "Invalid query.\n";
	exit 1;
    }
  }

  if ($#tocEntries >= 0) {
    print SaturnTOC->genTOC("report.pl?db=$configFile", $config, $category, @tocEntries);
  } else {
    print "<html><head><title>Saturn Reports: Not Found</title>\n" .
           "</head><body>\n" .
           "<h2>Saturn Reports: Not found</h2>\n" .
           "<blockquote><p>No matching reports were found.  Click " .
           "<a href=\"search.pl\">here</a> to try a new search." .
           "</p></blockquote></body></html>\n";
  }
} else {
  print '<html><head><title>Saturn Database Query</title>' . "\n";
  print "</head><body>\n";
  print "<center><h2>Search the <span class=\"sc\">Saturn</span> Report Database</h2>\n";
  print "<table width=\"25%\">\n";
  print "<form method=\"post\" action=\"" . getSelfURI() . "\">\n";

  print "<tr><td align=\"right\"><b>Database:</b></td>\n";
  print "<td colspan=\"2\"><select name=\"conf\">\n";

  opendir(DIRHANDLE, "./configs");
  my @fileNames = sort(readdir(DIRHANDLE));
  foreach my $file (@fileNames) {
    if($file =~ /^(\w+)\.conf$/) {
      my $config = SaturnConf->readConfigFile("./configs/$file");
      my $name = SaturnConf->queryConfig($config,"name");
      print "<option value=\"" . $1 . "\">$name</option>\n";
    }
  }
  closedir(DIRHANDLE);

  print "</select></td></tr>\n";

  print "<tr><td align=\"right\"><b>Type:</b></td>\n";
  print "<td><select name=\"search_type\">\n";
  print "<option>exact match</option>\n";
  print "<option>keyword</option></select></td>\n";

  print "<tr><td align=\"right\"><b>Category:<br /><font size=-2>(optional)</font></b></td>\n";
  print "<td><input name=\"category\" type=\"text\" size=\"30\"></td></tr>\n";

  print "<tr><td align=\"right\"><b>Query:</b></td>\n";
  print "<td><input name=\"query\" type=\"text\" size=\"30\"></td></tr>\n";

  print "<tr><td colspan=\"3\" align=\"center\"><input type=\"submit\" value=\"Search\"></td></tr>\n";
  print "</form>\n";
  print "</table></center></body></html>\n";
}
