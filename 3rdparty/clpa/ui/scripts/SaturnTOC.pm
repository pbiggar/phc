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

package SaturnTOC;

use strict;
use XMLParser;
use URI::Escape;

sub genTOC {
  my($self, $linkURL, $config, $category, @keys) = @_;
  my($returnHTML, $curLink, @tocKeys, %parsedKeys);

  my $displayFile = SaturnConf->queryConfig($config,"display");
  my $styleSheet = SaturnConf->queryConfig($config,"style");
  my $bdbUtilPath = SaturnConf->queryConfig($config,"binpath");
  my $auxDisplay = SaturnConf->maybeConfig($config,"auxdisplay");

  # If we didn't get any keys as parameters to this function, use
  # dbkeys to get the set of all keys in the database.
  if(@keys == 0) {
    my $cmd = "$bdbUtilPath/dbkeys $displayFile";
    @keys = `$cmd`;
  }

  # Prune out empty strings.
  foreach my $key (@keys) {
    if($key ne "") {
      push @tocKeys, $key;
    }
  }

  foreach my $key (@tocKeys) {
    chomp $key;
    my $parsedXML = XMLParser->parseDBEntry($bdbUtilPath, $displayFile, $auxDisplay, $key);

    if(not (defined $category) || $category eq "" || $parsedXML->{$key}->{"category"} eq $category) {
      $parsedKeys{$key} = $parsedXML->{$key};
    }
  }

  $returnHTML .= "<html><head><title>Saturn Reports: Table of Contents</title>\n";
  $returnHTML .= "<link rel=\"stylesheet\" type=\"text/css\" href=\"$styleSheet\" />\n";
  $returnHTML .= "</head><body>\n";
  $returnHTML .= "<center><h2><span class=\"sc\">Saturn</span> Reports: Table of Contents</h2>\n";
  $returnHTML .= "<table class=\"toc\" id=\"toc\">\n";
  $returnHTML .= "<tr><th>Report</th>\n";
  $returnHTML .= "<th>Category</th>\n";
  $returnHTML .= "<th>Function</th>\n";
  $returnHTML .= "<th>File</th>\n";
  $returnHTML .= "<th>Line</th></tr>\n";

  foreach my $key (sort(keys %parsedKeys)) {
    if($linkURL eq "-static") {
      my $outputFileName = $key;
      $outputFileName =~ s/\W/_/g;
      $curLink = "$outputFileName.html";
    } else {
      $curLink = $linkURL . "&report=" . uri_escape($key);
    }

    $returnHTML .= "<tr>";
    $returnHTML .= "<td><a href=\"$curLink\">" . $parsedKeys{$key}->{"title"} . "</a></td>\n";
    $returnHTML .= "<td align=\"center\">" . $parsedKeys{$key}->{"category"} . "</td>\n";
    $returnHTML .= "<td align=\"center\">" . $parsedKeys{$key}->{"function"} . "</td>\n";
    $returnHTML .= "<td align=\"center\">" . $parsedKeys{$key}->{"fileName"} . "</td>\n";
    $returnHTML .= "<td align=\"center\">" . $parsedKeys{$key}->{"focusLine"} . "</td>\n";
    $returnHTML .= "</tr>\n";
  }

  $returnHTML .= "</table></center></body></html>\n";

  return $returnHTML;
}

1;
__END__
